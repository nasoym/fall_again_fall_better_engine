#include "box_physic.h"
#include "logger.h"

PhysicBox::PhysicBox(PhysicsEngine* engine, PxVec3 position,PxVec3 size) :
	mEngine(engine)  
	{
    mBody = (mEngine->getPhysics())->createRigidDynamic( PxTransform(position) );
    mShape = mBody->createShape( PxBoxGeometry(size), *(mEngine->getMaterial()) );
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    (mEngine->getScene())->addActor(*mBody);
}

PhysicBox::~PhysicBox( ){
    deleteAllJoints();
    mBody->release();
    mBody = 0;
}

PxRigidActor*    PhysicBox::getBody() {
    return mBody;
}

void    PhysicBox::wakeUp() {
    mBody->wakeUp();
}

