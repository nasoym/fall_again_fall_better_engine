#ifndef _PHYSIC_BOX_H
	#define _PHYSIC_BOX_H

#include "baseactor.h"

#include "PxPhysicsAPI.h"
using namespace physx;

#include "engine_physic.h"
class PhysicsEngine;

#include "math3d.h"

class PhysicBox : public BaseActor {
    private:
        PhysicsEngine*      mEngine;
        PxRigidDynamic*     mBody;
        PxShape*            mShape;

    public:
        PhysicBox(PhysicsEngine*, Vec3&, Vec3&);
        virtual ~PhysicBox();

        virtual PxRigidActor*     	getBody();
        virtual void                wakeUp();

		Vec3				getPosition();
		Quat				getOrientation();
		Vec3				getSize();

		void				setPosition(Vec3);
		void				setOrientation(Quat);
		void				setSize(Vec3);
};
#endif
