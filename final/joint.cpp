#include "engine.h"
#include "joint.h"
#include "physic_engine.h"
#include "actor.h"

Joint::Joint(Engine* engine,Actor* actor1,Actor* actor2):
		GuiContainer(engine),
        mActor1(actor1),
        mActor2(actor2),
        mMotorOn(false),
        mDMotorSpring(70000),
        mDMotorDamping(10000),
        mDMotorAccel(true),
        mDContactDistance(0.01f)
    {
    createJoint();

    mActor1->addJoint(this);
    mActor2->addJoint(this);
	//body1->addJoint(this);
	//body2->addJoint(this);
}


Joint::~Joint(){
    unregisterJoint();
    //mActor1->deleteJoint(this);
    //mActor2->deleteJoint(this);
}

Actor*		Joint::getBody1(){
	return mActor1;
}
Actor*		Joint::getBody2(){
	return mActor2;
}

void        Joint::setAnchor1Size(Vec3& vec3){
	setAnchor1(vec3 * mActor1->getSize() );
}

void        Joint::setAnchor2Size(Vec3& vec3){
	setAnchor2(vec3 * mActor2->getSize() );
}

Vec3        Joint::getAnchor1Size(){
	return getAnchor1() / mActor1->getSize();
}

Vec3        Joint::getAnchor2Size(){
	return getAnchor2() / mActor2->getSize();
}

void	Joint::guiUpdate(){
	//TODO check if any body is awake
	setPosition(getPosition());
	setOrientation(getOrientation());
}

Vec3    	Joint::getPosition(){
	Vec3	jointPosition = mActor1->getPosition();
	jointPosition += mActor1->getOrientation() * getAnchor1();
	return jointPosition;
}

Quat Joint::getOrientation(){
	Quat 	jointOrientation;
	jointOrientation = mActor1->getOrientation() * getAnchor1Orientation();
	return jointOrientation;
}




void Joint::recreateJoint() {
    unregisterJoint();
    createJoint();
}

void Joint::createJoint(){
    mJoint = PxD6JointCreate(
        //*mEngine->getPhysics(), 
		*(getEngine()->getPhysicsEngine()->getPhysics()),
        mActor1->getActor(),
        PxTransform(PxVec3(
            0,0,0)),
        mActor2->getActor(),
        PxTransform(PxVec3(
            0,0,0))
        );
/*
    mJoint->setMotion(PxD6Axis::eX, PxD6Motion::eLOCKED);

    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);

    mJoint->setMotion(PxD6Axis::eX, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eY, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eZ, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eY, PxD6Motion::eFREE);
    mJoint->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);

    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eFREE);
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eFREE);

    mJoint->setMotion(PxD6Axis::eX, PxD6Motion::eLOCKED);
    mJoint->setMotion(PxD6Axis::eY, PxD6Motion::eLOCKED);
    mJoint->setMotion(PxD6Axis::eZ, PxD6Motion::eLOCKED);
*/

    mJoint->setMotion(PxD6Axis::eTWIST, PxD6Motion::eLOCKED);
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);

    //mJoint->setLinearLimit(PxJointLimit(0.0f,0.0f));
    //mJoint->setTwistLimit(PxJointLimitPair(0,0,0));
    mJoint->setSwingLimit(PxJointLimitCone(0,0,mDContactDistance));


	//mJoint->setConstraintFlag(PxConstraintFlag::ePROJECTION,true);

    //Logger::debug(format("ProjectionLinearTolerance: %p ") % mJoint->getProjectionLinearTolerance());
    //Logger::debug(format("ProjectionAngularTolerance: %p ") % mJoint->getProjectionAngularTolerance());


	//mJoint->setProjectionLinearTolerance(0);
	//mJoint->setProjectionAngularTolerance(0);




    updateBodies();
}

void Joint::dLockSwing1() {
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLOCKED);
}

void Joint::dUnLockSwing1() {
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
}

void Joint::dLockSwing2() {
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLOCKED);
}

void Joint::dUnLockSwing2() {
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);
}

void Joint::unregisterJoint() {
    mJoint->release();
    mJoint = 0;
}

Actor*  Joint::getActor1(){
    return mActor1;
}

Actor*  Joint::getActor2(){
    return mActor2;
}

Vec3   Joint::getAnchor1( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat   Joint::getAnchor1Orientation( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

Vec3   Joint::getAnchor2( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat   Joint::getAnchor2Orientation( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void Joint::setAnchor1(Vec3 & vec3){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR0, t);
    updateBodies();
}

void Joint::setAnchor2(Vec3& vec3){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR1, t);
    updateBodies();
}

void Joint::setAnchor1Orientation(Quat & quat){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR0, t);
    updateBodies();
}

void Joint::setAnchor2Orientation(Quat & quat){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR1, t);
    updateBodies();
}

void Joint::setLimits(float yLimit, float zLimit) {
    float minVal = 0.0000001f;
    if (yLimit == 0 && zLimit == 0 ) {
        mJoint->setSwingLimit(PxJointLimitCone(
            minVal * DEG2RAD,
            minVal * DEG2RAD,
            mDContactDistance));
    } else if (yLimit == 0 ) {
        mJoint->setSwingLimit(PxJointLimitCone(
            minVal * DEG2RAD,
            zLimit * DEG2RAD,
            mDContactDistance));
    } else if (zLimit == 0 ) {
        mJoint->setSwingLimit(PxJointLimitCone(
            yLimit * DEG2RAD,
            minVal * DEG2RAD,
            mDContactDistance));
    } else {
        mJoint->setSwingLimit(PxJointLimitCone(
            yLimit * DEG2RAD,
            zLimit * DEG2RAD,
            mDContactDistance));
    }
    updateBodies();
}

float Joint::getZLimit() {
    PxJointLimitCone limits = mJoint->getSwingLimit();
	return limits.zAngle * RAD2DEG;
}

float Joint::getYLimit() {
    PxJointLimitCone limits = mJoint->getSwingLimit();
	return limits.yAngle * RAD2DEG;
}

void Joint::dsetMotorSpring(float spring) {
    mDMotorSpring = spring;
	if (isMotorOn()){
		setMotorOn();
	}
}

void Joint::dsetMotorDamping(float damping) {
    mDMotorDamping = damping;
	if (isMotorOn()){
		setMotorOn();
	}
}

void Joint::dsetMotorAccel(bool accel) {
    mDMotorAccel = accel;
	if (isMotorOn()){
		setMotorOn();
	}
}

void Joint::dsetContactDistance(float value) {
    mDContactDistance = value;
}

void Joint::dResetLimits() {
    PxJointLimitCone limits = mJoint->getSwingLimit();
    mJoint->setSwingLimit(PxJointLimitCone(
        limits.yAngle,
        limits.zAngle,
        mDContactDistance));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

void Joint::setMotorOn() {
    mMotorOn = true;
    mJoint->setDrive(PxD6Drive::eSWING,PxD6JointDrive(
        mDMotorSpring,
        mDMotorDamping,
        PX_MAX_F32,
        mDMotorAccel
        ));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

void Joint::setMotorValues(float spring,float damping,bool accel) {
    mMotorOn = true;
    mJoint->setDrive(PxD6Drive::eSWING,PxD6JointDrive(
        spring,
        damping,
        PX_MAX_F32,
        accel
        ));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

void Joint::setMotorOff() {
    mMotorOn = false;
    mJoint->setDrive(PxD6Drive::eSWING,PxD6JointDrive(
        0,
        0,
        PX_MAX_F32
        ));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

bool Joint::isMotorOn() {
//    PxD6JointDrive drive = mJoint->getDrive(PxD6Drive::eSWING);
//    printf("drive spring: %.3f \n",drive.spring);
//    printf("drive damping: %.3f \n",drive.damping);
//    printf("drive forceLimit: %.3f \n",drive.forceLimit);
    return mMotorOn;
}

void Joint::setMotorStrength(float strength) {
    //TODO set motor strength
}

float Joint::getMotorStrength() {
    //TODO get motor strength
    return 1.0f;
}

void Joint::setMotorTarget(Quat & quat) {
    mJoint->setDrivePosition(PxTransform(quat.toPhysx()));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

Quat Joint::getMotorTarget() {
    PxTransform t = mJoint->getDrivePosition();
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void Joint::updateBodies() {
    mActor1->wakeUp();
    mActor2->wakeUp();
}







