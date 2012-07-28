#include "logger.h"
#include "engine.h"
//#include "engine.py.h"

#include "box_graphic.h"

#include "engine_gui_shape.h"
#include "engine_spacecage.h"
#include "engine_body.h"
#include "engine_joint.h"

Engine::Engine() :
	mLoopRendering(true),
	mPythonInitialized(false),
	mSimulationTime(0)
	{
    Logger::debug(format("creating engine: %p ") % this);
    setup();
}

Engine::~Engine(){
    Logger::debug(format("deleting engine: %p ") % this);
	if (mPythonInitialized) {
		closePython();
	}
    close();
}

void Engine::setup(){
    mGraphicsEngine = new GraphicsEngine();
	mGraphicsEngine->addKeyboardListener(this);

    mPhysicsEngine = new PhysicsEngine();
}

void Engine::close(){
    delete mPhysicsEngine;
    delete mGraphicsEngine;
}

void Engine::run(){
    while(mLoopRendering) {
		step();
    }
}

void	Engine::step() {
	mGraphicsEngine->processOIS();
	if (mGraphicsEngine->inputExit()) {
		quit();
	}
	updateKeysDown();
	//TODO camera pos/rot from node
	guiUpdates();
	mGraphicsEngine->render();
	//printf("o");

	unsigned long elapsedTime = mGraphicsEngine->getElapsedTime();
    //Logger::debug(format("%1%") % elapsedTime);

	float 	mSimulationTimeStep = 1000.0f / 60.0f;	
	//float	timeToSimulate = elapsedTime;
	mSimulationTime += elapsedTime;

	while(mSimulationTime > mSimulationTimeStep) {
		//Logger::debug("p");
		//printf("+");
		mSimulationTime -= mSimulationTimeStep;
		mPhysicsEngine->simulate(mSimulationTimeStep / 1000.0f);
		physicUpdates();
	}

}

void    Engine::guiUpdates() {
	std::set<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		(*mIterator)->guiUpdate();
	}
	callPythonKeyGuiUpdate();
}

void    Engine::physicUpdates() {
	std::set<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		//printf(".");
		(*mIterator)->physicUpdate();
	}
	callPythonKeyPysicUpdate();
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

void    Engine::addObject(EngineObject* object){
	mObjects.insert(object);
}

int     Engine::howManyObjects() {
	return mObjects.size();
}

EngineObject*	Engine::createGuiBox(){
	EngineGuiShape* engineObject = new EngineGuiShape(this);
	engineObject->setShape(new GraphicsBox(getGraphicsEngine()));
	engineObject->setSize(Vec3(10,1,10));
	engineObject->setPosition(Vec3(0,-0.5,0));
	return engineObject;
}

EngineObject*	Engine::createPhysicBox(){
	EngineBody* engineObject = new EngineBody(this);
	engineObject->setShape(new GraphicsBox(getGraphicsEngine()));
	engineObject->setSize(Vec3(6,3,3));
	engineObject->setPosition(Vec3(0,150,0));
	return engineObject;
}

EngineObject*	Engine::createJoint(EngineObject* obj1,EngineObject* obj2){
	if (obj1->isBody() && obj2->isBody() ) {
		EngineJoint* engineObject = new EngineJoint(this,obj1->isBody(),obj2->isBody());
		return engineObject;
	}
	return 0;
}

EngineObject*	Engine::createSpaceCage(){
	EngineSpaceCage* spaceCage = new EngineSpaceCage(this);
	spaceCage->setShape(new GraphicsBox(getGraphicsEngine()));
	spaceCage->setSize(Vec3(200,1,200));
	spaceCage->setPosition(Vec3(0,-0.5,0));
	return spaceCage;
}

void			Engine::setCameraPosition(Vec3 & vec){
	getGraphicsEngine()->setCameraPosition(vec.toOgre());
}

void			Engine::setCameraOrientation(Quat & quat){
	getGraphicsEngine()->setCameraOrientation(quat.toOgre());
}

Vec3			Engine::getCameraPosition(){
	return Vec3(getGraphicsEngine()->getCameraPosition());
}

Quat			Engine::getCameraOrientation(){
	return Quat(getGraphicsEngine()->getCameraOrientation());
}

	
