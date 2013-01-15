#include "logger.h"

#include <Ogre.h>
using namespace Ogre;

#include "gui_cube.h"
#include "engine.h"

GuiCube::GuiCube(Engine* engine) :
	GuiShape(engine)
	{

    setEntity(getEngine()->getSceneManager()->createEntity("Prefab_Cube"));
    //getEntity()->setMaterialName("test2");
	getEntity()->setCastShadows(true);
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    getNode()->attachObject(getEntity());

    //cube.entity.setMaterialName(material)
    //#cube.entity.setCastShadows(True)
    //cube.entity.setCastShadows(False)

}

