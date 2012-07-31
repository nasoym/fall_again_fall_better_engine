
#include "logger.h"
#include "engine_joint.h"
#include "engine.h"

#include "engine_body.h"
#include "joint_physic.h"

EngineJoint::EngineJoint(Engine* engine,EngineBody* body1, EngineBody* body2) :
	EngineGuiShape(engine),
	mBody1(body1),
	mBody2(body2)
	{
	mJoint = new PhysicJoint(
		getEngine()->getPhysicsEngine(),
		body1->getPhysicBody(),
		body2->getPhysicBody()
	);
}

void	EngineJoint::physicUpdate(){
}

void	EngineJoint::guiUpdate(){
}

void        EngineJoint::setAnchor1Size(Vec3& vec3){
	setAnchor1(vec3 * mBody1->getSize() );
}

void        EngineJoint::setAnchor2Size(Vec3& vec3){
	setAnchor2(vec3 * mBody2->getSize() );
}

