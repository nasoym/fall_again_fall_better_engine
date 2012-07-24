//-------------------------------------
#ifndef _GRAPHIC_ENGINE_H
#define _GRAPHIC_ENGINE_H

#include <Ogre.h>
using namespace Ogre;

#include <set>

#include "keyboard_listener.h"

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

//-------------------------------------
class GraphicsEngine : 
        public WindowEventListener,
		public OIS::KeyListener,
		public OIS::MouseListener
{
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        void    render();

        SceneManager*   getSceneManager(){ return mSceneMgr; }
        SceneNode*      getFinalNode(){ return mFinalSceneNode; }
        SceneNode*      getDebugNode(){ return mDebugSceneNode; }

        bool            inputExit();
        void            processOIS();

        virtual void    windowResized(RenderWindow*);
        virtual void windowMoved(RenderWindow* rw);
        virtual void windowClosed(RenderWindow* rw);
        virtual void windowFocusChange(RenderWindow* rw);

        virtual bool keyPressed(const OIS::KeyEvent& evt);
        virtual bool keyReleased(const OIS::KeyEvent& evt);
        virtual bool mouseMoved(const OIS::MouseEvent& evt);
        virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
        virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	
		void    deleteKeyboardListener(KeyboardListener*);
		void    addKeyboardListener(KeyboardListener*);

		void	allKeyboardListenersReleased(const OIS::KeyEvent& evt);
		void	allKeyboardListenersPressed(const OIS::KeyEvent& evt);

		void	allKeyboardListenersMouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		void	allKeyboardListenersMousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);


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

        SceneNode*      mRootSceneNode;
        SceneNode*      mDebugSceneNode;
        SceneNode*      mFinalSceneNode;

        OIS::InputManager* mInputManager;
        OIS::Mouse*     mMouse;
        OIS::Keyboard*  mKeyboard;
        bool            mExit;

		std::set<KeyboardListener*>    mKeyboardListeners;

};
//-------------------------------------
#endif
//-------------------------------------

