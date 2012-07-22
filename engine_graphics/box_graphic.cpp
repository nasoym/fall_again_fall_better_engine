//-------------------------------------
#include "logger.h"
#include "box_graphic.h"
//-------------------------------------
GraphicsBox::GraphicsBox(GraphicsEngine* graphicsEngine):
    mGraphicsEngine(graphicsEngine) 
    {
    Logger::debug(format("creating graphics box: %p ") % this);

    mEntity = mGraphicsEngine->getSceneManager()->createEntity("");
    mNode = mGraphicsEngine->getDebugNode()->createChildSceneNode();
    mNode->attachObject(mEntity);

    //cube.entity.setMaterialName(material)
    //#cube.entity.setCastShadows(True)
    //cube.entity.setCastShadows(False)

}

GraphicsBox::~GraphicsBox(){
    Logger::debug(format("deleting graphics box: %p ") % this);

    SceneNode*  parentNode = mNode->getParentSceneNode();
    mNode->removeAndDestroyAllChildren();
    parentNode->removeChild(mNode);
    mEntity = 0;
    mNode = 0;
}

