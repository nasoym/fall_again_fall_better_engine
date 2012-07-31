#ifndef _PHYSIC_PLANE_H
	#define _PHYSIC_PLANE_H

#include "PxPhysicsAPI.h"
using namespace physx;

class PhysicsEngine;

class PhysicPlane {
	public:
		PhysicPlane(PhysicsEngine*, PxVec3, PxQuat);
		~PhysicPlane();
	private:
        PxRigidStatic*  mBody;
		PhysicsEngine*  mEngine;
};
#endif

