
#include "logger.h"
#include "engine_joint.h"
#include "engine_body.h"

EngineJoint::EngineJoint(Engine* engine,EngineBody* body1, EngineBody* body2) :
	EngineGuiShape(engine)
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

