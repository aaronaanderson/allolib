#include "al_OpenVRDomain.hpp"

using namespace al;

bool OpenVRDomain::initialize(ComputationDomain *parent) {
#ifdef AL_EXT_OPENVR
  // A graphics context is needed to initialize OpenVR

  std::cerr << "Initializing OpenVR domain" << std::endl;
  if(!mOpenVR.init()) {
    std::cerr << "ERROR: OpenVR init returned error" << std::endl;
    return false;
  }
  if (dynamic_cast<OpenGLGraphicsDomain *>(parent)) {
    g = &dynamic_cast<OpenGLGraphicsDomain *>(parent)->graphics();
  }
  return true;
#else
  std::cerr << "Not building wiht OpenVR support" << std::endl;
  return false;
#endif
}

bool OpenVRDomain::tick() {
#ifdef AL_EXT_OPENVR
  // Update traking and controller data;
  mOpenVR.update();
  if (drawSceneFunc) {
    mOpenVR.draw(drawSceneFunc, *g);
  }
#endif
  return true;
}

bool OpenVRDomain::cleanup(ComputationDomain *parent) {
#ifdef AL_EXT_OPENVR
  mOpenVR.close();
#endif
  return true;
}
