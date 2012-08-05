#include "logger.h"

#include "engine_body.h"
#include "engine.h"

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

