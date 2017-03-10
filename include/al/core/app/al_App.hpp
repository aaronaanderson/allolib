#pragma once

#include "al/core/app/al_WindowApp.hpp"
#include "al/core/app/al_AudioApp.hpp"
#include "al/core/protocol/al_OSC.hpp"

#include "al/core/gl/al_Viewpoint.hpp"
#include "al/core/spatial/al_Pose.hpp"
#include "al/core/io/al_ControlNav.hpp"

namespace al {

// Unified app class: single window, audioIO,
//   single port osc recv and single port osc send, and al::Graphics
//   Also has a default nav and viewpoint for camera functionality

// TODO: better osc interface, add console app and graphics
class App: public WindowApp, public AudioApp, public osc::PacketHandler {
public:
  Nav _nav;
  Viewpoint _vp {_nav};
  NavInputControl _navInputControl {_nav};

  Viewpoint& viewpoint() { return _vp; }
  Nav& nav() { return _nav; }
  Lens& lens() { return _vp.lens(); }
  Viewport& viewport() { return _vp.viewport(); }

  virtual void onAnimate(double dt) {}
  virtual void onExit() {}

  // overrides WindowApp's start to also initiate AudioApp and etc.
  virtual void start() override {
    append(_navInputControl);

    open(); // WindowApp (calls glfw::init(); onInit(); create(); onCreate(); )
    startFPS(); // WindowApp (FPS)
    begin(); // AudioApp (only actually begins of `initAudio` was called before)
    while (!shouldQuit()) {
      // user can quit this loop with WindowApp::quit() or clicking close button
      // or with stdctrl class input (ctrl+q)

      // dt from WindowApp's FPS
      double dt_ = dt();
      _nav.step();
      // nav.step(dt_); TODO?! -> nav velocity value is hard coded!!!
      onAnimate(dt_);
      loop(); // WindowApp (onDraw)
      tickFPS(); // WindowApp (FPS)
    }
    onExit(); // user defined
    end(); // AudioApp
    close(); // WindowApp (calls onExit)
  }

  // PacketHandler
  virtual void onMessage(osc::Message& m) override {}
};

}