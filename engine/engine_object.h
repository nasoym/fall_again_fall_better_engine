#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include <string>
#include "uuid.h"

/*
#include "engine_gui_shape.h"
#include "engine_gui_container.h"
#include "engine_body.h"
#include "engine_joint.h"
#include "engine_spacecage.h"
*/

class EngineGuiShape;
class EngineGuiContainer;
class EngineBody;
class EngineJoint;
class EngineSpaceCage;

#include "engine.h"
class Engine;

class EngineObject {
    public:
        EngineObject(Engine* engine);
        virtual ~EngineObject();

		std::string 	getName(){return mName;}
		void 			setName(std::string& name){mName = name;}
		//void 			setName(char * chr_ptr){mName = name;}

		std::string		readUuid(){ return mUuid.toString(); }
		void			setUuid(){}
		Uuid			getUuid(){ return mUuid; }

		Engine*			getEngine(){ return mEngine; }

		virtual void	guiUpdate(){}
		virtual void	physicUpdate(){}

		virtual EngineGuiShape*			isGuiShape(){return 0;}
		virtual EngineGuiContainer*		isGuiContainer(){return 0;}
		virtual EngineBody*				isBody(){return 0;}
		virtual EngineJoint*			isJoint(){return 0;}
		virtual EngineSpaceCage*	 	isSpaceCage(){return 0;}

	private:
		Engine*		mEngine;
		std::string	mName;
		Uuid		mUuid;
};
#endif
