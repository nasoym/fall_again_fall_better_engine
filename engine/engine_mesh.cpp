#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

#include "engine_body.h"
#include "engine_joint.h"
#include "engine_gui_shape.h"

EngineMesh::EngineMesh(Engine* engine,const char* meshName) :
	EngineGuiShape(engine),
	mRootBone(0),
	mRootShape(0),
	mLocalPos(Vec3()),
	mLocalQuat(Quat())
	{
    setEntity(getEngine()->getSceneManager()->createEntity(meshName));
	//setColour(0.8f,0.8f,1.0f,0.8f);
	setMaterialName("Body");
    getNode()->attachObject(getEntity());
	setSize(Vec3(1,1,1) * 1000);
	setPosition(Vec3(0,150,0));

	setupAllBones();

	mRootBone = findRootBone();
	//Logger::debug(format("found root bone: %1% ") % mRootBone->getName());
	createPhysics(mRootBone);

	calcLocalPosOfRootBone();
	//createAllDebugObjects();
	//createDebugForBone(mRootBone);

	/*
	mRootShape = getEngine()->createGuiBox()->isGuiShape();
	mRootShape->setColour(1,0,0,0.5f);
	mRootShape->setSize(Vec3(5,2,2));
	mRootShape->setPosition(getPosition());
	mRootShape->setOrientation(getOrientation());
	*/
}

EngineMesh::~EngineMesh(){
}

void		EngineMesh::setupAllBones(){
	SkeletonInstance*		skeleton = getEntity()->getSkeleton();
	Skeleton::BoneIterator	boneIter = skeleton->getBoneIterator();
	Bone*					bonePtr;
	while(boneIter.hasMoreElements()) {
		bonePtr = boneIter.getNext();
		bonePtr->setManuallyControlled(true);
		mBoneBodies.push_back(BoneBody(bonePtr));
		Logger::debug(format("found bone: %1% ") % bonePtr->getName());
	}
}

void	EngineMesh::guiUpdate(){
	EngineBody* rootBody = getBodyOfBone(mRootBone);
	if (rootBody) {
		Vec3	rootBodyPos = rootBody->getPosition();
		Quat	rootBodyQuat = rootBody->getOrientation();
		setPosition(rootBodyPos - (rootBodyQuat*mLocalPos));
		setOrientation(rootBodyQuat * mLocalQuat);
	}
	if (mRootShape) {
		mRootShape->setPosition(getPosition());
		mRootShape->setOrientation(getOrientation());
	}
	updateBone(mRootBone);
}

void 	EngineMesh::calcLocalPosOfRootBone() {
	EngineBody* rootBody = getBodyOfBone(mRootBone);
	if (rootBody) {
		Vec3	rootBodyPos = rootBody->getPosition();
		Quat	rootBodyQuat = rootBody->getOrientation();
		mLocalPos = rootBodyPos - getPosition();
		mLocalPos = rootBodyQuat.inverse() * mLocalPos;
		mLocalQuat = getOrientation() * rootBodyQuat.inverse();
	}
}

void	EngineMesh::updateBone(Bone* bone){
	EngineBody* body = getBodyOfBone(bone);
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

void	EngineMesh::createPhysics(Bone* bone) {
	createPhysicBodiesFromParent(bone);
	Bone*	childBone;
	Ogre::Bone::ChildNodeIterator childIter = bone->getChildIterator();
	while(childIter.hasMoreElements()){
		childBone = (Ogre::Bone*)childIter.getNext();
		createPhysics(childBone);
	}
}

void	EngineMesh::createPhysicBodiesFromParent(Bone* bone){
	float 	boneWidth = 2.0f;
	EngineBody* boneBody;
	float 	boneLength = getBoneSize(bone);
	//boneBody = getEngine()->createPhysicStatic()->isBody();
	boneBody = getEngine()->createPhysicBox()->isBody();
	setBodyForBone(bone,boneBody);
	boneBody->setSize(Vec3(boneLength,boneWidth,boneWidth));

	if (getBoneParent(bone) ) {
		if (getBodyOfBone(getBoneParent(bone))) {
			Bone* parentBone = getBoneParent(bone);
			EngineBody*	parentBody = getBodyOfBone(parentBone);
			Logger::debug(format("create: %1% as child of: %2%") % bone->getName() % parentBone->getName());

			Vec3	boneLocalPosition = Vec3(bone->getPosition());
			Quat	boneLocalOrientation = Quat(bone->getOrientation());
			Vec3	scaledBoneLocalPosition = boneLocalPosition * Vec3(getNode()->getScale());

			Vec3	scaledFlippedBoneLocalPosition;
			scaledFlippedBoneLocalPosition.x = scaledBoneLocalPosition.y;
			scaledFlippedBoneLocalPosition.y = scaledBoneLocalPosition.x;
			scaledFlippedBoneLocalPosition.z = scaledBoneLocalPosition.z;

			Vec3	localOrientationAxis = boneLocalOrientation.toAxis();
			float	localOrientationAngle = boneLocalOrientation.toAngle();

			Vec3	rotatedOrientationAxis = Quat().fromAngles(0,0,-90) * localOrientationAxis;
			Quat	rotatedLocalOrientation = Quat().fromAngleAxis(localOrientationAngle,rotatedOrientationAxis);

			Quat	parentOrientation = parentBody->getOrientation();
			Vec3	parentPosition = parentBody->getPosition();

			float 	parentBoneLength = getBoneSize(parentBone);

			boneBody->setOrientation(parentOrientation * rotatedLocalOrientation);
			boneBody->setPosition( parentPosition  
				- (parentOrientation * Vec3(parentBoneLength,0,0))
				+ (parentOrientation * scaledFlippedBoneLocalPosition)
				+ (boneBody->getOrientation() * Vec3(boneLength,0,0) )
				);
			EngineJoint* joint = createJointToParent(
				bone,
				parentPosition  
				- (parentOrientation * Vec3(parentBoneLength,0,0))
				+ (parentOrientation * scaledFlippedBoneLocalPosition)
				,
				rotatedLocalOrientation);
			setJointForBone(bone,joint);
			checkForJointCollision(bone);
			//boneBody->addDebugAxises(2,0.2);

		}
	} else {
		Logger::debug(format("bone: %1% has no parent") % bone->getName());
		boneBody->setOrientation(
			getBoneOrientation(bone,false)
			* Quat().fromAngles(0,0,90)
			);
		boneBody->setPosition(
			getBonePosition(bone)
			+ (boneBody->getOrientation() * Vec3(boneLength,0,0) )
		);
		//boneBody->addDebugAxises(2,0.2);
	}
}

EngineJoint* 	EngineMesh::createJointToParent(Bone* bone,Vec3 & anchor,Quat & jointOrientation){
	EngineJoint* joint = 0;
	if (getBodyOfBone(bone) && getBoneParent(bone) && getBodyOfBone(getBoneParent(bone)) ) {
		EngineBody*	parentBody = getBodyOfBone(getBoneParent(bone));
		EngineBody* body = getBodyOfBone(bone);
		Logger::debug(format("create joint from : %1% to %2%") %bone->getName() % getBoneParent(bone)->getName());
		joint = getEngine()->createJoint(parentBody, body)->isJoint();
		joint->setAnchor1(translateGlobalAnchorToLocal(parentBody,anchor));
		joint->setAnchor2(translateGlobalAnchorToLocal(body,anchor));
		joint->setAnchor1Orientation(jointOrientation);
		//joint->addDebugAxises(8,0.25);
		joint->setLimits(10,10);
	}
	return joint;
}

void	EngineMesh::checkForJointCollision(Bone* bone){
	Bone* parentBone = getBoneParent(bone);
	EngineBody* body = getBodyOfBone(bone);
	if (body && parentBone && (parentBone->numChildren()>1) ) {
		Logger::debug(format("parent of: %1% is: %2% and has children: %3% ") % bone->getName() % parentBone->getName() % parentBone->numChildren());
		body->setSize( body->getSize() * Vec3(0.3,0.6,0.6) );
		EngineJoint* joint = getJointOfBone(bone);
		if ( joint ) {
			//joint->setLimits(30,30);
		}
	}
}

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

Bone*	EngineMesh::getBoneParent(Bone* bone){
	return (Bone*) bone->getParent();
}

Quat	EngineMesh::getBoneOrientation(Bone* bone,bool rotated){
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


