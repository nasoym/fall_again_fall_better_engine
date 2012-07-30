#include "logger.h"
#include "box_graphic.h"

GraphicsBox::GraphicsBox(GraphicsEngine* graphicsEngine):
	GraphicsShape(graphicsEngine)
    {
    setEntity(getGraphicsEngine()->getSceneManager()->createEntity("Prefab_Cube"));
    getEntity()->setMaterialName("test2");
	getEntity()->setCastShadows(true);
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    getNode()->attachObject(getEntity());

    //cube.entity.setMaterialName(material)
    //#cube.entity.setCastShadows(True)
    //cube.entity.setCastShadows(False)

}


