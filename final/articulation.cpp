#include "logger.h"
#include "articulation.h"
#include "engine.h"
#include "physic_engine.h"

Articulation::Articulation(Engine* engine) :
	Actor(engine),
	mParent(0),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{
	mArticulation = getEngine()->getPhysicsEngine()->getPhysics()->createArticulation();
	mLink = mArticulation->createLink(0,PxTransform());
	mJoint = mLink->getInboundJoint();
}

Articulation::Articulation(Engine* engine,Articulation* parentLink) :
	Actor(engine),
	mParent(parentLink),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{
	if(mParent) mArticulation = mParent->getArticulation();
	mLink = mArticulation->createLink(mParent->getLink(),PxTransform());
	mJoint = mLink->getInboundJoint();
}

Articulation::~Articulation( ) {

}


Vec3   Articulation::getParentAnchor( ) {
    PxTransform t = mJoint->getParentPose();
    return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat   Articulation::getParentAnchorOrientation( ) {
    PxTransform t = mJoint->getParentPose();
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

Vec3   Articulation::getChildAnchor( ) {
    PxTransform t = mJoint->getChildPose();
    return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat   Articulation::getChildAnchorOrientation( ) {
    PxTransform t = mJoint->getChildPose();
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void Articulation::setParentAnchor(Vec3 & vec3){
    PxTransform t = mJoint->getParentPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mJoint->setParentPose(t);
    wakeUp();
}

void Articulation::setChildAnchor(Vec3& vec3){
    PxTransform t = mJoint->getChildPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mJoint->setChildPose(t);
    wakeUp();
}

void Articulation::setParentAnchorOrientation(Quat & quat){
    PxTransform t = mJoint->getParentPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mJoint->setParentPose(t);
    wakeUp();
}

void Articulation::setChildAnchorOrientation(Quat & quat){
    PxTransform t = mJoint->getChildPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mJoint->setChildPose(t);
    wakeUp();
}

Quat Articulation::getMotorTarget() {
    PxQuat q = mJoint->getTargetOrientation();
    return Quat(q.w,q.x,q.y,q.z);
}

void Articulation::setMotorTarget(Quat & quat) {
    mJoint->setTargetOrientation(quat.toPhysx());
    wakeUp();
}

void Articulation::setSpring(float spring){
	mJoint->setSpring(spring);
}

float Articulation::getSpring(){
	return mJoint->getSpring();
}

void Articulation::setDamping(float damping){
	mJoint->setDamping(damping);
}

float Articulation::getDamping(){
	return mJoint->getDamping();
}


/*
virtual void  setSwingLimit (PxReal yLimit, PxReal zLimit)=0 
  set the extents of the cone limit. The extents are measured in the frame of the parent. 
 
virtual void  getSwingLimit (PxReal &yLimit, PxReal &zLimit) const =0 
  get the extents for the swing limit cone  

void  setSwingLimitEnabled (bool enabled)=0 
  set the flag which enables the swing limit  
*/



void Articulation::resetMass(){
    PxRigidBodyExt::updateMassAndInertia(*mLink, 1.0f);
    wakeUp();
}

void Articulation::setMass(float mass){
	mLink->setMass(mass);
    wakeUp();
}

float Articulation::getMass(){
	return mLink->getMass();
}

void	Articulation::wakeUp(){
	mArticulation->wakeUp();
}

void	Articulation::setSolverIterationCounts(float posIters, float velIters){
	mArticulation->setSolverIterationCounts(posIters,velIters);
}
//virtual void  getSolverIterationCounts (PxU32 &minPositionIters, PxU32 &minVelocityIters) const =0 


