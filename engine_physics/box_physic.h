#ifndef _PHYSIC_BOX_H
	#define _PHYSIC_BOX_H

#include "baseactor.h"

#include "PxPhysicsAPI.h"
using namespace physx;

#include "engine_physic.h"
class PhysicsEngine;

class PhysicBox : public BaseActor {
    private:
        PhysicsEngine*      mEngine;
        float               mSizeX;
        float               mSizeY;
        float               mSizeZ;

        PxRigidDynamic*     mBody;
        PxShape*            mShape;

    public:
        PxRigidActor*     	getBody();
        void                wakeUp();

    public: // python
        PhysicBox(PhysicsEngine*, PxVec3, PxVec3);
        ~PhysicBox();

};
#endif
