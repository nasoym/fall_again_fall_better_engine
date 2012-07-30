#include "joint_physic.h"


PhysicJoint::PhysicJoint(PhysicsEngine* engine,PhysicBody* actor1,PhysicBody* actor2):
        mEngine(engine),
        mActor1(actor1),
        mActor2(actor2),
        mMotorOn(false),
        mDMotorSpring(70000),
        mDMotorDamping(10000),
        mDMotorAccel(true),
        mDContactDistance(9.01f)
    {
    mActor1->addJoint(this);
    mActor2->addJoint(this);
    createJoint();
}

PhysicJoint::~PhysicJoint(){
    mActor1->deleteJoint(this);
    mActor2->deleteJoint(this);
    unregisterJoint();
}

void PhysicJoint::recreateJoint() {
    unregisterJoint();
    createJoint();
}

void PhysicJoint::createJoint(){
    mJoint = PxD6JointCreate(
        *mEngine->getPhysics(), 
        mActor1->getBody(),
        PxTransform(PxVec3(
            0,0,0)),
        mActor2->getBody(),
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

    updateBodies();
}

void PhysicJoint::dLockSwing1() {
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLOCKED);
}

void PhysicJoint::dUnLockSwing1() {
    mJoint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eLIMITED);
}

void PhysicJoint::dLockSwing2() {
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLOCKED);
}

void PhysicJoint::dUnLockSwing2() {
    mJoint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eLIMITED);
}

void PhysicJoint::unregisterJoint() {
    mJoint->release();
    mJoint = 0;
}

PhysicBody*  PhysicJoint::getActor1(){
    return mActor1;
}

PhysicBody*  PhysicJoint::getActor2(){
    return mActor2;
}

Vec3   PhysicJoint::getAnchor1( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat   PhysicJoint::getAnchor1Orientation( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

Vec3   PhysicJoint::getAnchor2( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat   PhysicJoint::getAnchor2Orientation( ) {
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void PhysicJoint::setAnchor1(Vec3 & vec3){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR0, t);
    updateBodies();
}

void PhysicJoint::setAnchor2(Vec3& vec3){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR1, t);
    updateBodies();
}

void PhysicJoint::setAnchor1Orientation(Quat & quat){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR0);
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR0, t);
    updateBodies();
}

void PhysicJoint::setAnchor2Orientation(Quat & quat){
    PxTransform t = mJoint->getLocalPose(PxJointActorIndex::eACTOR1);
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    mJoint->setLocalPose(PxJointActorIndex::eACTOR1, t);
    updateBodies();
}

void PhysicJoint::setLimits(float yLimit, float zLimit) {
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

float PhysicJoint::getZLimit() {
    PxJointLimitCone limits = mJoint->getSwingLimit();
	return limits.zAngle * RAD2DEG;
}

float PhysicJoint::getYLimit() {
    PxJointLimitCone limits = mJoint->getSwingLimit();
	return limits.yAngle * RAD2DEG;
}

void PhysicJoint::dsetMotorSpring(float spring) {
    mDMotorSpring = spring;
}

void PhysicJoint::dsetMotorDamping(float damping) {
    mDMotorDamping = damping;
}

void PhysicJoint::dsetMotorAccel(bool accel) {
    mDMotorAccel = accel;
}

void PhysicJoint::dsetContactDistance(float value) {
    mDContactDistance = value;
}

void PhysicJoint::dResetLimits() {
    PxJointLimitCone limits = mJoint->getSwingLimit();
    mJoint->setSwingLimit(PxJointLimitCone(
        limits.yAngle,
        limits.zAngle,
        mDContactDistance));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

void PhysicJoint::setMotorOn() {
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

void PhysicJoint::setMotorOff() {
    mMotorOn = false;
    mJoint->setDrive(PxD6Drive::eSWING,PxD6JointDrive(
        0,
        0,
        PX_MAX_F32
        ));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

bool PhysicJoint::isMotorOn() {
//    PxD6JointDrive drive = mJoint->getDrive(PxD6Drive::eSWING);
//    printf("drive spring: %.3f \n",drive.spring);
//    printf("drive damping: %.3f \n",drive.damping);
//    printf("drive forceLimit: %.3f \n",drive.forceLimit);
    return mMotorOn;
}

void PhysicJoint::setMotorStrength(float strength) {
    //TODO
}

float PhysicJoint::getMotorStrength() {
    //TODO
    return 1.0f;
}

void PhysicJoint::setMotorTarget(Quat & quat) {
    mJoint->setDrivePosition(PxTransform(quat.toPhysx()));
    mActor1->wakeUp();
    mActor2->wakeUp();
}

Quat PhysicJoint::getMotorTarget() {
    PxTransform t = mJoint->getDrivePosition();
    return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

void PhysicJoint::updateBodies() {
    mActor1->wakeUp();
    mActor2->wakeUp();
}






