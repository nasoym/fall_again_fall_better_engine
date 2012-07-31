#include "logger.h"
#include "engine_gui_shape.h"
#include "engine.h"
#include "shape_graphic.h"

EngineGuiShape::EngineGuiShape(Engine* engine) :
	EngineObject(engine),
	mShape(0)
	{
}

void        EngineGuiShape::setPosition(Vec3& vec3){
	mShape->setPosition(vec3);
}

Vec3    	EngineGuiShape::getPosition(){
	return mShape->getPosition();
}

void        EngineGuiShape::setOrientation(Quat& quat){
	mShape->setOrientation(quat);
}

Quat EngineGuiShape::getOrientation(){
	return mShape->getOrientation();
}

void        EngineGuiShape::setSize(Vec3& vec3){
	mShape->setSize(vec3);
}

Vec3    EngineGuiShape::getSize(){
	return mShape->getSize();
}

