//-------------------------------------
#include "logger.h"
#include "engine_graphic.h"
//-------------------------------------
GraphicsEngine::GraphicsEngine() :
    mExit(false),
    mInputManager(0)
    {
    Logger::debug(format("creating graphics engine: %p ") % this);
    setup();
    setupOIS();
    setupWindowEventListener();
}

GraphicsEngine::~GraphicsEngine(){
    Logger::debug(format("deleting graphics engine: %p ") % this);
    closeWindowEventListener();
    closeOIS();
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

    // Create one viewport, entire window
    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(0.5,0.3,0.2));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio( Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));

    //mFrameListener = new ExampleFrameListener(mWindow, mCamera);

    mSceneMgr->setAmbientLight(ColourValue(0.5,0.5,0.5));

    Light * light = mSceneMgr->createLight("MainLight");
    light->setPosition(0,400,0);

    //Entity *ent = mSceneMgr->createEntity("head","cube.mesh");
    Entity *ent = mSceneMgr->createEntity("head","Prefab_Cube");
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);


}

void GraphicsEngine::close(){
    mRoot->shutdown();
}

void GraphicsEngine::render(){
    WindowEventUtilities::messagePump();
    mRoot->renderOneFrame();
    //mRoot->startRendering();
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

void GraphicsEngine::setupOIS() {
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    bool bufferedKeys = false;
    bool bufferedMouse = false;

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

void GraphicsEngine::closeOIS() {
    if( mInputManager ) {
        mInputManager->destroyInputObject( mMouse );
        mInputManager->destroyInputObject( mKeyboard );

        OIS::InputManager::destroyInputSystem(mInputManager);
        mInputManager = 0;
    }
}

void GraphicsEngine::processOIS() {
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

bool    GraphicsEngine::inputExit() {
    return mExit;
}

void    GraphicsEngine::setupWindowEventListener() {
    WindowEventUtilities::addWindowEventListener(mWindow, this);
}
void    GraphicsEngine::closeWindowEventListener() {
    WindowEventUtilities::removeWindowEventListener(mWindow, this);
}


//Adjust mouse clipping area
void GraphicsEngine::windowResized(RenderWindow* rw) {
    Logger::debug("windowResized");
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void GraphicsEngine::windowMoved(RenderWindow* rw) {
    Logger::debug("windowMoved");
}

bool windowClosing(RenderWindow* rw) {
    Logger::debug("windowClosing");
    return true;
}

void GraphicsEngine::windowClosed(RenderWindow* rw) {
    Logger::debug("windowClosed");
    mExit = true;
}

void GraphicsEngine::windowFocusChange(RenderWindow* rw) {
    Logger::debug("windowFocusChange");
}

bool GraphicsEngine::keyPressed(const OIS::KeyEvent& evt) {
    Logger::debug("keyPressed");
    return true;
}

bool GraphicsEngine::keyReleased(const OIS::KeyEvent& evt) {
    Logger::debug("keyReleased");
    return true;
}

bool GraphicsEngine::mouseMoved(const OIS::MouseEvent& evt) {
    Logger::debug("mouseMoved");
    return true;
}

bool GraphicsEngine::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
    Logger::debug("mousePressed");
    return true;
}

bool GraphicsEngine::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
    Logger::debug("mouseReleased");
    return true;
}

