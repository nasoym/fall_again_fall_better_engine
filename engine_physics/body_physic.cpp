#include "basejoint.h"
#include "body_physic.h"

PhysicBody::PhysicBody( ) {

}
PhysicBody::~PhysicBody( ) {
    deleteAllJoints();
}

Vec3	PhysicBody::getPosition() {
    PxTransform t = getBody()->getGlobalPose();
	return Vec3(t.p.x,t.p.y,t.p.z);
}

Quat	PhysicBody::getOrientation() {
    PxTransform t = getBody()->getGlobalPose();
	return Quat(t.q.w,t.q.x,t.q.y,t.q.z);
}

Vec3	PhysicBody::getSize() {
	return Vec3();
}

void    PhysicBody::setPosition(Vec3 vec3) {
    PxTransform t = getBody()->getGlobalPose();
    t.p.x = vec3.X();
    t.p.y = vec3.Y();
    t.p.z = vec3.Z();
    getBody()->setGlobalPose(t);
    wakeUp();
}

void    PhysicBody::setOrientation(Quat quat) {
    PxTransform t = getBody()->getGlobalPose();
    t.q.x = quat.X();
    t.q.y = quat.Y();
    t.q.z = quat.Z();
    t.q.w = quat.W();
    getBody()->setGlobalPose(t);
    wakeUp();
}

void    PhysicBody::setSize(Vec3 vec3) {
}


void    PhysicBody::deleteAllJoints() {
	std::vector<BaseJoint*>::iterator  mJointsIterator;
	for (mJointsIterator = mJoints.begin(); 
		mJointsIterator != mJoints.end(); ++mJointsIterator) {
		delete (*mJointsIterator);
	}
	mJoints.clear();
}

void    PhysicBody::deleteJoint(BaseJoint* joint) {
	std::vector<BaseJoint*>::iterator  mJointsIterator;
	for (mJointsIterator = mJoints.begin(); 
		mJointsIterator != mJoints.end(); ++mJointsIterator) {
		if ( (*mJointsIterator) == joint ){
			delete (*mJointsIterator);
			mJoints.erase( mJointsIterator);
			break;
		}
	}
}

int     PhysicBody::howManyJoints() {
	return mJoints.size();
}

void    PhysicBody::addJoint(BaseJoint* joint){
	mJoints.push_back(joint);
}

BaseJoint*  PhysicBody::getJoint(int index) {
	return mJoints[index];
}

