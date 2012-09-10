#include "logger.h"

#include "actor.h"
#include "engine.h"
#include "physic_engine.h"
#include "physic_shape.h"

Actor::Actor(Engine* engine) :
	EngineGuiContainer(engine),
	mDoGuiUpdates(true)
	{
}

void	Actor::physicUpdate(){
}

void	Actor::guiUpdate(){
	if (mDoGuiUpdates) {
		EngineGuiContainer::setPosition(getPosition());
		EngineGuiContainer::setOrientation(getOrientation());
	}
}

Vec3	Actor::getPosition() {
    PxTransform t = getActor()->getGlobalPose();
	return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat	Actor::getOrientation() {
    PxTransform t = getActor()->getGlobalPose();
	return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void    Actor::setPosition(Vec3& vec3) {
    PxTransform t = getActor()->getGlobalPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    getActor()->setGlobalPose(t);
    wakeUp();
	EngineGuiContainer::setPosition(vec3);
}

void    Actor::setOrientation(Quat& quat) {
    PxTransform t = getActor()->getGlobalPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    getActor()->setGlobalPose(t);
    wakeUp();
	EngineGuiContainer::setOrientation(quat);
}

PhysicShape*		Actor::addBox(){
	PxShape* shape = getActor()->createShape( 
		PxBoxGeometry(Vec3(10,10,10).toPhysx() ), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	physicShape->createGuiBox();
	addShape(physicShape);
	resetMass();
	return physicShape;
}

PhysicShape*		Actor::addSphere(){
	PxShape* shape = getActor()->createShape( 
		PxSphereGeometry(10), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	physicShape->createGuiSphere();
	addShape(physicShape);
	resetMass();
	return physicShape;
}

PhysicShape*		Actor::addCapsule(){
	PxShape* shape = getActor()->createShape( 
		PxCapsuleGeometry(5,30), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	physicShape->createGuiCapsule(60,5);
	addShape(physicShape);
	resetMass();
	return physicShape;
}

