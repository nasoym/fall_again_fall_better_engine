#include "logger.h"

#include "actor.h"
#include "engine.h"
#include "physic_engine.h"
#include "physic_shape.h"
#include "engine_joint.h"

Actor::Actor(Engine* engine) :
	EngineGuiContainer(engine),
	mDoGuiUpdates(true)
	{
}

void	Actor::physicUpdate(){
}

int					Actor::howManyPhysicShapes(){
	return howManyShapes();
}

PhysicShape*		Actor::getPhysicShapeByIndex(int index){
	EngineGuiShape* shape = getShapeByIndex(index);
	if (shape->isPhysicShape()) {
		return shape->isPhysicShape();
	}
	return 0;
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

PhysicShape*		Actor::addBox(Vec3& vec3){
	PxShape* shape = getActor()->createShape( 
		PxBoxGeometry(vec3.toPhysx() ), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	physicShape->createGuiBox(vec3);
	addShape(physicShape);
	resetMass();
	wakeUp();	
	return physicShape;
}

PhysicShape*		Actor::addSphere(Vec3& vec3){
	PxShape* shape = getActor()->createShape( 
		PxSphereGeometry(vec3.x), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	physicShape->createGuiSphere(vec3);
	addShape(physicShape);
	resetMass();
    wakeUp();
	return physicShape;
}

PhysicShape*		Actor::addCapsule(Vec3& vec3){
	PxShape* shape = getActor()->createShape( 
		PxCapsuleGeometry(vec3.y,vec3.x), 
		//PxCapsuleGeometry(5,30), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	//physicShape->createGuiCapsule(60,5);
	physicShape->createGuiCapsule(vec3);
	addShape(physicShape);
	resetMass();
    wakeUp();
	return physicShape;
}


void    Actor::deleteAllJoints() {
	std::vector<EngineJoint*>::iterator  mJointsIterator;
	for (mJointsIterator = mJoints.begin(); 
		mJointsIterator != mJoints.end(); ++mJointsIterator) {
		delete (*mJointsIterator);
	}
	mJoints.clear();
}

void    Actor::deleteJoint(EngineJoint* joint) {
	std::vector<EngineJoint*>::iterator  mJointsIterator;
	for (mJointsIterator = mJoints.begin(); 
		mJointsIterator != mJoints.end(); ++mJointsIterator) {
		if ( (*mJointsIterator) == joint ){
			delete (*mJointsIterator);
			mJoints.erase( mJointsIterator);
			break;
		}
	}
}

int     Actor::howManyJoints() {
	return mJoints.size();
}

void    Actor::addJoint(EngineJoint* joint){
	mJoints.push_back(joint);
}

EngineJoint*  Actor::getJoint(int index) {
	return mJoints[index];
}



