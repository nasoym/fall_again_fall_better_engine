#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

//#include "engine_body.h"
#include "engine_joint.h"
#include "engine_gui_shape.h"
#include "engine_gui_container.h"

#include "actor.h"

EngineMesh::EngineMesh(Engine* engine,const char* meshName) :
	EngineGuiShape(engine),
	mRootBone(0),
	mLocalPos(Vec3()),
	mLocalQuat(Quat()),
	mRootShape(0),
	mMeshFileName(std::string(meshName)),
	mRotationX(0),
	mRotationY(0),
	mRotationZ(90)
	{
    setEntity(getEngine()->getSceneManager()->createEntity(meshName));
    getNode()->attachObject(getEntity());
	setupAllBones();
	mRootBone = findRootBone();
	setFinalShape();

	//mRootShape = new EngineGuiContainer(getEngine());
	//mRootShape->addDebugAxises(15,1);
	//mRootShape->setPosition(getPosition());
	//mRootShape->setOrientation(getOrientation());
}

int				EngineMesh::getNumberOfBones(){
	return mBoneBodies.size();
}

Actor*		EngineMesh::getBodyByIndex(int index){
	return mBoneBodies[index].body;
}

EngineJoint*	EngineMesh::getJointByIndex(int index){
	return mBoneBodies[index].joint;
}

std::string		EngineMesh::getBoneNameByIndex(int index){
	return mBoneBodies[index].bone->getName();
}

void		EngineMesh::setupAllBones(){
	SkeletonInstance*		skeleton = getEntity()->getSkeleton();
	Skeleton::BoneIterator	boneIter = skeleton->getBoneIterator();
	Bone*					bonePtr;
	while(boneIter.hasMoreElements()) {
		bonePtr = boneIter.getNext();
		bonePtr->setManuallyControlled(true);
		mBoneBodies.push_back(BoneBody(bonePtr));
		//Logger::debug(format("found bone: %1% ") % bonePtr->getName());
	}
}

void	EngineMesh::guiUpdate(){
	Actor* rootBody = getBodyOfBone(mRootBone);
	if (rootBody) {
	//if (false) {
		Vec3	rootBodyPos = rootBody->getPosition();
		Quat	rootBodyQuat = rootBody->getOrientation();
		setPosition(rootBodyPos - (rootBodyQuat*mLocalPos));
		setOrientation(rootBodyQuat * mLocalQuat);
	}
	if (mRootShape) {
	//if (false) {
		mRootShape->setPosition(getPosition());
		mRootShape->setOrientation(getOrientation());
	}
	updateBone(mRootBone);
}

void	EngineMesh::updateBone(Bone* bone){
	Actor* body = getBodyOfBone(bone);
	if (body) {
		boneSetOrientation(bone, body->getOrientation());
		Vec3	localPos = Vec3();
		EngineJoint* joint = getJointOfBone(bone);
		if (joint) {
			localPos = body->getOrientation() * joint->getAnchor2();
		} else {
			localPos = body->getOrientation() * (body->getSize()*Vec3(-1,0,0));
		}
		boneSetPosition(bone, body->getPosition() + localPos);
	}
	EngineGuiContainer* container = getContainerOfBone(bone);
	if (container) {
		container->setPosition(getBonePosition(bone));
		container->setOrientation(getBoneOrientation(bone,false)); //Y
	}
	if (bone) {
		Ogre::Bone::ChildNodeIterator childIter = bone->getChildIterator();
		while(childIter.hasMoreElements()){
			updateBone((Ogre::Bone*)childIter.getNext());
		}
	}
}

void 	EngineMesh::calcLocalPosOfRootBone() {
	Actor* rootBody = getBodyOfBone(mRootBone);
	if (rootBody) {
		//Logger::debug("calc local pos of root bone");
		Vec3	rootBodyPos = rootBody->getPosition();
		Quat	rootBodyQuat = rootBody->getOrientation();
		mLocalPos = rootBodyPos - getPosition();
		mLocalPos = rootBodyQuat.inverse() * mLocalPos;
		mLocalQuat = getOrientation() * rootBodyQuat.inverse();

		//Logger::debug(format("mesh pos: %1% ") % getPosition());
		//Logger::debug(format("mesh ori: %1% ") % getOrientation());
		//Logger::debug(format("local pos: %1% ") % mLocalPos);
		//Logger::debug(format("local ori: %1% ") % mLocalQuat);
	}
}

void	EngineMesh::createAllDebugObjects(){
	EngineGuiContainer* container;
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		createDebugForBone( (*iter).bone );
	}
}

void	EngineMesh::createDebugForBone(Bone* bone) {
	EngineGuiContainer* container;
	container = new EngineGuiContainer(getEngine());
	setContainerForBone(bone,container);
	container->addDebugAxises(5,0.3);
}

Vec3			EngineMesh::getBoneNameLocalPosition(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return Vec3(bone->getPosition());
	}
	return Vec3();
}

Quat			EngineMesh::getBoneNameLocalOrientation(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return Quat(bone->getOrientation());
	}
	return Quat();
}

Vec3			EngineMesh::getMeshScale(){
	return Vec3(getNode()->getScale());
}

void	EngineMesh::setContainerForBone(Bone* bone,EngineGuiContainer* container){
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ((*iter).bone == bone) {
			(*iter).container = container;
			break;
		}
	}
}

void	EngineMesh::setBodyForBone(Bone* bone,Actor* body){
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ((*iter).bone == bone) {
			(*iter).body = body;
			break;
		}
	}
}

void	EngineMesh::setJointForBone(Bone* bone,EngineJoint* joint){
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ((*iter).bone == bone) {
			(*iter).joint = joint;
			break;
		}
	}
}

Bone*	EngineMesh::findRootBone() {
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if (!getBoneParent((*iter).bone)) {
			return (*iter).bone;
		}
	}
	return 0;
}

Bone*	EngineMesh::getBoneParent(Bone* bone){
	return (Bone*) bone->getParent();
}

Quat	EngineMesh::getBoneOrientation(Bone* bone,bool rotated){
	Quat boneQuat = Quat(getOrientation() * bone->_getDerivedOrientation());
	if (rotated) {
		return Quat(boneQuat * Quat().fromAngles(mRotationX,mRotationY,mRotationZ) );
	} else {
		return Quat(boneQuat);
	}
}

void	EngineMesh::boneSetOrientation(Bone* bone,Quat quat,bool rotated){
	if (rotated) {
		if (bone == mRootBone) {
			bone->setOrientation(
				Quat(
					getOrientation().inverse() 
					* quat
					* Quat().fromAngles(mRotationX,mRotationY,mRotationZ).inverse() 
					).toOgre()
				//Quat(getOrientation().inverse() * quat).toOgre()
				);
		} else {
			bone->_setDerivedOrientation(
				Quat(
					getOrientation().inverse() 
					* quat
					* Quat().fromAngles(mRotationX,mRotationY,mRotationZ).inverse() 
					).toOgre()
				//Quat(getOrientation().inverse() * quat).toOgre()
				);
		}
	} else {
		if (bone == mRootBone) {
			bone->setOrientation(
				Quat(
					getOrientation().inverse() 
					* quat
					).toOgre()
				);
		} else {
			bone->_setDerivedOrientation(
				Quat(
					getOrientation().inverse() 
					* quat
					).toOgre()
				);
		}
	}
}

Vec3	EngineMesh::getBonePosition(Bone* bone) {
	Vec3 bonePos = Quat(getNode()->getOrientation()) * Vec3(bone->_getDerivedPosition());
	Vec3 scaledPos = Vec3(getNode()->getScale()) * bonePos;
	return Vec3(scaledPos + Vec3(getNode()->getPosition()));
}

void	EngineMesh::boneSetPosition(Bone* bone,Vec3 vec3){
	Vec3 localPos = vec3 - getPosition();
	localPos = localPos / getNode()->getScale();
	Vec3 bonePos = getOrientation().inverse() * localPos;
	if (bone == mRootBone) {
		bone->setPosition(bonePos.toOgre());
	} else {
		bone->_setDerivedPosition(bonePos.toOgre());
	}
}

EngineGuiContainer*	EngineMesh::getContainerOfBone(Bone* bone) {
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ( (*iter).bone == bone) {
			return (*iter).container;
		}
	}
	return 0;
}

EngineJoint*	EngineMesh::getJointOfBone(Bone* bone) {
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ( (*iter).bone == bone) {
			return (*iter).joint;
		}
	}
	return 0;
}

Actor*	EngineMesh::getBodyOfBone(Bone* bone) {
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ( (*iter).bone == bone) {
			return (*iter).body;
		}
	}
	return 0;
}

Bone*	EngineMesh::getBoneOfBody(Actor* body) {
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ( (*iter).body == body) {
			return (*iter).bone;
		}
	}
	return 0;
}

float	EngineMesh::getBoneSize(Bone* bone) {
	Vec3	bonePos = getBonePosition(bone);
	Vec3	childBonePos;
	float	closestDist = 0;
	float	localDist;
	Bone*	childBone;
	Ogre::Bone::ChildNodeIterator childIter = bone->getChildIterator();
	while(childIter.hasMoreElements()){
		childBone = (Ogre::Bone*)childIter.getNext();
		childBonePos = getBonePosition(childBone);
		localDist = bonePos.distance(childBonePos);
		if (closestDist == 0 ){
			closestDist = localDist;
		} else if (localDist<closestDist) {
			closestDist = localDist;
		}
	}
	if (closestDist == 0 ){
		//bone has no child bones
		//closestDist = 10;
	}
	return closestDist / 2.0f;
}

Bone*			EngineMesh::getBoneFromName(std::string boneName){
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
	    if( (*iter).bone->getName().compare(boneName) == 0 ) {
			return (*iter).bone;
		}
	}
	//Logger::debug(format("bone for %1% was not found") % boneName );
	return 0;
}

void			EngineMesh::setBodyForBoneName(std::string boneName,Actor* body){
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
	    if( (*iter).bone->getName().compare(boneName) == 0 ) {
			(*iter).body = body;
			break;
		}
	}
}

void			EngineMesh::setJointForBoneName(std::string boneName,EngineJoint* joint){
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
	    if( (*iter).bone->getName().compare(boneName) == 0 ) {
			(*iter).joint = joint;
			break;
		}
	}
}

Actor*		EngineMesh::getBodyOfBoneName(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return getBodyOfBone(bone);
	}
	return 0;
}

EngineJoint*	EngineMesh::getJointOfBoneName(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return getJointOfBone(bone);
	}
	return 0;
}

Vec3			EngineMesh::getBoneNamePosition(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return getBonePosition(bone);
	}
	return Vec3();
}

Quat			EngineMesh::getBoneNameOrientation(std::string boneName,bool rotated){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return getBoneOrientation(bone,rotated);
	}
	return Quat();
}

float			EngineMesh::getBoneNameSize(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return getBoneSize(bone);
	}
	return 0;
}

std::string 	EngineMesh::getBoneNameParentName(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		Bone* parentBone = getBoneParent(bone);
		if( parentBone) {
			return parentBone->getName();
		} else {
			//Logger::debug(format("parent for %1% was not found") % bone );
		}
	}
	return std::string("");
}

int				EngineMesh::getBoneNameChildren(std::string boneName){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return bone->numChildren();
	}
	return 0;
}

std::string				EngineMesh::getBoneNameChildName(std::string boneName,int index){
	Bone* bone = getBoneFromName(boneName);	
	if (bone) {
		return ((Ogre::Bone*)bone->getChild(index))->getName();
	}
	return std::string("");
}


