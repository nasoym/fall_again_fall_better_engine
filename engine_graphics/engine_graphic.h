#ifndef _GRAPHIC_ENGINE_H
#define _GRAPHIC_ENGINE_H

#include <Ogre.h>
using namespace Ogre;

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

#include <set>

#include "keyboard_listener.h"

class GraphicsEngine : 
        public WindowEventListener,
		public OIS::KeyListener,
		public OIS::MouseListener
	{
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        void    render();

        SceneManager*   getSceneManager(){return mSceneMgr;}
        SceneNode*      getFinalNode(){return mFinalSceneNode;}
        SceneNode*      getDebugNode(){return mDebugSceneNode;}
		Camera*			getCamera(){return mCamera;}

        bool            inputExit();
        void            processOIS();

        void    windowResized(RenderWindow*);
        void windowMoved(RenderWindow* rw);
        void windowClosed(RenderWindow* rw);
        void windowFocusChange(RenderWindow* rw);

        bool keyPressed(const OIS::KeyEvent& evt);
        bool keyReleased(const OIS::KeyEvent& evt);
        bool mouseMoved(const OIS::MouseEvent& evt);
        bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	
		void    deleteKeyboardListener(KeyboardListener*);
		void    addKeyboardListener(KeyboardListener*);

		void	allKeyboardListenersReleased(const OIS::KeyEvent& evt);
		void	allKeyboardListenersPressed(const OIS::KeyEvent& evt);

		void	allKeyboardListenersMouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		void	allKeyboardListenersMousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);


		void		setCameraPosition(Vector3&);
		void		setCameraOrientation(Quaternion&);

		const Vector3		getCameraPosition();
		const Quaternion		getCameraOrientation();

		unsigned long getElapsedTime();

		//TODO set windows params

    private:
        void    setup();
        void    close();
        void    setupResources();
        void    setupOIS();    
        void    closeOIS();
        void    setupWindowEventListener();
        void    closeWindowEventListener();

    private:
        Root*           mRoot;
        LogManager*     mLogger;
        Camera*         mCamera;
        SceneManager*   mSceneMgr;
        RenderWindow*   mWindow;
        Viewport*       mViewport;
		Timer			mTimer;
		unsigned long mCurrentTime;
		unsigned long mLastTime;

        SceneNode*      mRootSceneNode;
        SceneNode*      mDebugSceneNode;
        SceneNode*      mFinalSceneNode;

        OIS::InputManager* mInputManager;
        OIS::Mouse*     mMouse;
        OIS::Keyboard*  mKeyboard;
        bool            mExit;

		std::set<KeyboardListener*>    mKeyboardListeners;

};
#endif
