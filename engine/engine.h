#ifndef _ENGINE_H
#define _ENGINE_H

#include <boost/python.hpp>
using namespace boost::python;


enum Keys;

#include "engine_physic.h"

#include "engine_graphic.h"

#include "engine_object.h"
class EngineObject;

#include <set>
#include <vector>

#include "logger.h"

#include "math3d.h"

class Engine : public KeyboardListener {
    public:
        Engine();
        ~Engine();

        void    run();
		void	step();

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

		EngineObject*	createPhysicBox();
		EngineObject*	createSpaceCage(Vec3&);
		EngineObject*	createGuiBox();
		EngineObject*	createJoint(EngineObject* obj1,EngineObject* obj2);
		EngineObject*	createPhysicStatic();

		void	callPythonKeyPressed(Keys);
		void	callPythonKeyDown(Keys);
		void	callPythonKeyReleased(Keys);
		void	callPythonKeyPysicUpdate();
		void	callPythonKeyGuiUpdate();

		virtual void 	keyPressed(const OIS::KeyEvent& evt);
		virtual void 	keyReleased(const OIS::KeyEvent& evt);
		virtual void	mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		virtual void	mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		Keys	keyEventToKeys(const OIS::KeyEvent & evt);

		void updateKeysDown();

		void			setCameraPosition(Vec3&);
		void			setCameraOrientation(Quat&);
		Vec3			getCameraPosition();
		Quat			getCameraOrientation();

		void			setTimingFactor(float factor){mTimingFactor=factor;}
		float			getTimingFactor(){return mTimingFactor;}

    private:
        void    setup();
        void    close();

    private:
        PhysicsEngine*  		mPhysicsEngine;
        GraphicsEngine* 		mGraphicsEngine;
		bool					mLoopRendering;

		std::set<EngineObject*> mObjects;

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
};

#endif
