#ifndef _PHYSIC_STATIC_H
#define _PHYSIC_STATIC_H

#include "baseactor.h"

#include "PxPhysicsAPI.h"
using namespace physx;

#include "engine_physic.h"
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

        virtual PxRigidActor*     	getBody();

		Vec3				getPosition();
		Quat				getOrientation();
		Vec3				getSize();

		void				setPosition(Vec3);
		void				setOrientation(Quat);
		void				setSize(Vec3);
};
#endif

