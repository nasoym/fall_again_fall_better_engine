#include "logger.h"
#include "engine_graphic.h"
#include "keyboard_listener.h"

GraphicsEngine::GraphicsEngine() :
    mExit(false),
    mInputManager(0),
	mCurrentTime(0),
	mLastTime(0)
    {
    Logger::debug(format("creating graphics engine: %p ") % this);
    setup();
	setupStereo();
    setupOIS();
    setupWindowEventListener();

}

GraphicsEngine::~GraphicsEngine(){
    Logger::debug(format("deleting graphics engine: %p ") % this);
    closeWindowEventListener();
    closeOIS();
	closeStereo();
    close();
}

void GraphicsEngine::setup(){
    mLogger = new Ogre::LogManager();
    mLogger->createLog("log.log", true, false,true);

	//root = new Root("","");
	mRoot = new Root();
    setupResources();

    RenderSystemList rlist = mRoot->getAvailableRenderers();
    RenderSystemList::iterator it = rlist.begin();
    while (it !=rlist.end()) {
        RenderSystem *rSys = *(it++);
		rSys->setConfigOption("Full Screen", "No");
		rSys->setConfigOption("Video Mode", "1024 x 768 @ 32-bit colour");
		mRoot->setRenderSystem(rSys);
    }
	//mRoot->showConfigDialog();

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

void GraphicsEngine::close(){
	OGRE_DELETE mRoot;
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

void 		GraphicsEngine::setupStereo() {
	//mStereoManager.init(mViewport, NULL, "stereo.cfg");
}

void 		GraphicsEngine::closeStereo() {
}

void		GraphicsEngine::setCameraPosition(Vector3& vec){
	getCamera()->setPosition(vec);
}

void		GraphicsEngine::setCameraOrientation(Quaternion& quat){
	getCamera()->setOrientation(quat);
}

const Vector3		GraphicsEngine::getCameraPosition(){
	return getCamera()->getPosition();
}

const Quaternion		GraphicsEngine::getCameraOrientation(){
	return getCamera()->getOrientation();
}

unsigned long GraphicsEngine::getElapsedTime() {
	unsigned long timeDifference = 0;

	mCurrentTime = mTimer.getMilliseconds();
	timeDifference = mCurrentTime - mLastTime;
	mLastTime = mCurrentTime;
    //Logger::debug(format("%1% %2%") % mCurrentTime % timeDifference);
	return timeDifference;
}

void GraphicsEngine::setupOIS() {
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
    //Logger::debug("windowResized");
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;

    mCamera->setAspectRatio( Real(width) / Real(height));
}

void GraphicsEngine::windowMoved(RenderWindow* rw) {
    //Logger::debug("windowMoved");
}

bool windowClosing(RenderWindow* rw) {
    //Logger::debug("windowClosing");
    return true;
}

void GraphicsEngine::windowClosed(RenderWindow* rw) {
    //Logger::debug("windowClosed");
    mExit = true;
}

void GraphicsEngine::windowFocusChange(RenderWindow* rw) {
    //Logger::debug("windowFocusChange");
}

bool GraphicsEngine::keyPressed(const OIS::KeyEvent& evt) {
	allKeyboardListenersPressed(evt);
    return true;
}

bool GraphicsEngine::keyReleased(const OIS::KeyEvent& evt) {
	allKeyboardListenersReleased(evt);
    return true;
}

bool GraphicsEngine::mouseMoved(const OIS::MouseEvent& evt) {
	const OIS::MouseState &ms = mMouse->getMouseState();
	if( ms.buttonDown( OIS::MB_Left ) ) {
		mCamera->yaw(Degree(-ms.X.rel * 0.13));
		mCamera->pitch(Degree(-ms.Y.rel * 0.13));
	}
    return true;
}

bool GraphicsEngine::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
    //Logger::debug("mousePressed");
	allKeyboardListenersMousePressed(evt,id);
    return true;
}

bool GraphicsEngine::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
    //Logger::debug("mouseReleased");
	allKeyboardListenersMouseReleased(evt,id);
    return true;
}

void    GraphicsEngine::deleteKeyboardListener(KeyboardListener* keylistener) {
	std::set<KeyboardListener*>::iterator  mIterator;
	for (mIterator = mKeyboardListeners.begin(); 
		mIterator != mKeyboardListeners.end(); ++mIterator) {
		if ( (*mIterator) == keylistener ){
			delete (*mIterator);
			mKeyboardListeners.erase( mIterator);
			break;
		}
	}
}

void    GraphicsEngine::addKeyboardListener(KeyboardListener* keylistener) {
	mKeyboardListeners.insert(keylistener);
}

void	GraphicsEngine::allKeyboardListenersPressed(const OIS::KeyEvent& evt) {
	std::set<KeyboardListener*>::iterator  mIterator;
	for (mIterator = mKeyboardListeners.begin(); 
		mIterator != mKeyboardListeners.end(); ++mIterator) {
		(*mIterator)->keyPressed(evt);
	}
}

void	GraphicsEngine::allKeyboardListenersReleased(const OIS::KeyEvent& evt) {
	std::set<KeyboardListener*>::iterator  mIterator;
	for (mIterator = mKeyboardListeners.begin(); 
		mIterator != mKeyboardListeners.end(); ++mIterator) {
		(*mIterator)->keyReleased(evt);
	}
}

void	GraphicsEngine::allKeyboardListenersMousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
	std::set<KeyboardListener*>::iterator  mIterator;
	for (mIterator = mKeyboardListeners.begin(); 
		mIterator != mKeyboardListeners.end(); ++mIterator) {
		(*mIterator)->mousePressed(evt,id);
	}
}

void	GraphicsEngine::allKeyboardListenersMouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
	std::set<KeyboardListener*>::iterator  mIterator;
	for (mIterator = mKeyboardListeners.begin(); 
		mIterator != mKeyboardListeners.end(); ++mIterator) {
		(*mIterator)->mouseReleased(evt,id);
	}
}
