#include "logger.h"
#include "engine.h"
#include "engine.py.h"

#include "box_graphic.h"

#include "engine_gui_shape.h"
#include "engine_spacecage.h"

Engine::Engine() :
	mLoopRendering(true),
	mPythonInitialized(false)
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

void Engine::run(){
    while(mLoopRendering) {
        mGraphicsEngine->processOIS();
        if (mGraphicsEngine->inputExit()) {
            break;
        }
		//TODO camera pos/rot from node
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
	mPythonInitialized = false;
}

void	Engine::setupPython() {
	Logger::debug("setup python");
	Py_Initialize();
	//printf("Py_GetPath: %s\n",Py_GetPath());
	object main_module(( handle<>(borrowed(PyImport_AddModule("__main__"))) ));
	main_namespace = main_module.attr("__dict__");
	PyImport_AppendInittab("EngineModule", &initEngineModule ); 
	object engineModule(( handle<>(borrowed(PyImport_ImportModule("EngineModule"))) ));
	main_namespace["EngineModule"] = engineModule;
	main_namespace["Engine"] = ptr(this);

	mPythonInitialized = true;
}

void    Engine::runPython(){
	if (!mPythonInitialized) {
		setupPython();
	}
	Logger::debug("run python file");
	try {
        PyObject* file = PyFile_FromString("script.py", "r+");
        PyRun_File(PyFile_AsFile(file), "script.py", Py_file_input, 
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
	if (mPythonInitialized) {
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
}

void	Engine::callPythonKeyReleased(const OIS::KeyEvent& evt ) {
	if (mPythonInitialized) {
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
}

void	Engine::callPythonKeyGuiUpdate() {
	if (mPythonInitialized) {
		try {
			pyFunctionGuiUpdate();
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

void	Engine::callPythonKeyPysicUpdate() {
	if (mPythonInitialized) {
		try {
			pyFunctionPhysicUpdate();
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
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

void Engine::keyPressed(const OIS::KeyEvent& evt){
	if (evt.key == OIS::KC_ESCAPE) {
		Logger::debug("esc pressed");
		quit();
	}
	callPythonKeyPressed(evt);
}

void Engine::keyReleased(const OIS::KeyEvent& evt){
	callPythonKeyReleased(evt);
}

void	Engine::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
	if (id == OIS::MB_Left)  {
		pyFunctionKeyPressed(K_MLEFT);
	//} else if (id == OIS::MB_RIGHT) {
	//	pyFunctionKeyPressed(K_MRIGHT);
	}
}

void	Engine::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
	if (id == OIS::MB_Left)  {
		pyFunctionKeyReleased(K_MLEFT);
	//} else if (id == OIS::MB_RIGHT) {
//		pyFunctionKeyReleased(K_MRIGHT);
	}
}

EngineObject*	Engine::createGuiBox(){
	EngineGuiShape* engineObject = new EngineGuiShape(this);
	engineObject->setShape(new GraphicsBox(getGraphicsEngine()));
	return engineObject;
}

EngineObject*	Engine::createPhysicBox(){
	return 0;
}

EngineObject*	Engine::createSpaceCage(){
	EngineSpaceCage* spaceCage = new EngineSpaceCage(this);
	spaceCage->setShape(new GraphicsBox(getGraphicsEngine()));
	spaceCage->setSize(Vec3(10,1,10));
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

	
