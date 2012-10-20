#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "stdio.h"
#include <string>
#include "uuid.h"

class Engine;

class GuiShape;
class GuiContainer;
class MeshObject;
class GuiCube;
class Actor;
class PhysicShape;
class DynamicActor;
class Articulation;
class StaticActor;
class Joint;

enum ObjectType {
	OBJECT,
	GUICONTAINER,
	GUISHAPE,
    MESH,
	JOINT,
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

		virtual GuiShape*			isGuiShape(){return 0;}
		virtual GuiContainer*		isGuiContainer(){return 0;}
		virtual MeshObject*				isMesh(){return 0;}
		virtual GuiCube*				isBox(){return 0;}
		virtual Actor*					isActor(){return 0;}
		virtual DynamicActor*			isDynamicActor(){return 0;}
		virtual PhysicShape*			isPhysicShape(){return 0;}
		virtual Articulation*			isArticulation(){return 0;}
		virtual StaticActor*			isStaticActor(){return 0;}
		virtual Joint*					isJoint(){return 0;}

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
