#ifndef _PHYSIC_STATIC_H
#define _PHYSIC_STATIC_H

#include "physic_body.h"

#include "PxPhysicsAPI.h"
using namespace physx;

class PhysicsEngine;

#include "math3d.h"

class PhysicStatic : public PhysicBody {
    private:
        PhysicsEngine*      mEngine;
        PxRigidStatic*      mBody;
        PxShape*            mShape;

    public:
        PhysicStatic(PhysicsEngine*, Vec3&, Vec3&);
        virtual ~PhysicStatic();
        virtual PxRigidActor*     	getBody(){return mBody;}

		Vec3				getSize();
		void				setSize(Vec3);
};
#endif

