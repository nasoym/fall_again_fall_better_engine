#include "logger.h"
#include <Ogre.h>
using namespace Ogre;
#include "box_graphic.h"
#include "engine_graphic.h"

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


