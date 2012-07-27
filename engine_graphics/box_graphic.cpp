#include "logger.h"
#include "box_graphic.h"

GraphicsBox::GraphicsBox(GraphicsEngine* graphicsEngine):
	GraphicsShape(graphicsEngine)
    {
    Logger::debug(format("creating graphics box: %p") % this);

    setEntity(getGraphicsEngine()->getSceneManager()->createEntity("Prefab_Cube"));
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    getNode()->attachObject(getEntity());

    //cube.entity.setMaterialName(material)
    //#cube.entity.setCastShadows(True)
    //cube.entity.setCastShadows(False)

}


