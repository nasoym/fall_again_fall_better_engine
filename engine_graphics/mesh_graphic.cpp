#include "logger.h"

#include <Ogre.h>
#include <OgreSkeleton.h>
using namespace Ogre;

#include "mesh_graphic.h"

#include "engine_graphic.h"

#include "bone_graphic.h"

GraphicsMesh::GraphicsMesh(GraphicsEngine* graphicsEngine,const char* meshName):
	GraphicsShape(graphicsEngine)
    {
    setEntity(getGraphicsEngine()->getSceneManager()->createEntity(meshName));
    getEntity()->setMaterialName("test2");
	getEntity()->setCastShadows(true);
    getNode()->attachObject(getEntity());

	enableBones();
}

void		GraphicsMesh::enableBones(){
	SkeletonInstance*		skeleton = getEntity()->getSkeleton();
	Skeleton::BoneIterator	boneIter = skeleton->getBoneIterator();
	Bone*					bonePtr;

	while(boneIter.hasMoreElements()) {
		bonePtr = boneIter.getNext();
		bonePtr->setManuallyControlled(true);
		Logger::debug(format("bone: %1% ") % bonePtr->getName());
	}
}

