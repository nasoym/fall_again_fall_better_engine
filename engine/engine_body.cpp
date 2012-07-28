#include "logger.h"
#include "engine_body.h"

EngineBody::EngineBody(Engine* engine) :
	EngineGuiShape(engine)
	{
	PhysicBox* mPhysicBox = new PhysicBox(
		getEngine()->getPhysicsEngine(),
		PxVec3(0,40,0),
		PxVec3(3,3,3)
	);
}
