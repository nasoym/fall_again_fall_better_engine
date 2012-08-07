#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

#include "engine_body.h"
#include "engine_joint.h"
#include "engine_gui_container.h"

Vec3		EngineMesh::translateGlobalAnchorToLocal(EngineBody* body,Vec3 & globalAnchor) {
	return Vec3(
		body->getOrientation().inverse() 
		* (
			globalAnchor - body->getPosition()
		));
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

void	EngineMesh::setBodyForBone(Bone* bone,EngineBody* body){
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

bool	EngineMesh::hasBoneAParent(Bone* bone){
	if (getBoneParent(bone) && getBodyOfBone(getBoneParent(bone)) ) {
		return true;
	} else {
		return false;
	}
}

Bone*	EngineMesh::getBoneParent(Bone* bone){
	return (Bone*) bone->getParent();
}

Quat	EngineMesh::getBoneOrientation(Bone* bone,bool rotated){
	//Quat boneQuat = Quat(bone->_getDerivedOrientation()) * getOrientation();
	Quat boneQuat = Quat(getOrientation() * bone->_getDerivedOrientation());
	if (rotated) {
		return Quat(boneQuat * Quat().fromAngles(0,0,90) );
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
					* Quat().fromAngles(0,0,90).inverse() 
					).toOgre()
				//Quat(getOrientation().inverse() * quat).toOgre()
				);
		} else {
			bone->_setDerivedOrientation(
				Quat(
					getOrientation().inverse() 
					* quat
					* Quat().fromAngles(0,0,90).inverse() 
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

EngineBody*	EngineMesh::getBodyOfBone(Bone* bone) {
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if ( (*iter).bone == bone) {
			return (*iter).body;
		}
	}
	return 0;
}

Bone*	EngineMesh::getBoneOfBody(EngineBody* body) {
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
		closestDist = 10;
	}
	return closestDist / 2.0f;
}


