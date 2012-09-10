#ifndef _PHYSIC_SHAPE_H
	#define _PHYSIC_SHAPE_H

#include "PxPhysicsAPI.h"
using namespace physx;

class Engine;
class Actor;

#include "engine_gui_shape.h"

#include <Ogre.h>
using namespace Ogre;

#include "ProceduralStableHeaders.h"
#include "Procedural.h"

class PhysicShape : public EngineGuiShape {
	
	public:
		PhysicShape(Engine*,Actor*,PxShape*);
		virtual ~PhysicShape();

		virtual PhysicShape*				isPhysicShape(){return this;}
		virtual ObjectType					getType(){ return PHYSIC_SHAPE;}

	public:
		void 	createGuiBox();
		void 	createGuiSphere();
		void 	createGuiCapsule(float,float);
		void 	updateGuiCapsule(float,float);

		//virtual void        setPosition(Vec3& vec3);

		virtual void        setLocalPosition(Vec3& vec3);
		virtual Vec3    	getLocalPosition();

		virtual void        setLocalOrientation(Quat& quat);
		virtual Quat 		getLocalOrientation();

		virtual void        setLocalSize(Vec3& vec3);
		virtual Vec3    	getLocalSize();

	private:
        PxShape*            mShape;
		Actor*				mActor;
		Mesh*				mMesh;

};
#endif
