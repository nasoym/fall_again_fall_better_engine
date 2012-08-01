#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

#include "engine_body.h"
#include "engine_joint.h"

EngineMesh::EngineMesh(Engine* engine,const char* meshName) :
	EngineGuiShape(engine)
	{

	//getNode()->setScale(Vec3(1000,1000,1000).toOgre() * (2.0f / 100.0f));

    setEntity(getEngine()->getSceneManager()->createEntity(meshName));
    getEntity()->setMaterialName("transp_border");
	getEntity()->setCastShadows(true);
    getNode()->attachObject(getEntity());

	setSize(Vec3(1000,1000,1000));
	setPosition(Vec3(0,50,0));

	enableBones();
	createRootBone();

	createPhysicBodies();
	createPhsyisJoints();
	checkForJointCollision();
}

EngineMesh::~EngineMesh(){
}

EngineBody*				EngineMesh::getRootBone(){
	return mRootBody;
}

void	EngineMesh::guiUpdate(){
	if(getRootBone()){
		setPosition(getRootBone()->getPosition());
		setOrientation(getRootBone()->getOrientation());
	}
	
	updateBone(mRootBone);
}

void	EngineMesh::boneSetOrientation(Bone* bone,Quat quat){
	if (bone == mRootBone) {
		bone->setOrientation(
			Quat( getOrientation().inverse() * quat).toOgre()
			);
	} else {
		bone->_setDerivedOrientation(
			Quat( getOrientation().inverse() * quat)
		);
	}

}

void	EngineMesh::updateBone(Bone* bone){

	EngineBody* 	body = getBodyOfBone(bone);
	if (body) {
		boneSetOrientation(bone,body->getOrientation());
	}

	Bone*	childBone;
	Ogre::Bone::ChildNodeIterator childIter = bone->getChildIterator();
	while(childIter.hasMoreElements()){
		childBone = (Ogre::Bone*)childIter.getNext();
		updateBone(childBone);
	}

}
/*
    def _getPositionOrientationFromPhysicBody(self):
        if self.getPhysicBody():
            self.setOrientation(self.getPhysicBody().getOrientation())
            localPos = v.tvrotate(
                self.getPhysicBody().getLocalBonePosition(),
                self.getPhysicBody().getOrientation()
                )
            finalPos = v.tadd( 
                localPos, 
                self.getPhysicBody().getPosition()
                )
            self.setPosition(finalPos)
        return self


*/
void	EngineMesh::physicUpdate(){

}

void		EngineMesh::enableBones(){
	SkeletonInstance*		skeleton = getEntity()->getSkeleton();
	Skeleton::BoneIterator	boneIter = skeleton->getBoneIterator();
	Bone*					bonePtr;

	while(boneIter.hasMoreElements()) {
		bonePtr = boneIter.getNext();
		bonePtr->setManuallyControlled(true);
		mBoneBodies.push_back(BoneBody(bonePtr));
		Logger::debug(format("bone: %1% ") % bonePtr->getName());
	}
}

void	EngineMesh::createRootBone(){
	mRootBody = getEngine()->createPhysicBox()->isBody();
	mRootBody->setPosition(getPosition());
	mRootBody->setOrientation(getOrientation());
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

void	EngineMesh::createPhysicBodies(){
	float boneWidth = 2;
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		//EngineBody* body = getEngine()->createPhysicStatic()->isBody();
		EngineBody* body = getEngine()->createPhysicBox()->isBody();

		float size = getBoneSize((*iter).bone);
		Vec3	localSize = Vec3(0,size,0);
		Vec3	localPos = getBoneOrientation((*iter).bone) * localSize;

		body->setSize(Vec3(boneWidth,size,boneWidth));
		body->setPosition(localPos + getBonePosition((*iter).bone));

		body->setOrientation(getBoneOrientation((*iter).bone));

		(*iter).body = body;
	}
}

void	EngineMesh::checkForJointCollision(){
	Bone* bone;
	EngineBody* body;
	Bone* parentBone;
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		bone = (*iter).bone;
		body = (*iter).body;
		if (getBoneParent(bone) ) {
			parentBone = getBoneParent(bone);

			if (parentBone->numChildren() > 1) {
				Logger::debug(format("bone: %1% has children: %2% ") % parentBone->getName() % parentBone->numChildren());

				Vec3 boneSize = body->getSize();
				
				body->setSize(
					Vec3(
						boneSize.X() * 0.5f,
						boneSize.Y() * 0.30f,
						boneSize.Z() * 0.5f
					));


			}
		}
	}
}

Bone*	EngineMesh::getBoneParent(Bone* bone){
	return (Bone*) bone->getParent();
}

void	EngineMesh::createPhsyisJoints() {
	Bone* bone;
	EngineBody* body;
	EngineJoint* joint;
	std::vector<BoneBody>::iterator	iter;
	Vec3		globalAnchor;
	Vec3		anchor1;
	Vec3		anchor2;
	EngineBody*	parentBone;
	Quat		parentOrientation;
	Quat	 	bodyOrientation;
	Quat		jointOrientation;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		bone = (*iter).bone;
		body = (*iter).body;

		if (getBoneParent(bone) && getBodyOfBone(getBoneParent(bone)) ) {
			parentBone = getBodyOfBone(getBoneParent(bone));

			
		} else {
			Logger::debug(format("bone has no parent: %1% ") % bone->getName());
			parentBone = mRootBody;
			mRootBone = bone;

		}

		parentOrientation = parentBone->getOrientation();
		bodyOrientation = body->getOrientation();
		//jointOrientation = bodyOrientation * parentOrientation.inverse();
		jointOrientation = parentOrientation * bodyOrientation.inverse();

		globalAnchor = getBonePosition(bone);
		anchor1 = globalAnchor - parentBone->getPosition();
		anchor1 = parentBone->getOrientation().inverse() * anchor1;
		anchor2 = globalAnchor - body->getPosition();
		anchor2 = body->getOrientation().inverse() * anchor2;
		joint = getEngine()->createJoint(
			parentBone,
			body
			)->isJoint();

		joint->setAnchor1(anchor1);
		joint->setAnchor2(anchor2);
		joint->setAnchor2Orientation(jointOrientation);
		joint->setLimits(0,0);
	}
}

Vec3	EngineMesh::getBonePosition(Bone* bone) {
	Vec3 bonePos = Quat(getNode()->getOrientation()) * Vec3(bone->_getDerivedPosition());
	Vec3 scaledPos = Vec3(getNode()->getScale()) * bonePos;
	return Vec3(scaledPos + Vec3(getNode()->getPosition()));
}

Quat	EngineMesh::getBoneOrientation(Bone* bone){
	Quat boneQuat = Quat(bone->_getDerivedOrientation());
	return Quat(boneQuat * getOrientation());
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
