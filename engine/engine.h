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

class Engine {
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

    private:
        void    setup();
        void    close();

    private:
        PhysicsEngine*  mPhysicsEngine;
        GraphicsEngine* mGraphicsEngine;
		bool			mLoopRendering;

		std::set<EngineObject*>    mObjects;
};

class EngineKeyListener : public KeyboardListener {
    private:
        Engine* 	mEngine;

    public:
		EngineKeyListener(Engine* engine) : mEngine(engine) { }

		virtual void keyPressed(const OIS::KeyEvent& evt);
		/*
		virtual void keyPressed(const OIS::KeyEvent& evt){
			if (evt.key == OIS::KC_ESCAPE) {
				Logger::debug("esc pressed");
				mEngine->quit();
			}
			if (evt.key == OIS::KC_1) {
				//new GraphicsBox(mGraphicsEngine);
				EngineGuiShape* engineObject = new EngineGuiShape(mEngine);
				engineObject->setShape(new GraphicsBox(mEngine->mGraphicsEngine));
			}
		}
		*/

		virtual void keyReleased(const OIS::KeyEvent& evt){
			if (evt.key == OIS::KC_ESCAPE) {
				Logger::debug("esc released");
			}
		}

		virtual void	mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
			if(id == OIS::MB_Left)  {
				Logger::debug("left pressed");
			}
		}
		virtual void	mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
			if(id == OIS::MB_Left)  {
				Logger::debug("left released");
			}
		}
};
#endif
