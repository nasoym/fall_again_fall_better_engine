#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

#include "engine_body.h"
#include "engine_joint.h"

EngineMesh::EngineMesh(Engine* engine,const char* meshName) :
	EngineGuiShape(engine),
	mRootBone(0)
	{

    setEntity(getEngine()->getSceneManager()->createEntity(meshName));
	setColour(0.2f,0.2f,0.2f,0.3f);
    getNode()->attachObject(getEntity());

	setSize(Vec3(1000,1000,1000));
	setPosition(Vec3(0,150,0));

	enableBones();

	mRootBone = findRootBone();
	Logger::debug(format("found root bone: %1% ") % mRootBone->getName());
	createPhysics(mRootBone);
	calcLocalPosOfRootBone();
	createDebugObjects();

	mRootShape = getEngine()->createGuiBox()->isGuiShape();
	mRootShape->setColour(1,0,0,0.5f);
	mRootShape->setSize(Vec3(20,6,6));
	mRootShape->setPosition(getPosition());
	mRootShape->setOrientation(getOrientation());
}

EngineMesh::~EngineMesh(){
}

void		EngineMesh::printEulerAngles(Quat quat){
	Vec3 euler = quat.toAngles();
	Logger::debug(format("orientation in euler: %1% %2% %3%") % 
			euler.X() % euler.Y() % euler.Z() );
}

void		printVector3(Vec3 & vec3){
	Logger::debug(format("vec: %1% %2% %3%") % 
			vec3.X() % vec3.Y() % vec3.Z() );
}

void		EngineMesh::enableBones(){
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
	//if (false) {
		Vec3	rootBodyPos = rootBody->getPosition();
		Quat	rootBodyQuat = rootBody->getOrientation();
		setPosition(rootBodyPos - (rootBodyQuat* mLocalPos));
		setOrientation(rootBodyQuat * mLocalQuat);
	}
	if (mRootShape) {
	//if (false) {
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
			Vec3 localSize = body->getSize();
			localSize = Vec3(localSize.X() * -1, 0,0);
			localPos = body->getOrientation() * localSize;
		}
		Vec3	finalPos = localPos + body->getPosition();
		boneSetPosition(bone,finalPos);
	}

	EngineGuiContainer* container = getContainerOfBone(bone);
	if (container) {
		container->setPosition(getBonePosition(bone));
		container->setOrientation(getBoneOrientation(bone,false));
		//container->setOrientation(body->getOrientation());
	}

	if (bone) {
		Bone*	childBone;
		Ogre::Bone::ChildNodeIterator childIter = bone->getChildIterator();
		while(childIter.hasMoreElements()){
			childBone = (Ogre::Bone*)childIter.getNext();
			updateBone(childBone);
		}
	}
}

void	EngineMesh::createPhysics(Bone* bone) {
	createPhysicBodies(bone);
	Bone*	childBone;
	Ogre::Bone::ChildNodeIterator childIter = bone->getChildIterator();
	while(childIter.hasMoreElements()){
		childBone = (Ogre::Bone*)childIter.getNext();
		createPhysics(childBone);
	}
}

void	EngineMesh::createDebugObjects(){
	Bone* bone;
	EngineGuiShape* shape;
	float 	boneWidth = 1.0f;
	float	boneSize;
	float	debugSize = 5.0f;
	Vec3	localSize;
	Vec3	localPos;
	EngineGuiContainer* container;
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		bone = (*iter).bone;
		container = new EngineGuiContainer(getEngine());
		setContainerForBone(bone,container);
		container->addDebugAxises(5,0.5);
	}
}

void	EngineMesh::createPhysicBodies(Bone* bone){
	Logger::debug(format("create physic body for: %1% ") % bone->getName());

	EngineBody* body;
	bool bodyIsStatic = false;
	bool createJoint = false;
	if (getBoneParent( bone ) ) {
		if (getBoneParent(getBoneParent( bone) ) ) {
		} else {
			//bodyIsStatic = true;
		}
		createJoint = true;
	} else {
		//bodyIsStatic = true;
	}
	//bodyIsStatic = true;

	if (bodyIsStatic) {
		Logger::debug("bone is static");
		body = getEngine()->createPhysicStatic()->isBody();
		createJoint = false;
	} else {
		body = getEngine()->createPhysicBox()->isBody();
	}

	//body->setColour(1,1,1,0.5f);
	float 	boneWidth = 2.0f;
	float 	boneLength = getBoneSize(bone);
	body->setSize(Vec3(boneLength,boneWidth,boneWidth));
	body->setPosition(
		getBoneOrientation(bone) * Vec3(boneLength,0,0)
		+ getBonePosition(bone)
		);
	body->setOrientation(getBoneOrientation(bone));
	setBodyForBone(bone,body);

	if (createJoint) {
		EngineJoint* joint = createJointToParent(bone);
		setJointForBone(bone,joint);
		checkForJointCollision(bone);
	}
}

EngineJoint* 	EngineMesh::createJointToParent(Bone* bone) {
	EngineJoint* joint = 0;
	if (getBodyOfBone(bone) && getBoneParent(bone) && getBodyOfBone(getBoneParent(bone)) ) {
		EngineBody*	parentBody = getBodyOfBone(getBoneParent(bone));
		EngineBody* body = getBodyOfBone(bone);
		Logger::debug(format("create joint from : %1% to %2%") %bone->getName() % getBoneParent(bone)->getName());

		Vec3 localCenter = getBonePosition(bone);
		Quat localCenterOrientation = parentBody->getOrientation();

		Vec3 globalPosition = body->getPosition(); 
		Vec3 localPosition = localCenterOrientation.inverse() *
			(globalPosition -localCenter);
		localPosition.normalise();
		Quat localOrientation = Quat().fromTwoVectors(Vec3(1,0,0),localPosition);

		joint = getEngine()->createJoint(parentBody, body)->isJoint();
		Vec3 globalAnchor = getBonePosition(bone);
		joint->setAnchor1(translateGlobalAnchorToLocal(parentBody,globalAnchor));
		joint->setAnchor2(translateGlobalAnchorToLocal(body,globalAnchor));
		joint->setAnchor1Orientation(localOrientation);
		joint->setLimits(2,2);

		joint->addDebugAxises(8,0.25);

	}
	return joint;
}

void	EngineMesh::checkForJointCollision(Bone* bone){
	Bone* parentBone;
	EngineBody* body = getBodyOfBone(bone);
	EngineJoint* joint = getJointOfBone(bone);
	if(!body) {
		Logger::debug("bone has no body");
	}
	if(!joint) {
		Logger::debug("bone has no joint");
	}

	if (getBoneParent(bone) ) {
		parentBone = getBoneParent(bone);
		if (parentBone->numChildren() > 1) {
			Logger::debug(format("parent of: %1% is: %2% and has children: %3% ") % bone->getName() % parentBone->getName() % parentBone->numChildren());
			Vec3 bodySize = body->getSize();
			body->setSize(
				Vec3(
					bodySize.X() * 0.3f, 
					bodySize.Y() * 0.6f, 
					bodySize.Z() * 0.6f
				));
			if ( joint ) {
				//joint->setLimits(30,30);
				//joint->setLimits(0,0);
			}
		}
	}
}


