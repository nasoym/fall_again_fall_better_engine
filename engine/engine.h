#ifndef _ENGINE_H
#define _ENGINE_H

#include <boost/python.hpp>
#include <boost/python/list.hpp>
using namespace boost::python;

#include <Ogre.h>
using namespace Ogre;

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

enum Keys;

#include <set>
#include <vector>
#include <string>

#include "math3d.h"

class PhysicsEngine;

class GraphicsEngine;

#include "engine_object.h"
//class EngineObject;

#include <boost/python/list.hpp>

class Engine : 
        public WindowEventListener,
		public OIS::KeyListener,
		public OIS::MouseListener
		{
    public:
        Engine();
        ~Engine();

        void    run();
		void	step();
		void	simulatePhysics(float time);

		void	quit(){mLoopRendering=false;}

		void    deleteAllObjects();
		void    deleteObject(EngineObject*);
		int     howManyObjects();
		void    addObject(EngineObject*);
		EngineObject* getObject(int index);
		EngineObject* getFromUuid(std::string);

		PhysicsEngine*	getPhysicsEngine(){return mPhysicsEngine;}

		void    physicUpdates();
		void    guiUpdates();

		void	physicPauseToggle();

		void	setupSSAO();

		void	setupPython();
		void	closePython();
		void    runPython();

		EngineObject*	createPhysicBox();
		EngineObject*	createSpaceCage(Vec3&);
		EngineObject*	createGuiBox();
		EngineObject*	createJoint(EngineObject* obj1,EngineObject* obj2);
		EngineObject*	createPhysicStatic();
		EngineObject*	createMesh(const char*);

		void	callPythonKeyPressed(Keys);
		void	callPythonKeyDown(Keys);
		void	callPythonKeyReleased(Keys);
		void	callPythonKeyPysicUpdate();
		void	callPythonKeyGuiUpdate();

		bool 	keyPressed(const OIS::KeyEvent& evt);
		bool 	keyReleased(const OIS::KeyEvent& evt);
		bool	mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		bool	mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		Keys	keyEventToKeys(const OIS::KeyEvent & evt);

		void updateKeysDown();
		bool isKeyDown(Keys key);
		OIS::KeyCode	keysToKeyCode(Keys key);

		void			setCameraPosition(Vec3&);
		void			setCameraOrientation(Quat&);
		Vec3			getCameraPosition();
		Quat			getCameraOrientation();

		void			setTimingFactor(float factor){mTimingFactor=factor;}
		float			getTimingFactor(){return mTimingFactor;}

		void			setUseFirstRenderer(){mUseFirstRenderer=true;}
		void			setNotUseFirstRenderer(){mUseFirstRenderer=false;}


    private:
        void    setupPhysics();
        void    closePhysics();

    private:
        PhysicsEngine*  		mPhysicsEngine;
		bool					mLoopRendering;

		std::vector<EngineObject*> mObjects;

		float	mSimulationTime;

		bool	mPythonInitialized;
        object main_namespace;

		object pyFunctionKeyPressed;
		object pyFunctionKeyDown;
		object pyFunctionKeyReleased;
		object pyFunctionInit;
		object pyFunctionGuiUpdate;
		object pyFunctionPhysicUpdate;

		std::vector<Keys>		mPressedKeys;
		float			mTimingFactor;


	public:

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

        bool mouseMoved(const OIS::MouseEvent& evt);
	
		unsigned long getElapsedTime();

		//TODO set windows params
		void 		setupStereo();
		void 		closeStereo();
		EngineGuiShape*			getGuiShapeOfMovable(MovableObject* movable);
		boost::python::list		getMouseQuery();
		EngineObject*			getObjectOfShape(EngineGuiShape* shape);

		std::string				createUuid();

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

		bool			mPhysicPaused;
		bool			mUseFirstRenderer;
		RaySceneQuery*  mRaySceneQuery;

		//StereoManager	mStereoManager;

};
#endif
