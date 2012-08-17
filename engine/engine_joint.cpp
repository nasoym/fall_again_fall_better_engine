
#include "logger.h"
#include "engine_joint.h"
#include "engine.h"

#include "engine_body.h"
#include "physic_joint.h"

EngineJoint::EngineJoint(Engine* engine,EngineBody* body1, EngineBody* body2) :
	EngineGuiContainer(engine),
	mBody1(body1),
	mBody2(body2)
	{
	mJoint = new PhysicJoint(
		getEngine()->getPhysicsEngine(),
		body1->getPhysicBody(),
		body2->getPhysicBody()
	);
	body1->addJoint(this);
	body2->addJoint(this);
}

EngineBody*		EngineJoint::getBody1(){
	return mBody1;
}
EngineBody*		EngineJoint::getBody2(){
	return mBody2;
}

void        EngineJoint::setAnchor1Size(Vec3& vec3){
	setAnchor1(vec3 * mBody1->getSize() );
}

void        EngineJoint::setAnchor2Size(Vec3& vec3){
	setAnchor2(vec3 * mBody2->getSize() );
}


Vec3        EngineJoint::getAnchor1Size(){
	return mJoint->getAnchor1() / mBody1->getSize();
}

Vec3        EngineJoint::getAnchor2Size(){
	return mJoint->getAnchor2() / mBody2->getSize();
}

void	EngineJoint::guiUpdate(){
	//TODO check if any body is awake
	setPosition(getPosition());
	setOrientation(getOrientation());
}

Vec3    	EngineJoint::getPosition(){
	Vec3	jointPosition = mBody1->getPosition();
	jointPosition += mBody1->getOrientation() * getAnchor1();
	return jointPosition;
}

Quat EngineJoint::getOrientation(){
	Quat 	jointOrientation;
	jointOrientation = mBody1->getOrientation() * getAnchor1Orientation();
	return jointOrientation;
}


