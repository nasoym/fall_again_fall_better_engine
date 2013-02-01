#include "logger.h"
#include "gui_shape.h"
#include "gui_container.h"
#include "engine.h"

GuiShape::GuiShape(Engine* engine) :
	EngineObject(engine),
	mMaterial(0),
	mEntity(0),
	mNode(0),
	mLocalPosition(Vec3()),
	mLocalOrientation(Quat()),
	mLocalSize(Vec3(1,1,1)),
	mContainer(0),
	mFinalShape(false)
	{
    mNode = getEngine()->getDebugNode()->createChildSceneNode();
}

GuiShape::~GuiShape(){
	Logger::debug("guiShape delete");

	if(mEntity && getNode()){
		getNode()->detachObject(mEntity);
		getEngine()->getSceneManager()->destroyEntity(mEntity);
		mEntity = 0;
	}

    SceneNode*  parentNode = mNode->getParentSceneNode();
    mNode->removeAndDestroyAllChildren();
    parentNode->removeChild(mNode);
    mNode = 0;

	if(!mMaterial.isNull()){
		//TODO?  mMaterial.release();
	}
}

void	GuiShape::selectShow(){
	if (getNode()){
		getNode()->showBoundingBox(true);
	}
}

void	GuiShape::selectHide(){
	if (getNode()){
		getNode()->showBoundingBox(false);
	}
}

void	GuiShape::setContainer(GuiContainer* container){
	mContainer = container;
}

GuiContainer* GuiShape::getContainer(){
	return mContainer;
}

void    GuiShape::setPosition(Vec3& vec3){
	Vec3	globalPos;
	if (getContainer()) {
		globalPos = getContainer()->getOrientation() * getLocalPosition();
	} else {
		globalPos = getLocalPosition();
	}
	globalPos = globalPos + vec3;
	getNode()->setPosition(globalPos.toOgre());
}

Vec3    	GuiShape::getPosition(){
	return Vec3(getNode()->getPosition());
}

void        GuiShape::setOrientation(Quat& quat){
	getNode()->setOrientation((quat * getLocalOrientation()).toOgre());
}

Quat GuiShape::getOrientation(){
	return Quat(getNode()->getOrientation());
}

void        GuiShape::setLocalSize(Vec3& vec3){
	mLocalSize = vec3;
	getNode()->setScale(vec3.toOgre() * (2.0f / 100.0f));
}

void        GuiShape::setSize(Vec3& vec3){
	if (getContainer()) {
		Vec3 scaling = vec3 / getContainer()->getSize();
		//Logger::debug(format("scaling: %1% %2% %3%") % 
	//			scaling.X() % vec3.Y() % vec3.Z() );
		if (mScalingType != FIX) {
			setLocalPosition(getLocalPosition() * scaling);
		}
		if (mScalingType == ONE_TO_ONE) {
			//Logger::debug("one to one");
			getNode()->setScale(vec3.toOgre() * (2.0f / 100.0f));
		} else if (mScalingType == SCALING) {
			//Logger::debug("scaling");
			getNode()->setScale((getSize() * scaling).toOgre() * (2.0f / 100.0f));
		}
	} else {
		getNode()->setScale(vec3.toOgre() * (2.0f / 100.0f));
	}
}

Vec3    GuiShape::getSize(){
	return Vec3(getNode()->getScale() * (100.0f / 2.0f));
}

void	GuiShape::setMaterialName(const char* name){
    getEntity()->setMaterialName(name);
	mMaterialName = std::string(name);
	//mMaterial = 0; //TODO do correct cleanup
}

bool	GuiShape::hasColour(){
	if(mMaterial.isNull()){
		return false;
	} else {
		return true;
	}
}

float 	GuiShape::getAlpha(){
	if(!mMaterial.isNull()){
		ColourValue color = mMaterial->getTechnique(0)->getPass(0)->getDiffuse();
		return color.a;
	}
	return 1.0f;
}

Vec3 	GuiShape::getColour(){
	if(!mMaterial.isNull()){
		ColourValue color = mMaterial->getTechnique(0)->getPass(0)->getDiffuse();
		return Vec3(color.r,color.g,color.b);
	}
	return Vec3();
}

void	GuiShape::setColour(float red,float green,float blue,float alpha) {
	if(mMaterial.isNull()){
		setupCustomMaterial();
	}
	mMaterial->getTechnique(0)->getPass(0)->setDiffuse(
		ColourValue(
		red,green,blue,alpha
		)); 
}

void 	GuiShape::setCustomMaterial(){
	if(mMaterial.isNull()){
		setupCustomMaterial();
	} else {
		getEntity()->setMaterial(mMaterial);
	}
}

void	GuiShape::setupCustomMaterial(){
	mMaterial = Ogre::MaterialManager::getSingleton().create(
		readUuid(),
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mMaterial->getTechnique(0)->getPass(0)->setDiffuse(ColourValue(0.5f,0.5f,0.5f,0.25f)); 
	//mMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(true); 
	mMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false); 
	mMaterial->getTechnique(0)->getPass(0)->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	mMaterial->getTechnique(0)->getPass(0)->setCullingMode(CULL_NONE);
	Pass* wireFramePass = mMaterial->getTechnique(0)->createPass();
	wireFramePass->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	wireFramePass->setDepthWriteEnabled(true);
	wireFramePass->setPolygonMode(PM_WIREFRAME);
	wireFramePass->setDiffuse(ColourValue(0,0,0,0.2f));
    getEntity()->setMaterial(mMaterial);
    //getEntity()->setMaterialName(readUuid());
}

