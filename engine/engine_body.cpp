#include "logger.h"
#include "engine_body.h"

EngineBody::EngineBody(Engine* engine) :
	EngineGuiShape(engine)
	{
	mPhysicBox = new PhysicBox(
		getEngine()->getPhysicsEngine(),
		PxVec3(0,140,0),
		PxVec3(3,3,3)
	);
    Logger::debug(format("mPhysicBox:%1%") % mPhysicBox);
}

void	EngineBody::physicUpdate(){
	//Logger::debug("body:");
    //Logger::debug(format("> %1%") % mPhysicBox->mBody);
	//printf("-");
	//Logger::debug("p");
	//Vec3 pos = mPhysicBox->getPosition();
    //Logger::debug(format("%1%") % pos);
	//Logger::debug("got physic pos");
	//setPosition(mPhysicBox->getPosition());
	//setOrientation(mPhysicBox->getOrientation());
}

void	EngineBody::guiUpdate(){
    //Logger::debug(format("mPhysicBox:%1%") % mPhysicBox);
    //Logger::debug(format("mPhysicBox->mBody:%1%") % mPhysicBox->mBody);
	setPosition(mPhysicBox->getPosition());
	setOrientation(mPhysicBox->getOrientation());
}
