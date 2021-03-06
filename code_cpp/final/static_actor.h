#ifndef _STATIC_ACTOR_H
#define _STATIC_ACTOR_H

#include "logger.h"

#include "PxPhysicsAPI.h"
using namespace physx;

class Engine;

#include "actor.h"

class StaticActor : public Actor {
    public:
        StaticActor(Engine*,Vec3&);
        ~StaticActor();

		virtual PhysicShape*		addBox(Vec3&);
		virtual PhysicShape*		addSphere(Vec3&);
		virtual PhysicShape*		addCapsule(Vec3&);
		virtual PhysicShape*		addPlane();

		virtual StaticActor*	isStaticActor(){return this;}
		virtual ObjectType		getType(){return STATIC_ACTOR;}

        virtual PxRigidActor*   getActor(){return mBody;}

		virtual void        	setPosition(Vec3& vec3);
		virtual void        	setOrientation(Quat& quat);

	private:
        PxRigidStatic*      	mBody;
		bool					mAddedToScene;
};
#endif
