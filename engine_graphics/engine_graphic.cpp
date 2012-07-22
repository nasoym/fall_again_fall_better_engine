//-------------------------------------
#include "logger.h"
#include "engine_graphic.h"
//-------------------------------------
GraphicsEngine::GraphicsEngine() {
    Logger::debug(format("creating graphics engine: %p ") % this);
    setup();
}

GraphicsEngine::~GraphicsEngine(){
    Logger::debug(format("deleting graphics engine: %p ") % this);
    close();
}

void GraphicsEngine::setup(){
	//root = new Root("","");
	root = new Root();
	root->showConfigDialog();
	root->initialise(true);
	//root->startRendering();
}

void GraphicsEngine::close(){
    root->shutdown();
}

void GraphicsEngine::render(){
    Logger::debug(format("render graphics engine: %p ") % this);
    root->renderOneFrame();
}


