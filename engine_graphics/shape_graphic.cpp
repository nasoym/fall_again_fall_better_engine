#include "logger.h"
#include "shape_graphic.h"
#include "engine_graphic.h"

GraphicsShape::GraphicsShape(GraphicsEngine* graphicsEngine):
    mGraphicsEngine(graphicsEngine) 
    {
    mNode = mGraphicsEngine->getDebugNode()->createChildSceneNode();
}

GraphicsShape::~GraphicsShape(){
    SceneNode*  parentNode = mNode->getParentSceneNode();
    mNode->removeAndDestroyAllChildren();
    parentNode->removeChild(mNode);
    mEntity = 0;
    mNode = 0;
}

void        GraphicsShape::setPosition(Vec3& vec3){
	getNode()->setPosition(vec3.toOgre());
}

Vec3    	GraphicsShape::getPosition(){
	return Vec3(getNode()->getPosition());
}

void        GraphicsShape::setOrientation(Quat& quat){
	getNode()->setOrientation(quat.toOgre());
}

Quat GraphicsShape::getOrientation(){
	return Quat(getNode()->getOrientation());
}

void        GraphicsShape::setSize(Vec3& vec3){
	getNode()->setScale(vec3.toOgre() * (2.0f / 100.0f));
}

Vec3    GraphicsShape::getSize(){
	return Vec3(getNode()->getScale() * (100.0f / 2.0f));
}



