#include "box_physic.h"
#include "logger.h"

PhysicBox::PhysicBox(PhysicsEngine* engine, PxVec3 position,PxVec3 size) :
	BaseActor(),
	mEngine(engine),
	mBody(0),
	mShape(0)
	{
    Logger::debug(format("creating PhysicBox: %1% ") % this);
    mBody = (mEngine->getPhysics())->createRigidDynamic( PxTransform(position) );
    mShape = mBody->createShape( PxBoxGeometry(size), *(mEngine->getMaterial()) );
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    (mEngine->getScene())->addActor(*mBody);
}

PhysicBox::~PhysicBox( ){
    Logger::debug(format("deleting PhysicBox: %p ") % this);
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

Vec3	PhysicBox::getPosition() {
    PxTransform t = mBody->getGlobalPose();
	return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat	PhysicBox::getOrientation() {
    PxTransform t = mBody->getGlobalPose();
	return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

Vec3	PhysicBox::getSize() {
	PxBoxGeometry	boxGeometry;
	if (mShape->getBoxGeometry(boxGeometry)) {
		return Vec3(boxGeometry.halfExtents);
	}
	return Vec3();
}

void    PhysicBox::setPosition(Vec3 vec3) {
    PxTransform t = mBody->getGlobalPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mBody->setGlobalPose(t);
    wakeUp();
}

void    PhysicBox::setOrientation(Quat quat) {
    PxTransform t = mBody->getGlobalPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mBody->setGlobalPose(t);
    wakeUp();
}

void    PhysicBox::setSize(Vec3 vec3) {
    mShape->setGeometry(PxBoxGeometry(
		vec3.toPhysx()
		));
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    wakeUp();
}


