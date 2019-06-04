#ifndef COMPUTATIONDOMAIN_H
#define COMPUTATIONDOMAIN_H

#include <stack>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <cassert>



namespace al
{
class SynchronousDomain;

class ComputationDomain
{
public:
  virtual bool initialize() = 0;

  virtual bool cleanup() = 0;

  bool initializeSubdomains(bool pre = false);
  bool tickSubdomains(bool pre = false);
  bool cleanupSubdomains(bool pre = false);

  /**
   * @brief callInitializeCallbacks should be called by children of this class after the domain has been initialized
   */
  void callInitializeCallbacks() {
    for (auto callback: mInitializeCallbacks) {
      callback(this);
    }
  }

  /**
   * @brief callInitializeCallbacks should be called by children of this class before the domain has been cleaned up
   */
  void callCleanupCallbacks() {
    for (auto callback: mCleanupCallbacks) {
      callback(this);
    }
  }

  void registerInitializeCallback(std::function<void(ComputationDomain *)> callback) {
    mInitializeCallbacks.push_back(callback);
  }

  void registerCleanupCallback(std::function<void(ComputationDomain *)> callback) {
    mCleanupCallbacks.push_back(callback);
  }

  template<class DomainType>
  std::shared_ptr<DomainType> newSubDomain(bool prepend = false);

private:
  std::vector<std::pair<std::shared_ptr<SynchronousDomain>, bool>> mSubDomainList;
  std::vector<std::function<void(ComputationDomain *)>> mInitializeCallbacks;
  std::vector<std::function<void(ComputationDomain *)>> mCleanupCallbacks;

};


class SynchronousDomain : public ComputationDomain
{
public:

  virtual bool tick() { return true;}
};

class AsynchronousDomain : public ComputationDomain
{
public:

  virtual bool start() = 0;

  virtual bool stop() = 0;

  /**
   * @brief callInitializeCallbacks should be called by children of this class after the domain has been set up to start, before going into the blocking loop
   */
  void callStartCallbacks() {
    for (auto callback: mStartCallbacks) {
      callback(this);
    }
  }

  /**
   * @brief callInitializeCallbacks should be called by children of this class on the stop request, before the domain has been stopped
   */
  void callStopCallbacks() {
    for (auto callback: mStopCallbacks) {
      callback(this);
    }
  }

private:
  std::vector<std::function<void(ComputationDomain *)>> mStartCallbacks;
  std::vector<std::function<void(ComputationDomain *)>> mStopCallbacks;
};

template<class DomainType>
std::shared_ptr<DomainType> ComputationDomain::newSubDomain(bool prepend) {
  // Only Synchronous domains are allowed as subdomains
  assert(strcmp(typeid (DomainType).name(), "SynchronousDomain") == 0);
  auto newDomain = std::make_shared<DomainType>();
  if (newDomain) {
    mSubDomainList.push_back({newDomain, prepend});
  }
  return newDomain;
}

}



#include "Gamma/Domain.h"
#include "al/core/app/al_WindowApp.hpp"
#include "al/core/io/al_ControlNav.hpp"
namespace al {

class GraphicsDomain : public AsynchronousDomain, public gam::Domain
{
public:

  bool initialize() override {
    bool ret = true;
    ret &= initializeSubdomains(true);
    glfw::init(app.is_verbose);
    ret &= glfwInit();

    if (app.is_verbose) std::cout << "Initialized GLFW " << glfwGetVersionString() << std::endl;
    glfwSetErrorCallback([](int code, const char* description){std::cout << "glfw error [" << code << "]: " << description << std::endl;});

    ret &= initializeSubdomains(false);
    callInitializeCallbacks();
    return ret;
  }

  bool start() override {
    app.startFPS(); // WindowApp (FPS)
    gam::Domain::spu(app.fps());
    app.create(app.is_verbose);
    preOnCreate();
    onCreate();
    callStartCallbacks();
    while (!app.shouldQuit()) {
      // to quit, call WindowApp::quit() or click close button of window,
      // or press ctrl + q
      preOnAnimate(app.dt_sec());
      onAnimate(app.dt_sec());
      preOnDraw();
      onDraw(app.mGraphics);
      postOnDraw();
      app.refresh();
      app.tickFPS();
    }
    return true;
  }

  bool stop() override {
    callStopCallbacks();
    onExit(); // user defined
    postOnExit();
    app.destroy();
    return true;
  }

  bool cleanup() override {
    callCleanupCallbacks();
    glfw::terminate(app.is_verbose);
    return true;
  }

  virtual void preOnCreate() {
    app.append(mNavControl);
    app.mGraphics.init();
  }

  // Virtual functions to override

//  void onKeyDown(Keyboard const& k) {}
//  void onKeyUp(Keyboard const& k) {}
//  void onMouseDown(Mouse const& m) {}
//  void onMouseUp(Mouse const& m) {}
//  void onMouseDrag(Mouse const& m) {}
//  void onMouseMove(Mouse const& m) {}
//  void onResize(int w, int h) {}
//  void onVisibility(bool v) {}

  std::function<void(void)> onInit = [](){};
  std::function<void(void)> onCreate = [](){};
  std::function<void(double dt)> onAnimate = [](double){};
  std::function<void(Graphics &)> onDraw = [](Graphics &){};
  std::function<void()> onExit = [](){};


  virtual void preOnAnimate(double dt) {
      mNav.smooth(std::pow(0.0001, dt));
      mNav.step(dt * app.fps());
  }

  virtual void preOnDraw() {
      app.mGraphics.framebuffer(FBO::DEFAULT);
      app.mGraphics.viewport(0, 0, app.fbWidth(), app.fbHeight());
      app.mGraphics.resetMatrixStack();
      app.mGraphics.camera(mView);
      app.mGraphics.color(1, 1, 1);
  }

  virtual void postOnDraw() {
    //
  }

  virtual void postOnExit() {
    //
  }

private:
  WindowApp app;
  Nav mNav; // is a Pose itself and also handles manipulation of pose
  Viewpoint mView {mNav.transformed()};  // Pose with Lens and acts as camera
  NavInputControl mNavControl {mNav}; // interaction with keyboard and mouse
};
}


#include "al/core/io/al_AudioIO.hpp"
#include "Gamma/Domain.h"

namespace  al
{

class AudioDomain : public AsynchronousDomain, public gam::Domain
{
public:
  AudioIO& audioIO(){ return mAudioIO; }
  const AudioIO& audioIO() const { return mAudioIO; }

  bool initialize() override {
    callInitializeCallbacks();
    return true;
  }

  bool start() override {
    bool ret = true;
    ret &= audioIO().open();
    gam::Domain::spu(audioIO().framesPerSecond());
    ret &= audioIO().start();
    return ret;
  }

  bool stop() override {
    bool ret = true;
    ret &= audioIO().stop();
    ret &= audioIO().close();
    return true;
  }

  bool cleanup() override {
    callCleanupCallbacks();
    return true;
  }

  static void AppAudioCB(AudioIOData& io){
    AudioDomain& app = io.user<AudioDomain>();
    io.frame(0);
    app.onSound(app.audioIO());
  }

  // initialize audio with default values from default device
  enum AudioIOConfig : unsigned int {
    IN_ONLY = 0b1,
    OUT_ONLY = 0b10,
    IN_AND_OUT = 0b11
  };

  void configure(double audioRate, int audioBlockSize,
      int audioOutputs, int audioInputs,
      int device) {
    AudioDevice dev = AudioDevice(device);
    configure(dev, audioRate, audioBlockSize,
              audioOutputs, audioInputs);
  }

  void configure(AudioDevice &dev,
                 double audioRate, int audioBlockSize,
                 int audioOutputs, int audioInputs)
  {

    audioIO().init(AudioDomain::AppAudioCB, this, audioBlockSize, audioRate, audioOutputs, audioInputs);
    audioIO().device(dev);
    // mAudioIO.device() resets the channels to the device default number
    audioIO().channelsIn(audioInputs);
    audioIO().channelsOut(audioOutputs);
  }

  void configure(AudioIOConfig config = OUT_ONLY) {
    bool use_in = (config & IN_ONLY) ? true : false;
    bool use_out = (config & OUT_ONLY) ? true : false;
    audioIO().initWithDefaults(AppAudioCB, this, use_out, use_in);
  }


  std::function<void(AudioIOData &io)> onSound = [](AudioIOData &){};

private:

  AudioIO mAudioIO;
};

}

#include "al/core/protocol/al_OSC.hpp"
#include "al/util/ui/al_ParameterServer.hpp"
#include "al/util/al_FlowAppParameters.hpp"

namespace al {

class OSCDomain: public AsynchronousDomain {
public:

  bool initialize() override {
    mHandler.mOscDomain = this;
    mParameterServer.registerOSCListener(&mHandler); // Have the parameter server pass unhandled messages to this app's onMessage virtual function
    return true;
  }

  bool configure(uint16_t port, std::string address = "") {
    mParameterServer.configure(port, address);
    return true;
  }

  bool start() override {
    bool ret = true;
    ret &= mParameterServer.listen();
    return ret;
  }

  bool stop() override {
    bool ret = true;
    mParameterServer.stopServer();
    return ret;
  }

  bool cleanup() override { return true; }


  ParameterServer& parameterServer() { return mParameterServer; }
  ParameterServer const& parameterServer() const { return mParameterServer; }

  // PacketHandler
  std::function<void(osc::Message&)> onMessage = [](osc::Message &m){std::cout << "Received unhandled message." <<std::endl; m.print();};

private:

  class Handler: public osc::PacketHandler {
  public:
    OSCDomain *mOscDomain;
    void onMessage(osc::Message &m) {
      this->onMessage(m);
    }
  } mHandler;
    ParameterServer mParameterServer {"0.0.0.0", 9010, false};
};
}


 // ----------------------------------------------------------------
// The AL_EXT_OPENVR macro is set if OpenVR is found.
#ifdef AL_EXT_OPENVR
#include "al_ext/openvr/al_OpenVRWrapper.hpp"
#endif

namespace al {


class OpenVRDomain: public SynchronousDomain {
public:

  bool initialize() override {
#ifdef AL_EXT_OPENVR
    // Initialize openVR in onCreate. A graphics context is needed.
    if(!mOpenVR.init()) {
      return false;
//      std::cerr << "ERROR: OpenVR init returned error" << std::endl;
    }
//    std::cerr << "Not building wiht OpenVR support" << std::endl;
    return true;
#endif
    return false;
  }

  bool tick() override {
#ifdef AL_EXT_OPENVR
        // Update traking and controller data;
        mOpenVR.update();

        //openVR draw.
        // Draw in onAnimate, to make sure drawing happens only once per frame
        // Pass a function that takes Graphics &g argument
//        mOpenVR.draw(std::bind(&OpenVRDomain::drawScene, this, std::placeholders::_1), mGraphics);
#endif
        return true;
  }

  bool cleanup() override { return true; }

  std::function<void(Graphics &)> drawScene = [](Graphics &g){ };

private:
#ifdef AL_EXT_OPENVR
    al::OpenVRWrapper mOpenVR;
#endif
};

}

namespace  al
{

class BaseCompositeApp {
public:

  BaseCompositeApp() {
    mOSCDomain = newDomain<OSCDomain>();

    mAudioDomain = newDomain<AudioDomain>();
    mAudioDomain->configure();

    mGraphicsDomain = newDomain<GraphicsDomain>();
    //FIXME fix openVR domain
//    mGraphicsDomain->newSubDomain<OpenVRDomain>();
  }


  template<class DomainType>
  std::shared_ptr<DomainType> newDomain() {
    auto newDomain = std::make_shared<DomainType>();
    mDomainList.push_back(newDomain);
    return newDomain;
  }

  virtual void onInit () {}
  virtual void onCreate() {}
  virtual void onDraw(Graphics &g) {}
  virtual void onSound(AudioIOData &io) {}
  virtual void onMessage(osc::Message &m) {}

  void start();

  std::shared_ptr<OSCDomain> oscDomain() {return mOSCDomain;}
  std::shared_ptr<AudioDomain> audioDomain() { return mAudioDomain;}
  std::shared_ptr<GraphicsDomain> graphicsDomain() { return mGraphicsDomain;}

private:

  std::shared_ptr<OSCDomain> mOSCDomain;
  std::shared_ptr<AudioDomain> mAudioDomain;
  std::shared_ptr<GraphicsDomain> mGraphicsDomain;

  std::vector<std::shared_ptr<AsynchronousDomain>> mDomainList;
  std::stack<std::shared_ptr<AsynchronousDomain>> mRunningDomains;
};

} // namespace al

#endif // COMPUTATIONDOMAIN_H