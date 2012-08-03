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
    //getEntity()->setMaterialName("test2");
    //getEntity()->setMaterialName("transp_border");
    //getEntity()->setMaterialName("transp_blue");
    //getEntity()->setMaterialName("transp_red");
	setColour(0.2f,0.2f,0.2f,0.3f);
	getEntity()->setCastShadows(true);
    getNode()->attachObject(getEntity());

	setSize(Vec3(1000,1000,1000));
	setPosition(Vec3(0,150,0));

	enableBones();
    Logger::debug("creating root bone");
	createRootBone();
    Logger::debug("creating physic bodies");
	createPhysicBodies();
	createPhsyisJoints();
	checkForJointCollision();

    Logger::debug("creating debug objects");
	createDebugObjects();

	mRootBone = getRootBone();
}

EngineMesh::~EngineMesh(){
}

EngineBody*				EngineMesh::getRootBody(){
	return mRootBody;
}

void	EngineMesh::guiUpdate(){
	if(getRootBody()){
		setPosition(getRootBody()->getPosition());
		setOrientation(getRootBody()->getOrientation());
	}
	updateBone(mRootBone);
}

void	EngineMesh::physicUpdate(){
}

void	EngineMesh::updateBone(Bone* bone){
	EngineBody* 	body = getBodyOfBone(bone);
	if (body) {
		boneSetOrientation(bone,
			body->getOrientation()
			//* Quat().fromAngle(0,0,90).inverse() 
			);
		Vec3	localPos = 
			body->getOrientation() * 
			getJointOfBone(bone)->getAnchor2();
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
	//mRootBody = getEngine()->createPhysicStatic()->isBody();
	mRootBody->setMaterialName("Body");
	mRootBody->setPosition(getPosition());
	mRootBody->setSize(Vec3(5,3,3));
	mRootBody->setColour(1,0,0,0.5f);
	mRootBody->setOrientation(
		getOrientation()
		//* Quat().fromAngle(0,0,90)
		);
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

void	EngineMesh::createPhysicBodies(){
	float boneWidth = 1.0f;
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		//EngineBody* body = getEngine()->createPhysicStatic()->isBody();
		//TODO why crashing at shutdown when using statics ?

		EngineBody* body = getEngine()->createPhysicBox()->isBody();
		body->setColour(1,1,1,0.5f);

		float size = getBoneSize((*iter).bone);
		//Vec3	localSize = Vec3(0,size,0);
		Vec3	localSize = Vec3(size,0,0);
		Vec3	localPos = getBoneOrientation((*iter).bone) * localSize;

		//body->setSize(Vec3(boneWidth,size,boneWidth));
		body->setSize(Vec3(size,boneWidth,boneWidth));
		body->setPosition(localPos + getBonePosition((*iter).bone));
		body->setOrientation(
			getBoneOrientation((*iter).bone)
			//* Quat().fromAngle(0,0,90)
			);
		(*iter).body = body;
	}
}

Bone*	EngineMesh::getRootBone() {
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		if (!getBoneParent((*iter).bone)) {
			return (*iter).bone;
		}
	}
	return 0;
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

	Vec3 jointEuler;
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

		if (!getBoneOfBody(parentBone)) {
			parentOrientation = parentBone->getOrientation();
			//parentOrientation = parentOrientation * Quat().fromAngle(-90,0,0);
		} else {
			//parentOrientation = getBoneOrientation(getBoneOfBody(parentBone));
			parentOrientation = parentBone->getOrientation();
		}
		//bodyOrientation = getBoneOrientation(getBoneOfBody(body));
		bodyOrientation = body->getOrientation();
		jointOrientation = bodyOrientation * parentOrientation.inverse();
		//jointEuler = jointOrientation.toAngles();
		//Logger::debug(format("orientationA: %1% %2% %3%") % 
		//		jointEuler.X() % jointEuler.Y() % jointEuler.Z() );

		globalAnchor = getBonePosition(bone);
		anchor1 = globalAnchor - parentBone->getPosition();
		anchor1 = parentBone->getOrientation().inverse() * anchor1;
		anchor2 = globalAnchor - body->getPosition();
		anchor2 = body->getOrientation().inverse() * anchor2;

		joint = getEngine()->createJoint(parentBone, body)->isJoint();

		joint->setAnchor1(anchor1);
		joint->setAnchor2(anchor2);
		joint->setAnchor2Orientation(jointOrientation);
		joint->setLimits(1,1);
		(*iter).joint = joint;
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
				Vec3 bodySize = body->getSize();
				body->setSize(
					Vec3(
						bodySize.X() * 0.3f, 
						bodySize.Y() * 0.6f, 
						bodySize.Z() * 0.6f
					));
				(*iter).joint->setLimits(20,20);
			}
		}
	}
}


