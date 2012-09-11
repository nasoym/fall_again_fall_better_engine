#include "logger.h"
#include "articulation.h"
#include "engine.h"
#include "physic_engine.h"

	#ifndef PI
		#define 	PI (3.14159265f)
	#endif
	#ifndef DEG2RAD
		#define 	DEG2RAD (PI / 180.0f)
	#endif 
	#ifndef RAD2DEG
		#define 	RAD2DEG (180.0f / PI)
	#endif 

Articulation::Articulation(Engine* engine) :
	Actor(engine),
	mParent(0),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{
	mArticulation = getEngine()->getPhysicsEngine()->getPhysics()->createArticulation();
	//mLink = mArticulation->createLink(NULL,PxTransform(PxVec3(1,1,1)));
	mLink = mArticulation->createLink(NULL,PxTransform(PxVec3(0,0,0)));
}

Articulation::Articulation(Engine* engine,Articulation* parentLink) :
	Actor(engine),
	mParent(parentLink),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{
	if(mParent) {
		mArticulation = mParent->getArticulation();
		mLink = mArticulation->createLink(mParent->getLink(),PxTransform(PxVec3(50,0,0)));
		mJoint = mLink->getInboundJoint();
	}
}

Articulation::~Articulation( ) {

}

Articulation* Articulation::addArticulation(){
	return new Articulation(getEngine(),this);
}

void   Articulation::addToScene( ) {
	if (!mParent){
		getEngine()->getPhysicsEngine()->getScene()->addArticulation(
			*mArticulation
		);
	}
}

Vec3   Articulation::getParentAnchor( ) {
	if (mJoint) {
		PxTransform t = mJoint->getParentPose();
		return Vec3(t.p.x,t.p.y,t.p.z);
	} else {
		return Vec3();
	}
}

Quat   Articulation::getParentAnchorOrientation( ) {
	if (mJoint) {
		PxTransform t = mJoint->getParentPose();
		return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
	} else {
		return Quat();
	}
}

Vec3   Articulation::getChildAnchor( ) {
	if (mJoint) {
		PxTransform t = mJoint->getChildPose();
		return Vec3(t.p.x,t.p.y,t.p.z);
	} else {
		return Vec3();
	}
}

Quat   Articulation::getChildAnchorOrientation( ) {
	if (mJoint) {
		PxTransform t = mJoint->getChildPose();
		return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
	} else {
		return Quat();
	}
}

void Articulation::setParentAnchor(Vec3 & vec3){
	if (mJoint) {
		PxTransform t = mJoint->getParentPose();
		t.p.x = vec3.X();
		t.p.y = vec3.Y();
		t.p.z = vec3.Z();
		mJoint->setParentPose(t);
		wakeUp();
	}
}

void Articulation::setChildAnchor(Vec3& vec3){
	if (mJoint) {
		PxTransform t = mJoint->getChildPose();
		t.p.x = vec3.X();
		t.p.y = vec3.Y();
		t.p.z = vec3.Z();
		mJoint->setChildPose(t);
		wakeUp();
	}
}

void Articulation::setParentAnchorOrientation(Quat & quat){
	if (mJoint) {
		PxTransform t = mJoint->getParentPose();
		t.q.x = quat.X();
		t.q.y = quat.Y();
		t.q.z = quat.Z();
		t.q.w = quat.W();
		mJoint->setParentPose(t);
		wakeUp();
	}
}

void Articulation::setChildAnchorOrientation(Quat & quat){
	if (mJoint) {
		PxTransform t = mJoint->getChildPose();
		t.q.x = quat.X();
		t.q.y = quat.Y();
		t.q.z = quat.Z();
		t.q.w = quat.W();
		mJoint->setChildPose(t);
		wakeUp();
	}
}

Quat Articulation::getMotorTarget() {
	if (mJoint) {
		PxQuat q = mJoint->getTargetOrientation();
		return Quat(q.w,q.x,q.y,q.z);
	} else {
		return Quat();
	}
}

void Articulation::setMotorTarget(Quat & quat) {
	if (mJoint) {
		mJoint->setTargetOrientation(quat.toPhysx());
		wakeUp();
	}
}

void Articulation::setSpring(float spring){
	if (mJoint) {
		mJoint->setSpring(spring);
	}
}

float Articulation::getSpring(){
	if (mJoint) {
		return mJoint->getSpring();
	} else { 
		return 0;
	}
}

void Articulation::setDamping(float damping){
	if (mJoint) {
		mJoint->setDamping(damping);
	}
}

float Articulation::getDamping(){
	if (mJoint) {
		return mJoint->getDamping();
	} else { 
		return 0;
	}
}

void Articulation::setSwingLimits(float yLimit,float zLimit){
	if (mJoint) {
		mJoint->setSwingLimit(
			yLimit * DEG2RAD,
			zLimit * DEG2RAD
			);
		mJoint->setSwingLimitEnabled(true);
		wakeUp();
	}
}

float Articulation::getSwingYLimit(){
	if (mJoint) {
		PxReal	yLimit;
		PxReal	zLimit;
		mJoint->getSwingLimit(yLimit,zLimit);
		return yLimit * RAD2DEG;
	} else {
		return 0;
	}
}

float Articulation::getSwingZLimit(){
	if (mJoint) {
		PxReal	yLimit;
		PxReal	zLimit;
		mJoint->getSwingLimit(yLimit,zLimit);
		return zLimit * RAD2DEG;
	} else {
		return 0;
	}
}

void Articulation::setSwingLimitEnabled(){
	if (mJoint) {
		mJoint->setSwingLimitEnabled(true);
		wakeUp();
	}
}

void Articulation::setSwingLimitDisabled(){
	if (mJoint) {
		mJoint->setSwingLimitEnabled(false);
		wakeUp();
	}
}


void Articulation::setTwistLimitEnabled(){
	if (mJoint) {
		mJoint->setTwistLimitEnabled(true);
		wakeUp();
	}
}

void Articulation::setTwistLimitDisabled(){
	if (mJoint) {
		mJoint->setTwistLimitEnabled(false);
		wakeUp();
	}
}

void Articulation::setTwistLimits(float lowerLimit,float upperLimit){
	if (mJoint) {
		mJoint->setTwistLimit(
			lowerLimit * DEG2RAD,
			upperLimit * DEG2RAD
			);
		mJoint->setTwistLimitEnabled(true);
		wakeUp();
	}
}

float Articulation::getTwistLowerLimit(){
	if (mJoint) {
		PxReal	lowerLimit;
		PxReal	upperLimit;
		mJoint->getTwistLimit(lowerLimit,upperLimit);
		return lowerLimit * RAD2DEG;
	} else {
		return 0;
	}
}

float Articulation::getTwistUpperLimit(){
	if (mJoint) {
		PxReal	lowerLimit;
		PxReal	upperLimit;
		mJoint->getTwistLimit(lowerLimit,upperLimit);
		return upperLimit * RAD2DEG;
	} else {
		return 0;
	}
}

void	Articulation::addForce(Vec3 force){
	mLink->addForce(
		force.toPhysx(),
		PxForceMode::eIMPULSE
		);
}

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


