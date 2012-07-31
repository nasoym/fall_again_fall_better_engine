#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

EngineMesh::EngineMesh(Engine* engine) :
	EngineGuiShape(engine)
	{
}

void	EngineMesh::physicUpdate(){
}

void	EngineMesh::guiUpdate(){
}

void        EngineMesh::setPosition(Vec3& vec3){
	EngineGuiShape::setPosition(vec3);
}

void        EngineMesh::setOrientation(Quat& quat){
	EngineGuiShape::setOrientation(quat);
}

void        EngineMesh::setSize(Vec3& vec3){
	EngineGuiShape::setSize(vec3);
}

Vec3    	EngineMesh::getPosition(){
	return EngineGuiShape::getPosition();
}

Quat EngineMesh::getOrientation(){
	return EngineGuiShape::getOrientation();
}

Vec3    EngineMesh::getSize(){
	return EngineGuiShape::getSize();
}


