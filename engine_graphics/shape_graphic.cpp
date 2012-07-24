//-------------------------------------
#include "logger.h"
#include "shape_graphic.h"
//-------------------------------------
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


