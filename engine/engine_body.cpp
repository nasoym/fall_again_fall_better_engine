#include "logger.h"

#include "engine_body.h"
#include "engine.h"
#include "engine_joint.h"
#include "physic_body.h"
#include "physic_box.h"

EngineBody::EngineBody(Engine* engine) :
	EngineGuiContainer(engine),
	mDoGuiUpdates(true)
	{
}

void	EngineBody::physicUpdate(){
}

void	EngineBody::guiUpdate(){
	if (mDoGuiUpdates) {
		setPosition(getPhysicBody()->getPosition());
		setOrientation(getPhysicBody()->getOrientation());
	}
}

void        EngineBody::setPosition(Vec3& vec3){
	getPhysicBody()->setPosition(vec3);
	EngineGuiContainer::setPosition(vec3);
}

void        EngineBody::setOrientation(Quat& quat){
	getPhysicBody()->setOrientation(quat);
	EngineGuiContainer::setOrientation(quat);
}

void        EngineBody::setSize(Vec3& vec3){
	EngineGuiContainer::setSize(vec3);
	getPhysicBody()->setSize(vec3);
}

Vec3    	EngineBody::getPosition(){
	return getPhysicBody()->getPosition();
}

Quat EngineBody::getOrientation(){
	return getPhysicBody()->getOrientation();
}

Vec3    EngineBody::getSize(){
	return getPhysicBody()->getSize();
}

void    EngineBody::deleteAllJoints() {
	std::vector<EngineJoint*>::iterator  mJointsIterator;
	for (mJointsIterator = mJoints.begin(); 
		mJointsIterator != mJoints.end(); ++mJointsIterator) {
		delete (*mJointsIterator);
	}
	mJoints.clear();
}

void    EngineBody::deleteJoint(EngineJoint* joint) {
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

int     EngineBody::howManyJoints() {
	return mJoints.size();
}

void    EngineBody::addJoint(EngineJoint* joint){
	mJoints.push_back(joint);
}

EngineJoint*  EngineBody::getJoint(int index) {
	return mJoints[index];
}

void		EngineBody::addForce(Vec3 force){
	getPhysicBody()->addForce(force);
}

void	EngineBody::dsetSolverIterations(int i1,int i2){
	getPhysicBody()->dsetSolverIterations(i1,i2);
}

void	EngineBody::setMass(float mass){
	getPhysicBody()->setMass(mass);
}

float	EngineBody::getMass(){
	return getPhysicBody()->getMass();
}


