#ifndef _DYNAMIC_ACTOR_H
#define _DYNAMIC_ACTOR_H

#include "logger.h"

#include "PxPhysicsAPI.h"
using namespace physx;

class Engine;

#include "actor.h"

class DynamicActor : public Actor {

    public:
        DynamicActor(Engine*,Vec3&);
        ~DynamicActor();

		virtual DynamicActor*	isDynamicActor(){return this;}
		virtual ObjectType		getType(){return DYNAMIC_ACTOR;}

        virtual PxRigidActor*  	getActor(){return mBody;}

		virtual void        	wakeUp();

		virtual void			addForce(Vec3);	

		virtual void			setMass(float mass);
		virtual void			resetMass();
		virtual float			getMass();

		void 					setSolverIterations(int i1,int i2);

	private:
        PxRigidDynamic*     	mBody;
};
#endif
