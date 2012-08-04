#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

#include "engine_body.h"
#include "engine_joint.h"

EngineMesh::EngineMesh(Engine* engine,const char* meshName) :
	EngineGuiShape(engine),
	mRootBody(0),
	mRootBone(0)
	{

    setEntity(getEngine()->getSceneManager()->createEntity(meshName));
	setColour(0.2f,0.2f,0.2f,0.3f);
	//getEntity()->setCastShadows(true);
    getNode()->attachObject(getEntity());

	setSize(Vec3(1000,1000,1000));
	setPosition(Vec3(0,150,0));

	enableBones();

	mRootBone = findRootBone();
	Logger::debug(format("found root bone: %1% ") % mRootBone->getName());

	createRootBody();
	createPhysics(mRootBone);
	createDebugObjects();

}

EngineMesh::~EngineMesh(){
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
	if(getRootBody()){
		setPosition(getRootBody()->getPosition());
		setOrientation(getRootBody()->getOrientation());
	}
	updateBone(mRootBone);
}

void	EngineMesh::updateBone(Bone* bone){
	EngineBody* body = getBodyOfBone(bone);
	if (body) {
		boneSetOrientation(bone, body->getOrientation());
		Vec3	localPos = Vec3();
		if (getJointOfBone(bone) ) {
			localPos = body->getOrientation() * getJointOfBone(bone)->getAnchor2();
		}
		Vec3	finalPos = localPos + body->getPosition();
		boneSetPosition(bone,finalPos);
	}
	Bone*	childBone;
	Ogre::Bone::ChildNodeIterator childIter = bone->getChildIterator();
	while(childIter.hasMoreElements()){
		childBone = (Ogre::Bone*)childIter.getNext();
		updateBone(childBone);
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

void	EngineMesh::createRootBody(){
	//mRootBody = getEngine()->createPhysicBox()->isBody();
	mRootBody = getEngine()->createPhysicStatic()->isBody();
	mRootBody->setMaterialName("Body");
	mRootBody->setPosition(getPosition());
	mRootBody->setOrientation(getOrientation());
	mRootBody->setSize(Vec3(5,3,3));
	mRootBody->setColour(1,0,0,0.5f);
}

void	EngineMesh::createDebugObjects(){
	Bone* bone;
	EngineGuiShape* shape;
	float 	boneWidth = 1.0f;
	float	boneSize;
	float	debugSize = 5.0f;
	Vec3	localSize;
	Vec3	localPos;
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		bone = (*iter).bone;

		/*
		boneSize = getBoneSize(bone);
		localSize = Vec3(0,boneSize,0);
		localPos = getBoneOrientation(bone) * localSize;

		shape = getEngine()->createGuiBox()->isGuiShape();
		shape->setColour(1,1,1,0.5f);
		shape->setSize(Vec3(boneWidth,boneSize,boneWidth));
		shape->setPosition(localPos + getBonePosition(bone));
		shape->setOrientation(getBoneOrientation(bone));

		boneSize = getBoneSize(bone);
		localSize = Vec3(boneSize,0,0);
		localPos = getBoneOrientation(bone) * localSize;

		shape = getEngine()->createGuiBox()->isGuiShape();
		shape->setColour(0,1,1,0.5f);
		shape->setSize(Vec3(boneSize,boneWidth,boneWidth));
		shape->setPosition(localPos + getBonePosition(bone));
		shape->setOrientation(getBoneOrientation(bone)); 
		*/

		shape = getEngine()->createGuiBox()->isGuiShape();
		shape->setColour(1,0,0,0.5f);
		shape->setSize(Vec3(debugSize,1,1));
		shape->setPosition(getBonePosition(bone));
		shape->setOrientation(getBoneOrientation(bone));

		shape = getEngine()->createGuiBox()->isGuiShape();
		shape->setColour(0,1,0,0.5f);
		shape->setSize(Vec3(1,debugSize,1));
		shape->setPosition(getBonePosition(bone));
		shape->setOrientation(getBoneOrientation(bone));

		shape = getEngine()->createGuiBox()->isGuiShape();
		shape->setColour(0,0,1,0.5f);
		shape->setSize(Vec3(1,1,debugSize));
		shape->setPosition(getBonePosition(bone));
		shape->setOrientation(getBoneOrientation(bone));

	}

}

void	EngineMesh::createPhysicBodies(Bone* bone){
	Logger::debug(format("create physic body for: %1% ") % bone->getName());

	EngineBody* body;
	bool bodyIsStatic = false;
	if (getBoneParent( bone ) ) {
		if (getBoneParent(getBoneParent( bone) ) ) {
			body = getEngine()->createPhysicBox()->isBody();
		} else {
			body = getEngine()->createPhysicStatic()->isBody();
			bodyIsStatic = true;
			//body = getEngine()->createPhysicBox()->isBody();
		}
	} else {
		body = getEngine()->createPhysicStatic()->isBody();
		bodyIsStatic = true;
	}

	if (bodyIsStatic) {
		Logger::debug("bone is static");
	}

	body->setColour(1,1,1,0.5f);

	float 	boneWidth = 1.0f;
	float 	boneLength = getBoneSize(bone);
	body->setSize(Vec3(boneLength,boneWidth,boneWidth));
	body->setPosition(
		getBoneOrientation(bone) * Vec3(boneLength,0,0)
		+ getBonePosition(bone)
		);
	body->setOrientation(getBoneOrientation(bone));
	setBodyForBone(bone,body);

	if (!bodyIsStatic) {
		EngineJoint* joint = createJointToParent(bone);
		setJointForBone(bone,joint);
		checkForJointCollision(bone);
	}
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
		joint->setLimits(0,0);
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
			Logger::debug("resize");
			body->setSize(
				Vec3(
					bodySize.X() * 0.3f, 
					bodySize.Y() * 0.6f, 
					bodySize.Z() * 0.6f
				));
			if ( joint ) {
				Logger::debug("increase limits");
				//joint->setLimits(30,30);
				joint->setLimits(0,0);
			}
		}
	}
}


