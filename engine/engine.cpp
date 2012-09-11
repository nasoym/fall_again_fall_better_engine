#include "logger.h"
#include "engine.h"
#include "physic_engine.h"
#include "engine_object.h"
#include "engine_keys.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <vector>
#include <string>


Engine::Engine() :
	mLoopRendering(true),
	mPythonInitialized(false),
	mSimulationTime(0),
	mTimingFactor(1.0f),
    mExit(false),
    mInputManager(0),
	mCurrentTime(0),
	mLastTime(0),
	mTimeDifference(0),
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

    void Engine::setUniform(Ogre::String compositor, Ogre::String material, Ogre::String uniform, float value, bool setVisible, int position = -1)
    {
		Logger::debug("setUniform");
        // remove compositor first???
        CompositorManager::getSingleton().removeCompositor(mViewport, compositor);
        
        (static_cast<MaterialPtr>(MaterialManager::getSingleton().getByName(material)))->getTechnique(0)->
        getPass(0)->getFragmentProgramParameters()->setNamedConstant(uniform, value);
        
        // adding again
        CompositorManager::getSingleton().addCompositor(mViewport, compositor, position);
        CompositorManager::getSingleton().setCompositorEnabled(mViewport, compositor, setVisible);
    }


	
    void Engine::testsetup() {

		setUniform("SSAO/CreaseShading", "SSAO/CreaseShading", "cMinimumCrease", 0.2f, false, 1);
		setUniform("SSAO/CreaseShading", "SSAO/CreaseShading", "cBias", 1.0f, false, 1);
		setUniform("SSAO/CreaseShading", "SSAO/CreaseShading", "cAverager", 24, false, 1);
		setUniform("SSAO/CreaseShading", "SSAO/CreaseShading", "cRange", 1.0f, false, 1);
		setUniform("SSAO/CreaseShading", "SSAO/CreaseShading", "cKernelSize", 3.0f, false, 1);
        

		bool sampleInScreenSpace = true;
		//bool sampleInScreenSpace = false;
		setUniform("SSAO/Crytek", "SSAO/Crytek", "cSampleInScreenspace", sampleInScreenSpace, false, 1);
		setUniform("SSAO/HorizonBased", "SSAO/HorizonBased", "cSampleInScreenspace", sampleInScreenSpace, false, 1);
		setUniform("SSAO/HemisphereMC", "SSAO/HemisphereMC", "cSampleInScreenspace", sampleInScreenSpace, false, 1);
		setUniform("SSAO/Volumetric", "SSAO/Volumetric", "cSampleInScreenspace", sampleInScreenSpace, false, 1);
		CompositorManager::getSingleton().setCompositorEnabled(mViewport, mCurrentCompositor, true);

		float sampleInScreenSpaceLengthPercentage = 20.0f/100.0f;
		setUniform("SSAO/Crytek", "SSAO/Crytek", "cSampleLengthScreenSpace", sampleInScreenSpaceLengthPercentage, false, 1);
		setUniform("SSAO/HorizonBased", "SSAO/HorizonBased", "cSampleLengthScreenSpace", sampleInScreenSpaceLengthPercentage, false, 1);
		setUniform("SSAO/HemisphereMC", "SSAO/HemisphereMC", "cSampleLengthScreenSpace", sampleInScreenSpaceLengthPercentage, false, 1);
		setUniform("SSAO/Volumetric", "SSAO/Volumetric", "cSampleLengthScreenSpace", sampleInScreenSpaceLengthPercentage, false, 1);




		float size = 15.0f;
		//float size = 100.0f;
		setUniform("SSAO/Crytek", "SSAO/Crytek", "cSampleLengthWorldSpace", size, false, 1);
		setUniform("SSAO/HorizonBased", "SSAO/HorizonBased", "cSampleLengthWorldSpace", size, false, 1);
		setUniform("SSAO/HemisphereMC", "SSAO/HemisphereMC", "cSampleLengthWorldSpace", size, false, 1);
		setUniform("SSAO/Volumetric", "SSAO/Volumetric", "cSampleLengthWorldSpace", size, false, 1);
        
		setUniform("SSAO/Crytek", "SSAO/Crytek", "cOffsetScale", 95.0f/100, false, 1);
		setUniform("SSAO/Crytek", "SSAO/Crytek", "cEdgeHighlight", 0.75f, false, 1);
		setUniform("SSAO/Crytek", "SSAO/Crytek", "cDefaultAccessibility", 0.5f, false, 1);

		setUniform("SSAO/HorizonBased", "SSAO/HorizonBased", "cAngleBias", 0.2f, false, 1);

		setUniform("SSAO/HemisphereMC", "SSAO/HemisphereMC", "cSampleLengthExponent", 8.0f, false, 1);
        
		setUniform("SSAO/UnsharpMask", "SSAO/UnsharpMask/GaussianBlurY", "cKernelWidthBias", 1.0f, false, 1);
		setUniform("SSAO/UnsharpMask", "SSAO/UnsharpMask/GaussianBlurX", "cKernelWidthBias", 1.0f, false, 1);
		setUniform("SSAO/UnsharpMask", "SSAO/UnsharpMask", "cLambda", 25.0f, false, 1);
        
		setUniform("SSAO/Post/CrossBilateralFilter", "SSAO/HorizonBased/CrossBilateralFilter/X", "cPhotometricExponent", 0.5f, false);
		setUniform("SSAO/Post/CrossBilateralFilter", "SSAO/HorizonBased/CrossBilateralFilter/Y", "cPhotometricExponent", 0.5f, false);
        
        
        CompositorManager::getSingleton().setCompositorEnabled(mViewport, mCurrentCompositor, true);
        CompositorManager::getSingleton().setCompositorEnabled(mViewport, mCurrentPost, true);
    }


void	Engine::setupSSAO(){
	Logger::debug("setupSSAO");
	std::vector<String> mCompositorNames;
	mCurrentCompositor;
	
	std::vector<String> mPostNames;
	mCurrentPost;

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
	

	mCurrentCompositor = mCompositorNames[0];
	mCurrentPost = mPostNames[1];
	
	if (CompositorManager::getSingleton().addCompositor(mViewport, "SSAO/GBuffer"))
		CompositorManager::getSingleton().setCompositorEnabled(mViewport, "SSAO/GBuffer", true);
	else
		Logger::debug("Sample_SSAO: Failed to add GBuffer compositor\n");
	
	for (unsigned int i = 0; i < mCompositorNames.size(); i++)
	{
		if (CompositorManager::getSingleton().addCompositor(mViewport, mCompositorNames[i]))
			CompositorManager::getSingleton().setCompositorEnabled(mViewport, mCompositorNames[i], false);
		else
			Logger::debug("Sample_SSAO: Failed to add compositor: " + mCompositorNames[i] + "\n");
	}
	
	for (unsigned int i = 0; i < mPostNames.size(); i++)
	{
		
		if (CompositorManager::getSingleton().addCompositor(mViewport, mPostNames[i]))
			CompositorManager::getSingleton().setCompositorEnabled(mViewport, mPostNames[i], false);
		else
			;
			//Logger::debug("Sample_SSAO: Failed to add " + mPostNames[i] + " compositor\n");
	}
	
	CompositorManager::getSingleton().setCompositorEnabled(mViewport, mCurrentCompositor, true);
	CompositorManager::getSingleton().setCompositorEnabled(mViewport, mCurrentPost, true);

    testsetup();





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

	unsigned long elapsedTime = getElapsedTime();
    //Logger::debug(format("%1%") % elapsedTime);

	//float 	mSimulationTimeStep = 1000.0f / 60.0f;	
	float 	mSimulationTimeStep = 2.0f;	
	//float	timeToSimulate = elapsedTime;
	mSimulationTime += elapsedTime;
	float	timeToSimulate = mSimulationTimeStep / 1000.0f;
	timeToSimulate *= getTimingFactor();

	while(mSimulationTime > mSimulationTimeStep) {
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
			//rSys->setConfigOption("Full Screen", "Yes");
			rSys->setConfigOption("Video Mode", "700 x 850 @ 32-bit colour");
			//rSys->setConfigOption("Video Mode", "1024 x 768 @ 32-bit colour");
			//rSys->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
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

	mSceneMgr->setShadowTechnique(
		//Ogre::SHADOWTYPE_STENCIL_ADDITIVE
		Ogre::SHADOWTYPE_TEXTURE_MODULATIVE
		);
	//mSceneMgr->setShadowTextureSettings( 1024, 3, Ogre::PF_FLOAT32_R );
	//mSceneMgr->setShadowTextureSettings( 512, 2);
	//mSceneMgr->setShadowTextureSettings( 1024, 4);
	mSceneMgr->setShadowTextureSettings( 2048, 4);
	//FocusedShadowCameraSetup *camSetup = new FocusedShadowCameraSetup();
	LiSPSMShadowCameraSetup *camSetup = new LiSPSMShadowCameraSetup();
	//PSSMShadowCameraSetup *camSetup = new PSSMShadowCameraSetup();
	mSceneMgr->setShadowCameraSetup(ShadowCameraSetupPtr(camSetup));
	//mSceneMgr->setShadowTextureSelfShadow(true);
    mSceneMgr->setShadowColour(ColourValue(0.5,0.5,0.5));

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
    //mViewport->setBackgroundColour(ColourValue(0.5,0.3,0.2));
    mViewport->setBackgroundColour(ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio( Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

	/*
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
	*/

    Light * light3 = mSceneMgr->createLight("MainLight3");
	light3->setType(Light::LT_DIRECTIONAL);
    //light3->setPosition(-200,200,-200);
	light3->setDiffuseColour(0.2,0.2,0.2);
	light3->setSpecularColour(0.5,0.5,0.5);
	light3->setDirection(Vector3(0,-1,1));

	/*
    //Entity *ent = mSceneMgr->createEntity("head","cube.mesh");
    Entity *ent = mSceneMgr->createEntity("head","Prefab_Cube");
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	*/

	mRaySceneQuery = mSceneMgr->createRayQuery(Ray());

}

void Engine::close(){
	mSceneMgr->destroyQuery(mRaySceneQuery);
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
	mCurrentTime = mTimer.getMilliseconds();
	mTimeDifference = mCurrentTime - mLastTime;
	mLastTime = mCurrentTime;
    //Logger::debug(format("%1% %2%") % mCurrentTime % timeDifference);
	return mTimeDifference;
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
	releaseMouseKeys();
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
	releaseMouseKeys();
}

void	Engine::releaseMouseKeys(){
	if (isKeyDown(K_MLEFT)){
		removePressedKey(K_MLEFT);
		pyFunctionKeyReleased(K_MLEFT);
	}
	if (isKeyDown(K_MRIGHT)){
		removePressedKey(K_MRIGHT);
		pyFunctionKeyReleased(K_MRIGHT);
	}
	if (isKeyDown(K_MMIDDLE)){
		removePressedKey(K_MMIDDLE);
		pyFunctionKeyReleased(K_MMIDDLE);
	}
}

std::string		Engine::createUuid(){
	return boost::lexical_cast<std::string>(
		boost::uuids::random_generator()()
		);
}


