
#include "plane_physic.h"

//PhysicPlane::PhysicPlane(Engine* engine, object pos, object quat):
PhysicPlane::PhysicPlane(PhysicsEngine* engine, PxVec3 position, PxQuat orientation):
    mEngine(engine)  
{
	mBody = (mEngine->getPhysics())->createRigidStatic(
        PxTransform(position, orientation)
        );
	PxShape* shape = mBody->createShape(
        PxPlaneGeometry(), 
        *(mEngine->getMaterial())
        );
    (mEngine->getScene())->addActor(*mBody);
}

PhysicPlane::~PhysicPlane( ){
    mBody->release();
    mBody = 0;
}
