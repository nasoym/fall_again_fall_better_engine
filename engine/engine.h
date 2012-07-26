#ifndef _ENGINE_H
#define _ENGINE_H

#include <boost/python.hpp>
using namespace boost::python;

#include "engine_physic.h"

#include "engine_graphic.h"

#include "engine_object.h"
class EngineObject;

#include <set>

#include "logger.h"

class Engine : public KeyboardListener {
    public:
        Engine();
        ~Engine();

        void    run();

		void	quit(){mLoopRendering=false;}

		void    deleteAllObjects();
		void    deleteObject(EngineObject*);
		int     howManyObjects();
		void    addObject(EngineObject*);
		//TODO object query

		GraphicsEngine*	getGraphicsEngine(){return mGraphicsEngine;}
		PhysicsEngine*	getPhysicsEngine(){return mPhysicsEngine;}

		void    physicUpdates();
		void    guiUpdates();

		void	setupPython();
		void	closePython();
		void    runPython();


		EngineObject*	createGuiBox();
		void	callPythonKeyPressed(const OIS::KeyEvent& evt );
		void	callPythonKeyReleased(const OIS::KeyEvent& evt );
		void	callPythonKeyPysicUpdate();
		void	callPythonKeyGuiUpdate();

		virtual void keyPressed(const OIS::KeyEvent& evt);
		virtual void keyReleased(const OIS::KeyEvent& evt);
		
		virtual void	mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		virtual void	mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);


    private:
        void    setup();
        void    close();

    private:
        PhysicsEngine*  		mPhysicsEngine;
        GraphicsEngine* 		mGraphicsEngine;
		bool					mLoopRendering;

		std::set<EngineObject*> mObjects;

		bool	mPythonInitialized;
        object main_namespace;

		object pyFunctionKeyPressed;
		object pyFunctionKeyReleased;
		object pyFunctionInit;
		object pyFunctionGuiUpdate;
		object pyFunctionPhysicUpdate;
};

#endif
