#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

#include "engine_body.h"
#include "engine_joint.h"

Bone*	EngineMesh::getBoneParent(Bone* bone){
	return (Bone*) bone->getParent();
}

Quat	EngineMesh::getBoneOrientation(Bone* bone){
	//Quat boneQuat = Quat(bone->_getDerivedOrientation());
	//return Quat(boneQuat * getOrientation());
	Quat boneQuat = Quat(bone->_getDerivedOrientation()) * getOrientation();
	return Quat(boneQuat * Quat().fromAngle(0,0,90) );
}

void	EngineMesh::boneSetOrientation(Bone* bone,Quat quat){
	if (bone == mRootBone) {
		bone->setOrientation(
			Quat(
				getOrientation().inverse() 
				* quat
				* Quat().fromAngle(0,0,90).inverse() 
				).toOgre()
			//Quat(getOrientation().inverse() * quat).toOgre()
			);
	} else {
		bone->_setDerivedOrientation(
			Quat(
				getOrientation().inverse() 
				* quat
				* Quat().fromAngle(0,0,90).inverse() 
				).toOgre()
			//Quat(getOrientation().inverse() * quat).toOgre()
			);
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

