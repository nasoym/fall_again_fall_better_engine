//-------------------------------------
#include "logger.h"
#include "engine.h"
#include "engine.py.h"
#include "engine_gui_shape.h"
#include "box_graphic.h"
//-------------------------------------
Engine::Engine() :
	mLoopRendering(true) {
    Logger::debug(format("creating engine: %p ") % this);
    setup();
	setupPython();
}

Engine::~Engine(){
    Logger::debug(format("deleting engine: %p ") % this);
	closePython();
    close();

}

void Engine::setup(){
    mGraphicsEngine = new GraphicsEngine();
    mPhysicsEngine = new PhysicsEngine();

	mGraphicsEngine->addKeyboardListener(new EngineKeyListener(this));
}

void Engine::run(){
    while(mLoopRendering) {
        mGraphicsEngine->processOIS();
        if (mGraphicsEngine->inputExit()) {
            break;
        }
		//TODO camera
		guiUpdates();
        mGraphicsEngine->render();

		unsigned long elapsedTime = mGraphicsEngine->getElapsedTime();

		float 	mSimulationTimeStep = 1000.0f / 60.0f;	
		float	timeToSimulate = elapsedTime;

		while(timeToSimulate > mSimulationTimeStep) {
			timeToSimulate -= mSimulationTimeStep;
			physicUpdates();
			mPhysicsEngine->simulate(mSimulationTimeStep / 1000.0f);
		}

    }
}

void	Engine::closePython() {
	Logger::debug("close python");
	Py_Finalize();
}

void	Engine::setupPython() {
	Logger::debug("setup python");
	Py_Initialize();
	object main_module(( handle<>(borrowed(PyImport_AddModule("__main__"))) ));
	main_namespace = main_module.attr("__dict__");
	PyImport_AppendInittab("EngineModule", &initEngineModule ); 
	object engineModule(( handle<>(borrowed(PyImport_ImportModule("EngineModule"))) ));
	main_namespace["EngineModule"] = engineModule;
	main_namespace["Engine"] = ptr(this);

	runPython();
}

void    Engine::runPython(){
	Logger::debug("run python file");
	try {
        PyObject* file = PyFile_FromString("main.py", "r+");
        PyRun_File(PyFile_AsFile(file), "main.py", Py_file_input, 
			main_namespace.ptr(), main_namespace.ptr()
			);

		pyFunctionKeyPressed = main_namespace["keyPressed"];
		pyFunctionKeyReleased = main_namespace["keyReleased"];
		pyFunctionInit = main_namespace["init"];
		pyFunctionGuiUpdate = main_namespace["guiUpdate"];
		pyFunctionPhysicUpdate = main_namespace["physicUpdate"];

		pyFunctionInit();

    } catch( error_already_set ) {
		Logger::debug("python error");
        PyErr_Print();
    }
}

void	Engine::callPythonKeyPressed(const OIS::KeyEvent& evt ) {
	std::map<OIS::KeyCode,Keys>::iterator keyListIterator;
	keyListIterator = keyList.find(evt.key);
    if (keyListIterator != keyList.end()) {
		try {
			pyFunctionKeyPressed(keyListIterator->second);
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

void	Engine::callPythonKeyReleased(const OIS::KeyEvent& evt ) {
	std::map<OIS::KeyCode,Keys>::iterator keyListIterator;
	keyListIterator = keyList.find(evt.key);
    if (keyListIterator != keyList.end()) {
		try {
			pyFunctionKeyReleased(keyListIterator->second);
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

void	Engine::callPythonKeyGuiUpdate() {
	try {
		pyFunctionGuiUpdate();
	} catch( error_already_set ) {
		Logger::debug("Python error");
		PyErr_Print();
	}
}

void	Engine::callPythonKeyPysicUpdate() {
	try {
		pyFunctionPhysicUpdate();
	} catch( error_already_set ) {
		Logger::debug("Python error");
		PyErr_Print();
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
		(*mIterator)->physicUpdate();
	}
	callPythonKeyPysicUpdate();
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
	/*
	if (evt.key == OIS::KC_1) {
		//new GraphicsBox(mGraphicsEngine);
		EngineGuiShape* engineObject = new EngineGuiShape(mEngine);
		engineObject->setShape(new GraphicsBox(mEngine->getGraphicsEngine()));
	}
	*/
	mEngine->callPythonKeyPressed(evt);
}

void EngineKeyListener::keyReleased(const OIS::KeyEvent& evt){
	mEngine->callPythonKeyReleased(evt);
}

EngineObject*	Engine::createGuiBox(){
	EngineGuiShape* engineObject = new EngineGuiShape(this);
	engineObject->setShape(new GraphicsBox(getGraphicsEngine()));
	return engineObject;
}

