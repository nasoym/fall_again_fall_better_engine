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
    mLogger = new Ogre::LogManager();
    mLogger->createLog("log.log", true, false,true);

	//root = new Root("","");
	mRoot = new Root();
	mRoot->showConfigDialog();
    setupResources();

	mWindow = mRoot->initialise(true);

    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mCamera = mSceneMgr->createCamera("PlayerCam");
    // Position it at 500 in Z direction
    mCamera->setPosition(Vector3(0,0,500));
    // Look back along -Z
    mCamera->lookAt(Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    // Create one viewport, entire window
    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.5,0.3,0.2));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio( Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

    //mFrameListener = new ExampleFrameListener(mWindow, mCamera);

    mSceneMgr->setAmbientLight(ColourValue(0.5,0.5,0.5));

    Light * light = mSceneMgr->createLight("MainLight");
    light->setPosition(0,400,0);

    Entity *ent = mSceneMgr->createEntity("head","cube.mesh");
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);


}

void GraphicsEngine::close(){
    mRoot->shutdown();
}

void GraphicsEngine::setupResources() {
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


void GraphicsEngine::render(){
    Logger::debug(format("render graphics engine: %p ") % this);
    mRoot->renderOneFrame();
}


