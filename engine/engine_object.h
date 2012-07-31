#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "stdio.h"
#include <string>
#include "uuid.h"

class Engine;

class EngineGuiShape;
class EngineGuiContainer;
class EngineBody;
class EngineJoint;
class EngineSpaceCage;

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
