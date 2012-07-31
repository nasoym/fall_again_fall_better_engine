#include "logger.h"
#include "bone_graphic.h"
#include "mesh_graphic.h"
#include "engine_graphic.h"

GraphicsBone::GraphicsBone(
		GraphicsEngine* graphicsEngine,
		GraphicsMesh*	mesh,
		Bone*			bone
		):
    mGraphicsEngine(graphicsEngine),
	mMesh(mesh),
	mBone(bone)
    {
}

GraphicsBone::~GraphicsBone(){
}

void        GraphicsBone::setPosition(Vec3& vec3){
}

Vec3    	GraphicsBone::getPosition(){
	return Vec3();
}

void        GraphicsBone::setOrientation(Quat& quat){
}

Quat GraphicsBone::getOrientation(){
	return Quat();
}

void        GraphicsBone::setSize(Vec3& vec3){
}

Vec3    GraphicsBone::getSize(){
	return Vec3();
}

