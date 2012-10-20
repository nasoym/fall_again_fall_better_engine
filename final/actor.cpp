#include "logger.h"

#include "actor.h"
#include "engine.h"
#include "physic_engine.h"
#include "physic_shape.h"
#include "joint.h"

Actor::Actor(Engine* engine) :
	GuiContainer(engine),
	mDoGuiUpdates(true),
	mMass(1000)
	{
}


void	Actor::enableCollisions(){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		if ( (*iter)->isPhysicShape() ) {
			(*iter)->isPhysicShape()->enableCollisions();
		}
	}
}

void	Actor::dissableCollisions(){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		if ( (*iter)->isPhysicShape() ) {
			(*iter)->isPhysicShape()->dissableCollisions();
		}
	}
}

void	Actor::removeFromScene(){
    (getEngine()->getPhysicsEngine()->getScene())->removeActor(*getActor());
}

void	Actor::moveBackToScene(){
    (getEngine()->getPhysicsEngine()->getScene())->addActor(*getActor());
}

void	Actor::physicUpdate(){
}

int					Actor::howManyPhysicShapes(){
	return howManyShapes();
}

PhysicShape*		Actor::getPhysicShapeByIndex(int index){
	GuiShape* shape = getShapeByIndex(index);
	if (shape->isPhysicShape()) {
		return shape->isPhysicShape();
	}
	return 0;
}

void	Actor::guiUpdate(){
	if (mDoGuiUpdates) {
		GuiContainer::setPosition(getPosition());
		GuiContainer::setOrientation(getOrientation());
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
	GuiContainer::setPosition(vec3);
}

void    Actor::setOrientation(Quat& quat) {
    PxTransform t = getActor()->getGlobalPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    getActor()->setGlobalPose(t);
    wakeUp();
	GuiContainer::setOrientation(quat);
}

PhysicShape*		Actor::addBox(Vec3& vec3){
	PxShape* shape = getActor()->createShape( 
		PxBoxGeometry(vec3.toPhysx() ), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	physicShape->createGuiBox(vec3);
	physicShape->setBoxShape();
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
	physicShape->setSphereShape();
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
	physicShape->setCapsuleShape();
	addShape(physicShape);
	resetMass();
    wakeUp();
	return physicShape;
}

PhysicShape*		Actor::addPlane(){
	PxShape* shape = getActor()->createShape( 
        PxPlaneGeometry(), 
		*(getEngine()->getPhysicsEngine()->getMaterial()) 
		);
	PhysicShape* physicShape = new PhysicShape(getEngine(),this,shape);
	physicShape->createGuiBox(Vec3(1,1,1));
	physicShape->setPlaneShape();
	addShape(physicShape);
	return physicShape;
}

void    Actor::deleteAllJoints() {
	std::vector<Joint*>::iterator  mJointsIterator;
	for (mJointsIterator = mJoints.begin(); 
		mJointsIterator != mJoints.end(); ++mJointsIterator) {
		delete (*mJointsIterator);
	}
	mJoints.clear();
}

void    Actor::deleteJoint(Joint* joint) {
	std::vector<Joint*>::iterator  mJointsIterator;
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

void    Actor::addJoint(Joint* joint){
	mJoints.push_back(joint);
}

Joint*  Actor::getJoint(int index) {
	return mJoints[index];
}



