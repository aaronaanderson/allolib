#include "al_App.hpp"

using namespace al;

void BaseCompositeApp::start() {

  initializeDomains();

  for (auto &domain: mDomainList) {
    mRunningDomains.push(domain);
    if (!domain->start()) {
      std::cerr << "ERROR starting domain " << std::endl;
    }
  }

  while (mRunningDomains.size() > 0 ) {

    if (!mRunningDomains.top()->stop()) {
      std::cerr << "ERROR stopping domain " << std::endl;
    }
    mRunningDomains.pop();
  }

  for (auto &domain: mDomainList) {
    if (!domain->cleanup()) {
      std::cerr << "ERROR cleaning up domain " << std::endl;
    }
  }
  onExit();
}

void BaseCompositeApp::initializeDomains() {
  for (auto domain: mDomainList) {
    if (strcmp(typeid(*domain).name(), typeid(OpenGLGraphicsDomain).name()) == 0) {
      dynamic_cast<OpenGLGraphicsDomain *>(domain.get())->onInit = std::bind(&BaseCompositeApp::onInit, this);
      dynamic_cast<OpenGLGraphicsDomain *>(domain.get())->onCreate = std::bind(&BaseCompositeApp::onCreate, this);
      dynamic_cast<OpenGLGraphicsDomain *>(domain.get())->onDraw = std::bind(&BaseCompositeApp::onDraw, this, std::placeholders::_1);
      mSimulationDomain->simulationFunction = std::bind(&BaseCompositeApp::onAnimate, this, std::placeholders::_1);
    } else if (strcmp(typeid(*domain).name(), typeid(AudioDomain).name()) == 0) {
      dynamic_cast<AudioDomain *>(domain.get())->onSound = std::bind(&BaseCompositeApp::onSound, this, std::placeholders::_1);
    } else if (strcmp(typeid(*domain).name(), typeid(OSCDomain).name()) == 0) {
      dynamic_cast<OSCDomain *>(domain.get())->onMessage = std::bind(&BaseCompositeApp::onMessage, this, std::placeholders::_1);
    } else {
      std::cout << "WARNING: Domain unknown for auto connection" << std::endl;
    }
    if (!domain->initialize()) {
      std::cerr << "ERROR initializing domain " << std::endl;
    }
  }
}
