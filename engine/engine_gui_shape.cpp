#include "logger.h"
#include "engine_gui_shape.h"

EngineGuiShape::EngineGuiShape(Engine* engine) :
	EngineObject(engine),
	mShape(0)
	{
}

void        EngineGuiShape::tupleSetPosition(boost::python::object& tupleObject){
	mShape->setPosition(Vec3(tupleObject));
}
boost::python::tuple EngineGuiShape::tupleGetPosition(){
	return mShape->getPosition().toTuple();
}

void        EngineGuiShape::tupleSetOrientation(boost::python::object& tupleObject){
	mShape->setOrientation(Quat(tupleObject));
}
boost::python::tuple EngineGuiShape::tupleGetOrientation(){
	return mShape->getOrientation().toTuple();
}

void        EngineGuiShape::tupleSetSize(boost::python::object& tupleObject){
	mShape->setSize(Vec3(tupleObject));
}
boost::python::tuple EngineGuiShape::tupleGetSize(){
	return mShape->getSize().toTuple();
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

