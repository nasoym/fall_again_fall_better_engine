#include "static_actor.h"
#include "engine.h"
#include "physic_engine.h"

StaticActor::StaticActor(Engine* engine, Vec3 & position) :
	Actor(engine),
	mBody(0),
	mAddedToScene(false)
	{
    mBody = (getEngine()->getPhysicsEngine()->getPhysics())->createRigidStatic( 
		PxTransform(position.toPhysx()) );
    (getEngine()->getPhysicsEngine()->getScene())->addActor(*mBody);
}

StaticActor::~StaticActor( ){
    mBody->release();
    mBody = 0;
}


/*
PhysicShape*		StaticActor::addBox(Vec3& vec3){
	PhysicShape* shape = Actor::addBox(vec3);
	return shape;
}
PhysicShape*		StaticActor::addSphere(Vec3& vec3){
	PhysicShape* shape = Actor::addSphere(vec3);
	return shape;
}
PhysicShape*		StaticActor::addCapsule(Vec3& vec3){
	PhysicShape* shape = Actor::addCapsule(vec3);
	return shape;
}
*/

void    StaticActor::setPosition(Vec3& vec3) {
	(getEngine()->getPhysicsEngine()->getScene())->removeActor(*mBody);
    PxTransform t = getActor()->getGlobalPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    getActor()->setGlobalPose(t);
	(getEngine()->getPhysicsEngine()->getScene())->addActor(*mBody);
}

void    StaticActor::setOrientation(Quat& quat) {
	(getEngine()->getPhysicsEngine()->getScene())->removeActor(*mBody);
    PxTransform t = getActor()->getGlobalPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    getActor()->setGlobalPose(t);
	(getEngine()->getPhysicsEngine()->getScene())->addActor(*mBody);
}
