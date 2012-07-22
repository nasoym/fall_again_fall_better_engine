//-------------------------------------
#include "logger.h"
#include "engine.h"
//-------------------------------------
Engine::Engine() {
    Logger::debug(format("creating engine: %p ") % this);
    setup();
}

Engine::~Engine(){
    Logger::debug(format("deleting engine: %p ") % this);
    close();
}

void Engine::setup(){
    mGraphicsEngine = new GraphicsEngine();
    mPhysicsEngine = new PhysicsEngine();
}

void Engine::run(){
    while(true) {
        mGraphicsEngine->processOIS();
        if (mGraphicsEngine->inputExit()) {
            break;
        }
        mGraphicsEngine->render();
        mPhysicsEngine->simulate(0.1f);
    }
}

void Engine::close(){
    delete mPhysicsEngine;
    delete mGraphicsEngine;
}

