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

void	EngineBody::physicUpdate(){
	Logger::debug("p");
	Vec3 pos = mPhysicBox->getPosition();
	Logger::debug("got physic pos");
	//setPosition(mPhysicBox->getPosition());
	//setOrientation(mPhysicBox->getOrientation());
}

