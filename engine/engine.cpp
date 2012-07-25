//-------------------------------------
#include "logger.h"
#include "engine.h"
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
		//TODO all gui updates
		//camera
        mGraphicsEngine->render();

		unsigned long elapsedTime = mGraphicsEngine->getElapsedTime();

		float 	mSimulationTimeStep = 1000.0f / 60.0f;	
		float	timeToSimulate = elapsedTime;

		while(timeToSimulate > mSimulationTimeStep) {
			timeToSimulate -= mSimulationTimeStep;
			mPhysicsEngine->simulate(mSimulationTimeStep / 1000.0f);
			//TODO all physics updates
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

	/*
	char *path, *newpath;
	path=Py_GetPath(); 
	newpath=strcat(path, ":."); // or ";.", possibly 
	PySys_SetPath(newpath); 
	//PySys_SetPath("/home/sinan/code/cpp/07_boost-python-examples/01_embedding/");
	free(newpath);
	*/
	Logger::debug("setup python done");
}

void    Engine::runPython(){
	Logger::debug("run python file");
	try {

		object main_module((
			handle<>(borrowed(PyImport_AddModule("__main__")))
			));
		object main_namespace = main_module.attr("__dict__");

		FILE *file = fopen("test.py","r+");
		if(file) {
			Logger::debug("reading python file");
			handle<> ignored(( 
				PyRun_File(file,"test.py",
					 Py_file_input,
					 main_namespace.ptr(),
					 main_namespace.ptr() )
				));
			fclose(file);
		}
    } catch( error_already_set ) {
        PyErr_Print();
    }
}

void    Engine::guiUpdates() {
	std::set<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		(*mIterator)->guiUpdate();
	}
}

void    Engine::physicUpdates() {
	std::set<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		(*mIterator)->physicUpdate();
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
		engineObject->setShape(new GraphicsBox(mEngine->getGraphicsEngine()));
	}
}

