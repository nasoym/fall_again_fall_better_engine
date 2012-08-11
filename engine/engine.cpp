#include "logger.h"
#include "engine.h"
#include "physic_engine.h"
#include "engine_object.h"

#include "OgreRTShaderSystem.h"

Engine::Engine() :
	mLoopRendering(true),
	mPythonInitialized(false),
	mSimulationTime(0),
	mTimingFactor(1.0f),
    mExit(false),
    mInputManager(0),
	mCurrentTime(0),
	mLastTime(0),
	mPhysicPaused(false),
	mUseFirstRenderer(true)
	{
    Logger::debug(format("creating engine: %p ") % this);
    setupPhysics();
    setup();
	setupStereo();
	//setupSSAO();
    setupOIS();
    setupWindowEventListener();
}

Engine::~Engine(){
    Logger::debug(format("deleting engine: %p ") % this);
	if (mPythonInitialized) {
		closePython();
	}
    closeWindowEventListener();
    closeOIS();
	closeStereo();
    close();
    closePhysics();
}

void	Engine::setupSSAO(){
		/*
        mCompositorNames.push_back("SSAO/HemisphereMC");
        mCompositorNames.push_back("SSAO/Volumetric");
        mCompositorNames.push_back("SSAO/HorizonBased");
        mCompositorNames.push_back("SSAO/Crytek");
        mCompositorNames.push_back("SSAO/CreaseShading");
        mCompositorNames.push_back("SSAO/UnsharpMask");
        mCompositorNames.push_back("SSAO/ShowDepth");
        mCompositorNames.push_back("SSAO/ShowNormals");
        mCompositorNames.push_back("SSAO/ShowViewPos");
        
        mPostNames.push_back("SSAO/Post/NoFilter");
        mPostNames.push_back("SSAO/Post/CrossBilateralFilter");
        mPostNames.push_back("SSAO/Post/SmartBoxFilter");
        mPostNames.push_back("SSAO/Post/BoxFilter");
		*/
		
        if (CompositorManager::getSingleton().addCompositor(mViewport, "SSAO/GBuffer")) {
            CompositorManager::getSingleton().setCompositorEnabled(mViewport, "SSAO/GBuffer", true);
        } else {
            Logger::debug("Sample_SSAO: Failed to add GBuffer compositor");
        } 

		if (CompositorManager::getSingleton().addCompositor(mViewport, "SSAO/HemisphereMC")) {
			CompositorManager::getSingleton().setCompositorEnabled(mViewport, "SSAO/HemisphereMC", true);
		} else {
			Logger::debug("Sample_SSAO: Failed to add compositor: ");
		}
        
		if (CompositorManager::getSingleton().addCompositor(mViewport, "SSAO/Post/NoFilter")) {
			CompositorManager::getSingleton().setCompositorEnabled(mViewport, "SSAO/Post/NoFilter", false);
		} else {
			Logger::debug("Sample_SSAO: Failed to add Post");
		}

		/*
		Ogre::Viewport* mainVP = mCamera->getViewport();
		//const Ogre::String& curMaterialScheme = mainVP->getMaterialScheme();
		if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false)
		{
			mainVP->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
		}
		*/
}

void Engine::setupPhysics(){
    mPhysicsEngine = new PhysicsEngine();
}

void Engine::closePhysics(){
    delete mPhysicsEngine;
}

void Engine::run(){
    while(mLoopRendering) {
		step();
    }
}

void Engine::physicPauseToggle() {
	if (mPhysicPaused) {
		mPhysicPaused = false;
	} else {
		mPhysicPaused = true;
	}
}

void	Engine::step() {
	processOIS();
	if (inputExit()) {
		quit();
	}
	updateKeysDown();
	//TODO camera pos/rot from node
	guiUpdates();
	render();
	//printf("o");

	unsigned long elapsedTime = getElapsedTime();
    //Logger::debug(format("%1%") % elapsedTime);

	//float 	mSimulationTimeStep = 1000.0f / 60.0f;	
	float 	mSimulationTimeStep = 2.0f;	
	//float	timeToSimulate = elapsedTime;
	mSimulationTime += elapsedTime;
	float	timeToSimulate = mSimulationTimeStep / 1000.0f;
	timeToSimulate *= getTimingFactor();

	while(mSimulationTime > mSimulationTimeStep) {
		//Logger::debug("p");
		//printf("+");
		mSimulationTime -= mSimulationTimeStep;
		//mPhysicsEngine->simulate(mSimulationTimeStep / 1000.0f);

		if (!mPhysicPaused) {
			//mPhysicsEngine->simulate(timeToSimulate);
			simulatePhysics(timeToSimulate);
		}
		physicUpdates();
	}

}

void	Engine::simulatePhysics(float time) {
	mPhysicsEngine->simulate(time);
}

void    Engine::guiUpdates() {
	std::vector<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		(*mIterator)->guiUpdate();
	}
	callPythonKeyGuiUpdate();
}

void    Engine::physicUpdates() {
	std::vector<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		//printf(".");
		(*mIterator)->physicUpdate();
	}
	callPythonKeyPysicUpdate();
}

void    Engine::deleteAllObjects() {
	std::vector<EngineObject*>	objectsCopy=std::vector<EngineObject*>(mObjects);
	mObjects.clear();
	std::vector<EngineObject*>::iterator  mIterator;
	for (mIterator = objectsCopy.begin(); 
		mIterator != objectsCopy.end(); ++mIterator) {
		delete (*mIterator);
	}
}

void    Engine::deleteObject(EngineObject* object) {
	std::vector<EngineObject*>::iterator  mIterator;
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
	mObjects.push_back(object);
}

int     Engine::howManyObjects() {
	return mObjects.size();
}

EngineObject* Engine::getObject(int index){
	return mObjects[index];
}

EngineObject* Engine::getFromUuid(std::string uuidToFind){
	std::vector<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		if( (*mIterator)->getUuid().isEqual(uuidToFind) ) {
			return (*mIterator);
		}
	}
	return 0;
}

void Engine::setup(){
    mLogger = new Ogre::LogManager();
    mLogger->createLog("log.log", true, false,true);

	//root = new Root("","");
	mRoot = new Root();
    setupResources();

	if (mUseFirstRenderer){ 
		RenderSystemList rlist = mRoot->getAvailableRenderers();
		RenderSystemList::iterator it = rlist.begin();
		while (it !=rlist.end()) {
			RenderSystem *rSys = *(it++);
			rSys->setConfigOption("Full Screen", "No");
			rSys->setConfigOption("Video Mode", "1024 x 768 @ 32-bit colour");
			mRoot->setRenderSystem(rSys);
			break;
		}
	} else {
		mRoot->showConfigDialog();
	}

	mWindow = mRoot->initialise(true);
	//mRoot->initialise(false);
	//mWindow = mRoot->createRenderWindow("main window",400,400,false);

    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");
    mSceneMgr->setAmbientLight(ColourValue(0.2,0.2,0.2));

    mRootSceneNode = mSceneMgr->getRootSceneNode();
    mDebugSceneNode = mRootSceneNode->createChildSceneNode();
    mFinalSceneNode = mRootSceneNode->createChildSceneNode();

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mCamera = mSceneMgr->createCamera("PlayerCam");
    // Position it at 500 in Z direction
    mCamera->setPosition(Vector3(0,0,500));
    // Look back along -Z
    mCamera->lookAt(Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);
	//mCamera->setFOVy(Radian(Degree(45).valueRadians())); // i.e. 60deg * 1.3.. maya and ogre use fovX and fovY
	//mCamera->setFarClipDistance(400);
	//mCamera->setNearClipDistance(0.1);

    // Create one viewport, entire window
    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.5,0.3,0.2));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio( Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

    Light * light = mSceneMgr->createLight("MainLight");
	light->setType(Light::LT_POINT);
    light->setPosition(200,200,200);
	light->setDiffuseColour(0.2,0.2,0.2);
	light->setSpecularColour(0.5,0.5,0.5);

    Light * light2 = mSceneMgr->createLight("MainLight2");
	light2->setType(Light::LT_POINT);
    light2->setPosition(-200,200,-200);
	light2->setDiffuseColour(0.2,0.2,0.2);
	light2->setSpecularColour(0.5,0.5,0.5);

	/*
    //Entity *ent = mSceneMgr->createEntity("head","cube.mesh");
    Entity *ent = mSceneMgr->createEntity("head","Prefab_Cube");
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	*/


}

void Engine::close(){
	OGRE_DELETE mRoot;
}

void Engine::render(){
    WindowEventUtilities::messagePump();
    mRoot->renderOneFrame();
    //mRoot->startRendering();
}

void Engine::setupResources() {
    ConfigFile cf;
    cf.load("resources.cfg");

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

void 		Engine::setupStereo() {
	//mStereoManager.init(mViewport, NULL, "stereo.cfg");
}

void 		Engine::closeStereo() {
}


void			Engine::setCameraPosition(Vec3 & vec){
	getCamera()->setPosition(vec.toOgre());
}

void			Engine::setCameraOrientation(Quat & quat){
	getCamera()->setOrientation(quat.toOgre());
}

Vec3			Engine::getCameraPosition(){
	return Vec3(getCamera()->getPosition());
}

Quat			Engine::getCameraOrientation(){
	return Quat(getCamera()->getOrientation());
}

unsigned long Engine::getElapsedTime() {
	unsigned long timeDifference = 0;

	mCurrentTime = mTimer.getMilliseconds();
	timeDifference = mCurrentTime - mLastTime;
	mLastTime = mCurrentTime;
    //Logger::debug(format("%1% %2%") % mCurrentTime % timeDifference);
	return timeDifference;
}

void Engine::setupOIS() {
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    bool bufferedKeys = true;
    bool bufferedMouse = true;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_FOREGROUND"));
    pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_NONEXCLUSIVE"));

    pl.insert(std::make_pair("w32_keyboard", "DISCL_FOREGROUND"));
    pl.insert(std::make_pair("w32_keyboard", "DISCL_NONEXCLUSIVE"));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, bufferedKeys ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, bufferedMouse ));

    mKeyboard->setEventCallback(this);
    mMouse->setEventCallback(this);

    windowResized(mWindow); 
}

void Engine::closeOIS() {
    if( mInputManager ) {
        mInputManager->destroyInputObject( mMouse );
        mInputManager->destroyInputObject( mKeyboard );

        OIS::InputManager::destroyInputSystem(mInputManager);
        mInputManager = 0;
    }
}

void Engine::processOIS() {
    if( mInputManager ) {
        mKeyboard->capture();
        mMouse->capture();
        if( !mKeyboard->buffered() ) {
            if( mKeyboard->isKeyDown(OIS::KC_ESCAPE) || mKeyboard->isKeyDown(OIS::KC_Q) ) {
                mExit = true;
            }
        }

        if( !mMouse->buffered() ) {
            const OIS::MouseState &ms = mMouse->getMouseState();
            if( ms.buttonDown( OIS::MB_Right ) ) {
                ms.X.rel;
                ms.Y.rel;
            } else {
            }
        }
    }
}

bool    Engine::inputExit() {
    return mExit;
}

void    Engine::setupWindowEventListener() {
    WindowEventUtilities::addWindowEventListener(mWindow, this);
}
void    Engine::closeWindowEventListener() {
    WindowEventUtilities::removeWindowEventListener(mWindow, this);
}


//Adjust mouse clipping area
void Engine::windowResized(RenderWindow* rw) {
    //Logger::debug("windowResized");
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;

    mCamera->setAspectRatio( Real(width) / Real(height));
}

void Engine::windowMoved(RenderWindow* rw) {
    //Logger::debug("windowMoved");
}

bool windowClosing(RenderWindow* rw) {
    //Logger::debug("windowClosing");
    return true;
}

void Engine::windowClosed(RenderWindow* rw) {
    //Logger::debug("windowClosed");
    mExit = true;
}

void Engine::windowFocusChange(RenderWindow* rw) {
    //Logger::debug("windowFocusChange");
}

