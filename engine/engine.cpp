//-------------------------------------
#include "logger.h"
#include "engine.h"
#include "engine_gui_shape.h"
//-------------------------------------
Engine::Engine() :
	mLoopRendering(true) {
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

	mGraphicsEngine->addKeyboardListener(new EngineKeyListener(this));
}

void Engine::run(){
    //while(true) {
    while(mLoopRendering) {
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

void    Engine::deleteAllObjects() {
	std::set<EngineObject*>	objectsCopy=std::set<EngineObject*>(mObjects);
	mObjects.clear();
	std::set<EngineObject*>::iterator  mIterator;
	for (mIterator = objectsCopy.begin(); 
		mIterator != objectsCopy.end(); ++mIterator) {
		delete (*mIterator);
	}
}

void    Engine::deleteObject(EngineObject* object) {
	std::set<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		if ( (*mIterator) == object ){
			mObjects.erase( mIterator);
			delete (*mIterator);
			break;
		}
	}
}

int     Engine::howManyObjects() {
	return mObjects.size();
}

void    Engine::addObject(EngineObject* object){
	mObjects.insert(object);
}

void EngineKeyListener::keyPressed(const OIS::KeyEvent& evt){
	if (evt.key == OIS::KC_ESCAPE) {
		Logger::debug("esc pressed");
		mEngine->quit();
	}
	if (evt.key == OIS::KC_1) {
		//new GraphicsBox(mGraphicsEngine);
		EngineGuiShape* engineObject = new EngineGuiShape(mEngine);
		engineObject->setShape(new GraphicsBox(mEngine->mGraphicsEngine));
	}
}

