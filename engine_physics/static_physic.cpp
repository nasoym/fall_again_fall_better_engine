#include "static_physic.h"
#include "logger.h"

PhysicStatic::PhysicStatic(PhysicsEngine* engine, Vec3& position,Vec3& size) :
	PhysicBody(),
	mEngine(engine),
	mBody(0),
	mShape(0)
	{
    mBody = (mEngine->getPhysics())->createRigidStatic( PxTransform(position.toPhysx()) );
    mShape = mBody->createShape( PxBoxGeometry(size.toPhysx()), *(mEngine->getMaterial()) );
    (mEngine->getScene())->addActor(*mBody);
}

PhysicStatic::~PhysicStatic( ){
    deleteAllJoints();
    mBody->release();
    mBody = 0;
}

PxRigidActor*    PhysicStatic::getBody() {
    return mBody;
}

Vec3	PhysicStatic::getPosition() {
    PxTransform t = mBody->getGlobalPose();
	return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat	PhysicStatic::getOrientation() {
    PxTransform t = mBody->getGlobalPose();
	return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

Vec3	PhysicStatic::getSize() {
	PxBoxGeometry	boxGeometry;
	if (mShape->getBoxGeometry(boxGeometry)) {
		return Vec3(boxGeometry.halfExtents);
	}
	return Vec3();
}

void    PhysicStatic::setPosition(Vec3 vec3) {
    PxTransform t = mBody->getGlobalPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mBody->setGlobalPose(t);
}

void    PhysicStatic::setOrientation(Quat quat) {
    PxTransform t = mBody->getGlobalPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mBody->setGlobalPose(t);
}

void    PhysicStatic::setSize(Vec3 vec3) {
    mShape->setGeometry(PxBoxGeometry(
		vec3.toPhysx()
		));
}


