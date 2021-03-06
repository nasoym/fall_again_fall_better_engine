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

#include <stdio.h>
#include <time.h>


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
	mUseFirstRenderer(true),
	mHideMouse(false),
	//mHideMouse(true),
	mDefaultShadedMaterialName("")
	{
    setup();
    Logger::debug(format("creating engine: %p ") % this);
    setupPhysics();
	//setupSSAO();
    setupOIS();
    setupWindowEventListener();
	setupStereo();
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

		setUniform("SSAO/HemisphereMC", "SSAO/HemisphereMC", "cSampleLengthExponent", 15.0f, false, 1);
        
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

void Engine::physicsPause(){
	mPhysicPaused = true;
}

void Engine::physicsUnpause(){
	mPhysicPaused = false;
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
	mMappedObjects.clear();
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
			//delete (*mIterator);
			break;
		}
	}
	deleteMappedObject(object);
	Logger::debug("done with engine del");
}

void 	Engine::deleteMappedObject(EngineObject* object){
	std::map<std::string,EngineObject*>::iterator  mIterator;
	for (mIterator = mMappedObjects.begin(); 
		mIterator != mMappedObjects.end(); ++mIterator) {
		if ( (*mIterator).second == object ){
			mMappedObjects.erase( mIterator);
			break;
		}
	}
}

void 	Engine::addMappedObject(EngineObject* object) {
	mMappedObjects[object->readUuid()] = object;
}

void    Engine::addObject(EngineObject* object){
	mObjects.push_back(object);
	addMappedObject(object);
}

int     Engine::howManyObjects() {
	return mObjects.size();
}

EngineObject* Engine::getObject(int index){
	return mObjects[index];
}

EngineObject* Engine::getFromUuid(std::string uuidToFind){
	std::map<std::string,EngineObject*>::iterator  mIterator;
	mIterator = mMappedObjects.find(uuidToFind);
	if (mIterator!=mMappedObjects.end()) {
		return (*mIterator).second;
	}
	return 0;
}

bool	Engine::isFullscreen(){
	if (mWindow) {
		return mWindow->isFullScreen();
	} else {
		return false;
	}
}



void Engine::setup(){
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char buffer [40];
	strftime(buffer,40,"../logs/%Y_%m_%d_%H_%M_%S_ogre.log",timeinfo);

	//LogManager::getSingleton().logMessage("before",LML_CRITICAL);
    mLogger = new Ogre::LogManager();

	bool	ogreLogSupressFileOutput = false;
	bool	ogreLogDebuggerOutput = true;
	bool	ogreLogDefaultLog = false;
    //mLogger->createLog("ogre.log",
    mLogger->createLog(buffer,
		ogreLogSupressFileOutput,
		ogreLogDebuggerOutput,
		ogreLogDefaultLog);

	mLogger->setLogDetail(LL_LOW);
	//mLogger->setLogDetail(LL_NORMAL);
	//mLogger->setLogDetail(LL_BOREME);

	//LogManager::getSingleton().logMessage("hello",LML_CRITICAL);
//LML_TRIVIAL 	
//LML_NORMAL 	
//LML_CRITICAL


	mRoot = new Root();

	if (mRoot->restoreConfig()){

	} else {

	}
    setupResources();

	//if (!mUseFirstRenderer){
	//	mRoot->showConfigDialog();
	//}
	FILE * pFile;
	pFile = fopen("ogre.cfg" , "r");
	if (pFile == NULL) {
		//Logger::debug("ogre.cfg does NOT exists");
		mRoot->showConfigDialog();
	} else {
		//Logger::debug("ogre.cfg exists");
	}

	mWindow = mRoot->initialise(true);

	if (mWindow->isFullScreen()){
		mHideMouse = true;
	}

	//mRoot->initialise(false);
	//mWindow = mRoot->createRenderWindow("main window",400,400,false);

    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");

	mSceneMgr->setShadowTechnique(
		//Ogre::SHADOWTYPE_STENCIL_ADDITIVE
		//Ogre::SHADOWTYPE_STENCIL_MODULATIVE
		Ogre::SHADOWTYPE_TEXTURE_MODULATIVE
		);
	//mSceneMgr->setShadowTextureSettings( 1024, 3, Ogre::PF_FLOAT32_R );
	//mSceneMgr->setShadowTextureSettings( 512, 2);
	//mSceneMgr->setShadowTextureSettings( 1024, 4);
	//mSceneMgr->setShadowTextureSettings( 2048, 8);
	mSceneMgr->setShadowTextureSettings( 4096, 1);
	mSceneMgr->setShadowFarDistance(5000);

	//DefaultShadowCameraSetup *camSetup = new DefaultShadowCameraSetup();
	//FocusedShadowCameraSetup *camSetup = new FocusedShadowCameraSetup();
	//LiSPSMShadowCameraSetup *camSetup = new LiSPSMShadowCameraSetup();
	PSSMShadowCameraSetup *camSetup = new PSSMShadowCameraSetup();
	mSceneMgr->setShadowCameraSetup(ShadowCameraSetupPtr(camSetup));
	//mSceneMgr->setShadowTextureSelfShadow(true);

    mRootSceneNode = mSceneMgr->getRootSceneNode();
    mDebugSceneNode = mRootSceneNode->createChildSceneNode();
    mFinalSceneNode = mRootSceneNode->createChildSceneNode();

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Vector3(0,0,500));
    mCamera->lookAt(Vector3(0,0,-300));
	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(100000);

    // Create one viewport, entire window
    mViewport = mWindow->addViewport(mCamera);
    mCamera->setAspectRatio( Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

    mMainLight = mSceneMgr->createLight("MainLight");
	mMainLight->setType(Light::LT_DIRECTIONAL);
	mMainLight->setDirection(Vector3(0,-1,1));

    mSecondLight = mSceneMgr->createLight("SecondLight");
	mSecondLight->setType(Light::LT_DIRECTIONAL);
	mSecondLight->setDirection(Vector3(0,-1,-1));
	mSecondLight->setCastShadows(false);


	/*
	Entity* ent;
	SceneNode* node;

    node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ent = mSceneMgr->createEntity("Prefab_Cube");
    ent->setMaterialName("Body");
	node->attachObject(ent);
	node->setPosition(0,-40,0);
	node->setScale(10,0.001,10);
	ent->setCastShadows(false);
	//ent->setCastShadows(true);

    node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    //ent = mSceneMgr->createEntity("figure.mesh");
    ent = mSceneMgr->createEntity("tube.mesh");
    ent->setMaterialName("Body");
	node->attachObject(ent);
	node->setPosition(0,-50,0);
	node->setPosition(0,0,0);
	node->setScale(30,30,30);
	ent->setCastShadows(true);

    node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ent = mSceneMgr->createEntity("athene.mesh");
    ent->setMaterialName("Body");
	node->attachObject(ent);
	node->setPosition(60,60,0);
	node->setScale(1,1,1);
	ent->setCastShadows(true);

    node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ent = mSceneMgr->createEntity("Prefab_Cube");
    ent->setMaterialName("Body");
	node->attachObject(ent);
	node->setPosition(-60,20,0);
	node->setScale(0.3,0.3,0.3);
	ent->setCastShadows(true);
	*/


	mRaySceneQuery = mSceneMgr->createRayQuery(Ray());

	lightsOn();

	setupDefaultMaterial();
}


void		Engine::lightsOff(){
	ColourValue	col0 = ColourValue(0.00,0.00,0.00,1.0);
	ColourValue	col1 = ColourValue(0.14,0.09,0.06,1.0);
	ColourValue	col2 = ColourValue(0.30,0.15,0.02,1.0);
	ColourValue	col3 = ColourValue(0.69,0.62,0.53,1.0);
	ColourValue	col4 = ColourValue(0.86,0.78,0.68,1.0);
	ColourValue	col5 = ColourValue(0.30,0.15,0.02,1.0);
	ColourValue	col6 = ColourValue(0.30,0.15,0.02,1.0);
	ColourValue	col7 = ColourValue(0.30,0.15,0.02,1.0);

    mSceneMgr->setAmbientLight(col0);

    mSceneMgr->setShadowColour(col0);
    mViewport->setBackgroundColour(col0);
	mMainLight->setDiffuseColour(col0);
	mMainLight->setSpecularColour(col0);

	mSecondLight->setDiffuseColour(col0);
	mSecondLight->setSpecularColour(col0);

	MaterialPtr mat = MaterialManager::getSingleton().getByName("Body");
	mat->getTechnique(0)->getPass(0)->setAmbient(col0);
	mat->getTechnique(0)->getPass(0)->setDiffuse(col0);
	mat->getTechnique(0)->getPass(0)->setSpecular(col0);

}

void		Engine::lightsOn(){
	ColourValue	col0 = ColourValue(0.00,0.00,0.00,1.0);

	// sepia
	ColourValue	col1 = ColourValue(0.14,0.09,0.06,1.0);
	ColourValue	col2 = ColourValue(0.30,0.15,0.02,1.0);
	ColourValue	col3 = ColourValue(0.69,0.62,0.53,1.0);
	ColourValue	col4 = ColourValue(0.86,0.78,0.68,1.0);
	ColourValue	col5 = ColourValue(0.30,0.15,0.02,1.0);
	ColourValue	col6 = ColourValue(0.30,0.15,0.02,1.0);
	ColourValue	col7 = ColourValue(0.30,0.15,0.02,1.0);

	/*
	ColourValue	col1 = ColourValue(0.1,0.1,0.1,1.0);
	ColourValue	col2 = ColourValue(0.2,0.2,0.2,1.0);
	ColourValue	col3 = ColourValue(0.5,0.5,0.5,1.0);
	ColourValue	col4 = ColourValue(0.7,0.7,0.7,1.0);
	ColourValue	col5 = ColourValue(0.3,0.3,0.3,1.0);
	ColourValue	col6 = ColourValue(0.5,0.5,0.5,1.0);
	*/

    mSceneMgr->setAmbientLight(col1);

    mSceneMgr->setShadowColour(col2);
    mViewport->setBackgroundColour(col0);
	mMainLight->setDiffuseColour(col3);
	mMainLight->setSpecularColour(col4);

	mSecondLight->setDiffuseColour(col5);
	mSecondLight->setSpecularColour(col6);

	MaterialPtr mat = MaterialManager::getSingleton().getByName("Body");
	mat->getTechnique(0)->getPass(0)->setAmbient(col1);
	mat->getTechnique(0)->getPass(0)->setDiffuse(col2);
	mat->getTechnique(0)->getPass(0)->setSpecular(col3);
	mat->getTechnique(0)->getPass(0)->setShininess(2.0f);

}

void			Engine::setupDefaultMaterial(){
	MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
		"default_material",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->setDiffuse(ColourValue(0.5f,0.5f,0.5f,0.25f)); 
	//material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(true); 
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false); 
	material->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	material->getTechnique(0)->getPass(0)->setCullingMode(CULL_NONE);
	Pass* wireFramePass = material->getTechnique(0)->createPass();
	wireFramePass->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	wireFramePass->setDepthWriteEnabled(true);
	wireFramePass->setPolygonMode(PM_WIREFRAME);
	wireFramePass->setDiffuse(ColourValue(0,0,0,0.2f));

	mDefaultShadedMaterialName = std::string("Body");
	//mDefaultShadedMaterialName = std::string("default_material");
}

std::string		Engine::getDefaultShadedMaterialName(){
	return mDefaultShadedMaterialName;
}

void Engine::close(){
	mSceneMgr->destroyQuery(mRaySceneQuery);
	OGRE_DELETE mRoot;
}

void Engine::render(){
    WindowEventUtilities::messagePump();
	if (mWindow->isActive()){
		mRoot->renderOneFrame();
	} else if (mWindow->isVisible()) {
		mWindow->update();
	}
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

	if (!mHideMouse){
		pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_FOREGROUND"));
		pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_NONEXCLUSIVE"));
	}

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

		/*
        if( !mMouse->buffered() ) {
            const OIS::MouseState &ms = mMouse->getMouseState();
            if( ms.buttonDown( OIS::MB_Right ) ) {
                ms.X.rel;
                ms.Y.rel;
            } else {
            }
        }
		*/
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
	//releaseMouseKeys();
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
	pyFunctionKeyPressed(K_FOCUS_CHANGE);
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


