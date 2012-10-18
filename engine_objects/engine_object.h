#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "stdio.h"
#include <string>
#include "uuid.h"

class Engine;

class EngineGuiShape;
class EngineGuiContainer;
class EngineJoint;
class EngineMesh;
class EngineBox;
class Actor;
class PhysicShape;
class DynamicActor;
class Articulation;
class StaticActor;

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
	ACTOR,
	DYNAMIC_ACTOR,
	PHYSIC_SHAPE,
	ARTICULATION,
	STATIC_ACTOR,

};

class EngineObject {
    public:
        EngineObject(Engine* engine);
        virtual ~EngineObject();

		std::string 	getName(){return mName;}
		void 			setName(std::string name){mName = name;}
		//void 			setName(char * chr_ptr){mName = std::string(chr_ptr);}

		std::string		readUuid(){ return mUuid.toString(); }
		void			setUuid(std::string name){mUuid.fromString(name);}
		Uuid			getUuid(){ return mUuid; }

		Engine*			getEngine(){ return mEngine; }

		virtual ObjectType		getType(){ return OBJECT;}

		virtual void	guiUpdate(){}
		virtual void	physicUpdate(){}

		virtual EngineGuiShape*			isGuiShape(){return 0;}
		virtual EngineGuiContainer*		isGuiContainer(){return 0;}
		virtual EngineJoint*			isJoint(){return 0;}
		virtual EngineMesh*				isMesh(){return 0;}
		virtual EngineBox*				isBox(){return 0;}
		virtual Actor*					isActor(){return 0;}
		virtual DynamicActor*			isDynamicActor(){return 0;}
		virtual PhysicShape*			isPhysicShape(){return 0;}
		virtual Articulation*			isArticulation(){return 0;}
		virtual StaticActor*			isStaticActor(){return 0;}

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