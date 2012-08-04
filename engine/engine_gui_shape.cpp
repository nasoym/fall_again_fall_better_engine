#include "logger.h"
#include "engine_gui_shape.h"
#include "engine.h"

EngineGuiShape::EngineGuiShape(Engine* engine) :
	EngineObject(engine),
	mMaterial(0),
	mLocalPosition(Vec3()),
	mLocalOrientation(Quat()),
	mLocalSize(Vec3(1,1,1)),
	mContainer(0)
	{
    mNode = getEngine()->getDebugNode()->createChildSceneNode();
}

EngineGuiShape::~EngineGuiShape(){
    SceneNode*  parentNode = mNode->getParentSceneNode();
    mNode->removeAndDestroyAllChildren();
    parentNode->removeChild(mNode);
    mEntity = 0;
    mNode = 0;
	if(!mMaterial.isNull()){
		//TODO?
		//mMaterial.release();
	}
}

void	EngineGuiShape::createBoxEntity(){
    setEntity(getEngine()->getSceneManager()->createEntity("Prefab_Cube"));
    //setEntity(getEngine()->getSceneManager()->createEntity("Cube.mesh"));
    //setEntity(getEngine()->getSceneManager()->createEntity("Character.mesh"));
	getEntity()->setCastShadows(true);
    getNode()->attachObject(getEntity());
}

void	EngineGuiShape::setContainer(EngineGuiContainer* container){
	mContainer = container;
}

EngineGuiContainer* EngineGuiShape::getContainer(){
	return mContainer;
}

void    EngineGuiShape::setPosition(Vec3& vec3){
	getNode()->setPosition((vec3 + mLocalPosition).toOgre());
}

Vec3    	EngineGuiShape::getPosition(){
	return Vec3(getNode()->getPosition());
}

void        EngineGuiShape::setOrientation(Quat& quat){
	getNode()->setOrientation((quat * mLocalOrientation).toOgre());
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

void	EngineGuiShape::setMaterialName(const char* name){
    getEntity()->setMaterialName(name);
}

void	EngineGuiShape::setColour(float red,float green,float blue,float alpha) {
	if(mMaterial.isNull()){
		setupCustomMaterial();
	}
	mMaterial->getTechnique(0)->getPass(0)->setDiffuse(
		ColourValue(
		red,green,blue,alpha
		)); 
}

void	EngineGuiShape::setupCustomMaterial(){
	mMaterial = Ogre::MaterialManager::getSingleton().create(
		readUuid(),
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mMaterial->getTechnique(0)->getPass(0)->setDiffuse(ColourValue(0.5f,0.5f,0.5f,0.5f)); 
	//mMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(true); 
	mMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false); 
	mMaterial->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	mMaterial->getTechnique(0)->getPass(0)->setCullingMode(CULL_NONE);
	Pass* wireFramePass = mMaterial->getTechnique(0)->createPass();
	wireFramePass->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	wireFramePass->setDepthWriteEnabled(true);
	wireFramePass->setPolygonMode(PM_WIREFRAME);
	wireFramePass->setDiffuse(ColourValue(0,0,0,0.5f));
    getEntity()->setMaterial(mMaterial);
    //getEntity()->setMaterialName(readUuid());
}

