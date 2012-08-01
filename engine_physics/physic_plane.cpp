#include "logger.h"
#include "physic_plane.h"
#include "physic_engine.h"

PhysicPlane::PhysicPlane(PhysicsEngine* engine, PxVec3 position, PxQuat orientation):
    mEngine(engine)  
{
    Logger::debug(format("creating PhysicPlane: %1% ") % this);
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
    Logger::debug(format("delete PhysicPlane: %1% ") % this);
    mBody->release();
    mBody = 0;
}
