#include "logger.h"
#include "engine_body.h"

EngineBody::EngineBody(Engine* engine) :
	EngineGuiShape(engine)
	{
	mPhysicBox = new PhysicBox(
		getEngine()->getPhysicsEngine(),
		Vec3(0,0,0),
		Vec3(1,1,1)
	);
}

void	EngineBody::physicUpdate(){
}


void	EngineBody::guiUpdate(){
	setPosition(mPhysicBox->getPosition());
	setOrientation(mPhysicBox->getOrientation());
}

void        EngineBody::setPosition(Vec3& vec3){
	mPhysicBox->setPosition(vec3);
	EngineGuiShape::setPosition(vec3);
}

void        EngineBody::setOrientation(Quat& quat){
	mPhysicBox->setOrientation(quat);
	EngineGuiShape::setOrientation(quat);
}

void        EngineBody::setSize(Vec3& vec3){
	mPhysicBox->setSize(vec3);
	EngineGuiShape::setSize(vec3);
}


