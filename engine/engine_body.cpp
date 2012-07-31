#include "logger.h"

#include "engine_body.h"
#include "engine.h"

#include "body_physic.h"
#include "box_physic.h"

EngineBody::EngineBody(Engine* engine) :
	EngineGuiShape(engine),
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
	EngineGuiShape::setPosition(vec3);
}

void        EngineBody::setOrientation(Quat& quat){
	getPhysicBody()->setOrientation(quat);
	EngineGuiShape::setOrientation(quat);
}

void        EngineBody::setSize(Vec3& vec3){
	getPhysicBody()->setSize(vec3);
	EngineGuiShape::setSize(vec3);
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

