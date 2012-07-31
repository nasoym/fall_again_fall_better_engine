#ifndef _PHYSIC_BOX_H
	#define _PHYSIC_BOX_H

#include "body_physic.h"

#include "PxPhysicsAPI.h"
using namespace physx;

class PhysicsEngine;

#include "math3d.h"

class PhysicBox : public PhysicBody {
    private:
        PhysicsEngine*      mEngine;
        PxRigidDynamic*     mBody;
        PxShape*            mShape;

    public:
        PhysicBox(PhysicsEngine*, Vec3&, Vec3&);
        virtual ~PhysicBox();

        virtual PxRigidActor*     	getBody(){return mBody;}
        virtual void                wakeUp();

		virtual Vec3				getSize();
		virtual void				setSize(Vec3);
};
#endif
