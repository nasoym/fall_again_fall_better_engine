#include "logger.h"
#include "engine_gui_shape.h"
#include "engine.h"

EngineGuiShape::EngineGuiShape(Engine* engine) :
	EngineObject(engine)
	{
    mNode = getEngine()->getDebugNode()->createChildSceneNode();
}

EngineGuiShape::~EngineGuiShape(){
    SceneNode*  parentNode = mNode->getParentSceneNode();
    mNode->removeAndDestroyAllChildren();
    parentNode->removeChild(mNode);
    mEntity = 0;
    mNode = 0;
}

void	EngineGuiShape::createBoxEntity(){
    setEntity(getEngine()->getSceneManager()->createEntity("Prefab_Cube"));
    getEntity()->setMaterialName("test2");
	getEntity()->setCastShadows(true);
    //ent->setMaterialName("Ogre/Skin");
    //ent->setMaterialName("Examples/Chrome");
    getNode()->attachObject(getEntity());

}

void	EngineGuiShape::createMesh(const char* meshName) {
    setEntity(getEngine()->getSceneManager()->createEntity(meshName));
    getEntity()->setMaterialName("test2");
	getEntity()->setCastShadows(true);
    getNode()->attachObject(getEntity());
	enableBones();
		//std::vector<GraphicsBone*> 	mMeshBones;	
		//std::vector<GraphicsBone*>	mRootBones;
}

void		EngineGuiShape::enableBones(){
	SkeletonInstance*		skeleton = getEntity()->getSkeleton();
	Skeleton::BoneIterator	boneIter = skeleton->getBoneIterator();
	Bone*					bonePtr;

	while(boneIter.hasMoreElements()) {
		bonePtr = boneIter.getNext();
		bonePtr->setManuallyControlled(true);
		Logger::debug(format("bone: %1% ") % bonePtr->getName());
	}
}

void        EngineGuiShape::setPosition(Vec3& vec3){
	getNode()->setPosition(vec3.toOgre());
}

Vec3    	EngineGuiShape::getPosition(){
	return Vec3(getNode()->getPosition());
}

void        EngineGuiShape::setOrientation(Quat& quat){
	getNode()->setOrientation(quat.toOgre());
}

Quat EngineGuiShape::getOrientation(){
	return Quat(getNode()->getOrientation());
}

void        EngineGuiShape::setSize(Vec3& vec3){
	getNode()->setScale(vec3.toOgre() * (2.0f / 100.0f));
}

Vec3    EngineGuiShape::getSize(){
	return Vec3(getNode()->getScale() * (100.0f / 2.0f));
}

