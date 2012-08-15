#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "stdio.h"
#include <string>
#include "uuid.h"

class Engine;

class EngineGuiShape;
class EngineGuiContainer;
class EngineBody;
class EngineStaticBody;
class EngineJoint;
class EngineSpaceCage;
class EngineMesh;
class EngineBox;

enum ObjectType {
	OBJECT,
	GUISHAPE,
    MESH,
	SPACECAGE,
	JOINT,
	BODY,
	STATICBODY,
	GUICONTAINER,
	BOX,
};

class EngineObject {
    public:
        EngineObject(Engine* engine);
        virtual ~EngineObject();

		std::string 	getName(){return mName;}
		void 			setName(std::string& name){mName = name;}
		//void 			setName(char * chr_ptr){mName = name;}

		std::string		readUuid(){ return mUuid.toString(); }
		void			setUuid(std::string name){mUuid.fromString(name);}
		Uuid			getUuid(){ return mUuid; }

		Engine*			getEngine(){ return mEngine; }

		virtual ObjectType		getType(){ return OBJECT;}

		virtual void	guiUpdate(){}
		virtual void	physicUpdate(){}

		virtual EngineGuiShape*			isGuiShape(){return 0;}
		virtual EngineGuiContainer*		isGuiContainer(){return 0;}
		virtual EngineBody*				isBody(){return 0;}
		virtual EngineStaticBody*	 	isStaticBody(){return 0;}
		virtual EngineJoint*			isJoint(){return 0;}
		virtual EngineSpaceCage*	 	isSpaceCage(){return 0;}
		virtual EngineMesh*				isMesh(){return 0;}
		virtual EngineBox*				isBox(){return 0;}

		void			setSelectable(){mSelectable=true;}
		void			setUnselectable(){mSelectable=false;}
		bool			isSelectable(){return mSelectable;}

	private:
		Engine*		mEngine;
		std::string	mName;
		Uuid		mUuid;
		bool		mSelectable;
};
#endif
