#include "logger.h"

#include "engine_mesh.h"
#include "engine.h"

#include "engine_body.h"
#include "engine_joint.h"
#include "engine_gui_shape.h"

std::vector<const char*>	boneNames;
/*

008 head
007 neck

020 lhand
019 llarm
018 luarm
006 lshoulder

017 rhand
016 rlarm
015 luarm
005 rshoulder

003 breast
002 belly

004 lhip
010 luleg
012 llleg
014 lfoot

001 rhip
009 ruleg
011 rlleg
013 rfoot


*/
void setupBoneNames() {
	boneNames.push_back("Bone.017");
	boneNames.push_back("Bone.016");
	boneNames.push_back("Bone.015");
	boneNames.push_back("Bone.005");

	boneNames.push_back("Bone.020");
	boneNames.push_back("Bone.019");
	boneNames.push_back("Bone.018");
	boneNames.push_back("Bone.006");

	boneNames.push_back("Bone.008");
	boneNames.push_back("Bone.007");

	boneNames.push_back("Bone.003");
	boneNames.push_back("Bone.002");

	boneNames.push_back("Bone.004");
	boneNames.push_back("Bone.010");
	boneNames.push_back("Bone.012");
	boneNames.push_back("Bone.014");

	boneNames.push_back("Bone.001");
	boneNames.push_back("Bone.009");
	boneNames.push_back("Bone.011");
	boneNames.push_back("Bone.013");

}

bool isInBoneNames(std::string name) {
	std::vector<const char*>::iterator	iter;
	for(iter=boneNames.begin();iter!=boneNames.end();++iter){
		if (name.compare( (*iter) ) == 0 ) {
			return true;
		}
	}
	return false;
}

EngineMesh::EngineMesh(Engine* engine,const char* meshName) :
	EngineGuiShape(engine),
	mRootBone(0)
	{

    setEntity(getEngine()->getSceneManager()->createEntity(meshName));
	//setColour(0.6f,0.6f,0.6f,0.8f);
	setMaterialName("Body");
    getNode()->attachObject(getEntity());

	setSize(Vec3(1000,1000,1000));
	setPosition(Vec3(0,150,0));

	setupBoneNames();

	enableBones();

	mRootBone = findRootBone();
	Logger::debug(format("found root bone: %1% ") % mRootBone->getName());
	createPhysics(mRootBone);
	calcLocalPosOfRootBone();
	//createDebugObjects();

	mRootShape = getEngine()->createGuiBox()->isGuiShape();
	mRootShape->setColour(1,0,0,0.5f);
	mRootShape->setSize(Vec3(20,6,6));
	mRootShape->setPosition(getPosition());
	mRootShape->setOrientation(getOrientation());
}

EngineMesh::~EngineMesh(){
}

void		printEulerAngles(Quat quat,const char* text){
	Vec3 euler = quat.toAngles();
	Logger::debug(format("%s: %3.3f %3.3f %3.3f") % 
			text % euler.X() % euler.Y() % euler.Z() );
}

void		printVector3(Vec3 & vec3,const char* text){
	Logger::debug(format("%s: %3.3f %3.3f %3.3f") % 
			text % vec3.X() % vec3.Y() % vec3.Z() );
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
	//if (false) {
		//if (isInBoneNames(bone->getName())) {
			boneSetOrientation(bone, body->getOrientation());
			//boneSetOrientation(bone, body->getOrientation(),false); //Y
			Vec3	localPos = Vec3();
			EngineJoint* joint = getJointOfBone(bone);
			if (joint) {
				localPos = body->getOrientation() * joint->getAnchor2();
			} else {
				localPos = body->getOrientation() * 
					(body->getSize() * Vec3(-1,0,0));
					//(body->getSize() * Vec3(0,-1,0)); //Y
			}
			boneSetPosition(bone, localPos + body->getPosition());
			/*
		} else {
			//boneSetOrientation(bone, body->getOrientation());
			boneSetOrientation(bone, body->getOrientation(),false); //Y
			Vec3	localPos = Vec3();
			EngineJoint* joint = getJointOfBone(bone);
			if (joint) {
				localPos = body->getOrientation() * joint->getAnchor2();
			} else {
				localPos = body->getOrientation() * 
					(body->getSize() * Vec3(-1,0,0));
					//(body->getSize() * Vec3(0,-1,0)); //Y
			}
			boneSetPosition(bone, localPos + body->getPosition());
		}
			*/
	}

	EngineGuiContainer* container = getContainerOfBone(bone);
	if (container) {
		container->setPosition(getBonePosition(bone));
		//container->setPosition(body->getPosition());

		//container->setOrientation(getBoneOrientation(bone));
		container->setOrientation(getBoneOrientation(bone,false)); //Y

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

void	EngineMesh::createDebugObjects(){
	Bone* bone;
	EngineGuiContainer* container;
	std::vector<BoneBody>::iterator	iter;
	for(iter=mBoneBodies.begin();iter!=mBoneBodies.end();++iter){
		bone = (*iter).bone;
		container = new EngineGuiContainer(getEngine());
		setContainerForBone(bone,container);
		container->addDebugAxises(5,0.3);
	}
}

void	EngineMesh::createPhysics(Bone* bone) {
	//createPhysicBodies(bone);
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

			Quat	flippedBoneLocalOrientation;

			Vec3	obaxis = boneLocalOrientation.toAxis();
			float	oba = boneLocalOrientation.toAngle();

			Vec3	newAxis = Vec3();
			newAxis = Quat().fromAngles(0,0,-90) * obaxis;

			flippedBoneLocalOrientation.fromAngleAxis(oba,newAxis);

			Quat	parentOrientation = parentBody->getOrientation();
			Vec3	parentPosition = parentBody->getPosition();

			float 	parentBoneLength = getBoneSize(parentBone);
			float 	boneLength = getBoneSize(bone);

			EngineBody* boneBody;
			//boneBody = getEngine()->createPhysicStatic()->isBody();
			boneBody = getEngine()->createPhysicBox()->isBody();
			boneBody->setSize(Vec3(boneLength,boneWidth,boneWidth));
			boneBody->setOrientation(parentOrientation * flippedBoneLocalOrientation);
			boneBody->setPosition( parentPosition  
				- (parentOrientation * Vec3(parentBoneLength,0,0))
				+ (parentOrientation * scaledFlippedBoneLocalPosition)
				+ (boneBody->getOrientation() * Vec3(boneLength,0,0) )
				);
			//boneBody->addDebugAxises(2,0.2);
			setBodyForBone(bone,boneBody);
			EngineJoint* joint = createJointToParent2(
				bone,
				parentPosition  
				- (parentOrientation * Vec3(parentBoneLength,0,0))
				+ (parentOrientation * scaledFlippedBoneLocalPosition)
				,
				flippedBoneLocalOrientation);
			setJointForBone(bone,joint);
			checkForJointCollision(bone);

		}
	} else {
		Logger::debug(format("bone: %1% has no parent") % bone->getName());
		EngineBody* boneBody;
		//boneBody = getEngine()->createPhysicStatic()->isBody();
		boneBody = getEngine()->createPhysicBox()->isBody();
		setBodyForBone(bone,boneBody);

		float 	boneLength = getBoneSize(bone);

		boneBody->setSize(Vec3(boneLength,boneWidth,boneWidth));
		boneBody->setOrientation(
			getBoneOrientation(bone,false)
			//* Quat().fromAngles(0,0,90)
			);
		boneBody->setPosition(
			getBonePosition(bone)
			+ (boneBody->getOrientation() * Vec3(boneLength,0,0) )
		);
		boneBody->addDebugAxises(2,0.2);
	}
}

void	EngineMesh::createPhysicBodies(Bone* bone){
	Logger::debug(format("create physic body for: %1% ") % bone->getName());

	EngineBody* body;
	bool bodyIsStatic = false;
	bool createJoint = false;


	bool createXBone = false;
	if (getBoneParent( bone ) ) {
		if (getBoneParent(getBoneParent( bone) ) ) {
		} else {
			//bodyIsStatic = true;
		}
		createJoint = true;
	} else {
		//bodyIsStatic = true;
	}
	bodyIsStatic = true;

	//if (bone->getName().compare("Bone.017") == 0 ) {
	if (isInBoneNames(bone->getName())) {
		bodyIsStatic = false;
		createXBone = true;
	}

	if (bodyIsStatic) {
		Logger::debug("bone is static");
		body = getEngine()->createPhysicStatic()->isBody();
		createJoint = false;
	} else {
		body = getEngine()->createPhysicBox()->isBody();
	}

	float 	boneWidth = 2.0f;
	float 	boneLength = getBoneSize(bone);
	if (createXBone) {
		body->setSize(Vec3(boneLength,boneWidth,boneWidth));
		//body->setSize(Vec3(boneWidth,boneLength,boneWidth)); //Y
		body->setPosition(
			getBoneOrientation(bone) * Vec3(boneLength,0,0)
			//getBoneOrientation(bone,false) * Vec3(0,boneLength,0) //Y
			+ getBonePosition(bone)
			);
		body->setOrientation(getBoneOrientation(bone));
		//body->setOrientation(getBoneOrientation(bone,false)); //Y
		setBodyForBone(bone,body);

	} else {
		body->setSize(Vec3(boneLength,boneWidth,boneWidth));
		//body->setSize(Vec3(boneWidth,boneLength,boneWidth)); //Y
		body->setPosition(
			getBoneOrientation(bone) * Vec3(boneLength,0,0)
			//getBoneOrientation(bone,false) * Vec3(0,boneLength,0) //Y
			+ getBonePosition(bone)
			);
		//body->setOrientation(getBoneOrientation(bone));
		body->setOrientation(getBoneOrientation(bone,false)); //Y
		setBodyForBone(bone,body);
	}

	if (createJoint) {
		EngineJoint* joint = createJointToParent(bone);
		setJointForBone(bone,joint);
		checkForJointCollision(bone);
	}
}

Quat			EngineMesh::calcJointOrientation(Bone* bone) {
	EngineBody*	parentBody = getBodyOfBone(getBoneParent(bone));
	EngineBody* body = getBodyOfBone(bone);

	Vec3 localCenter = getBonePosition(bone);
	Quat localCenterOrientation = parentBody->getOrientation();

	Vec3 globalPosition = body->getPosition(); 
	Vec3 localPosition = localCenterOrientation.inverse() *
		(globalPosition -localCenter);
	localPosition.normalise();
	Quat jointOrientation = Quat().fromTwoVectors(Vec3(1,0,0),localPosition);

	Logger::debug("--------------------------------");
	printEulerAngles(jointOrientation,"joint orientation from vec");

	Quat	parentOrientation = parentBody->getOrientation();
	Quat	myOrientation = body->getOrientation();

	//Quat	parentOrientation = getBoneOrientation(getBoneParent(bone));
	//Quat	myOrientation = getBoneOrientation(bone);

	Quat	deltaOrientation;
	deltaOrientation = myOrientation * parentOrientation.inverse();
	//printEulerAngles(deltaOrientation,"delta orientation");
	//printEulerAngles(deltaOrientation.inverse(),"delta orientation inv");
	Quat	deltaOrientationInv = deltaOrientation.inverse();

	Quat	test = (
		deltaOrientationInv * 
		Quat().fromAngles(0,0,90) 
		) * Quat().fromAngles(0,90,90) ;

	Quat	oneTotwo = jointOrientation * deltaOrientation.inverse();
	//printEulerAngles(test,"test");
	//printEulerAngles(oneTotwo,"one to two");
	//printEulerAngles(deltaOrientation * oneTotwo,"mult");

	//Quat boneQuat = Quat(getOrientation() * bone->_getDerivedOrientation());

	//printEulerAngles(bone->getOrientation(),"bone orientation");
	//printEulerAngles(bone->getOrientation() * Quat().fromAngles(0,0,90),"bone orientation");
	Quat	boneOrientation = Quat(bone->getOrientation()).inverse();

	Vector3	axis;
	Radian	angle;
	boneOrientation.toOgre().ToAngleAxis(angle,axis);

	Vec3	newAxis = Quat().fromAngles(0,0,90) * Vec3(axis);
	//printVector3(Vec3(axis),"axis");
	//printVector3(newAxis,"newAxis");

	Quat	newOrientation = Quat(angle.valueRadians(),newAxis);
	newOrientation.normalise();
	printEulerAngles(newOrientation,"bone orientation");

	//return newOrientation;


	//return jointOrientation;
	//return deltaOrientationInv;

	//return Quat( Quat().fromAngles(0,0,90) * bone->getOrientation() );
	//return Quat( bone->getOrientation() * Quat().fromAngles(0,0,90));
	//return Quat( bone->getOrientation() * Quat().fromAngles(0,0,-20));
	if (bone->getName().compare("Bone.005") == 0 ) { 
		//return Quat( bone->getOrientation() * Quat().fromAngles(90,-90,0));
	}
	if (bone->getName().compare("Bone.006") == 0 ) { 
		//return Quat( bone->getOrientation() * Quat().fromAngles(0,90,0));
	}
	/*
	if (	
		(bone->getName().compare("Bone.003") == 0 ) 
		//(bone->getName().compare("Bone.005") == 0 )  ||
		//(bone->getName().compare("Bone.006") == 0 )  ||
		//(bone->getName().compare("Bone.007") == 0 ) 
	){
		return Quat( bone->getOrientation() * Quat().fromAngles(0,90,90));
	} else {
		return Quat( bone->getOrientation() ); //Y
	}
	*/
	return Quat( bone->getOrientation() ); //Y
}

EngineJoint* 	EngineMesh::createJointToParent2(Bone* bone,Vec3 & anchor,Quat & jointOrientation){
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
		//joint->setLimits(0,0);

	}
	return joint;
}

EngineJoint* 	EngineMesh::createJointToParent(Bone* bone) {
	EngineJoint* joint = 0;
	if (getBodyOfBone(bone) && getBoneParent(bone) && getBodyOfBone(getBoneParent(bone)) ) {
		EngineBody*	parentBody = getBodyOfBone(getBoneParent(bone));
		EngineBody* body = getBodyOfBone(bone);
		Logger::debug(format("create joint from : %1% to %2%") %bone->getName() % getBoneParent(bone)->getName());

		joint = getEngine()->createJoint(parentBody, body)->isJoint();
		Vec3 globalAnchor = getBonePosition(bone);
		joint->setAnchor1(translateGlobalAnchorToLocal(parentBody,globalAnchor));
		joint->setAnchor2(translateGlobalAnchorToLocal(body,globalAnchor));

		joint->setAnchor1Orientation(calcJointOrientation(bone));

		joint->setLimits(5,5);
		//joint->setLimits(0,0);

		/*
		if (bone->getName().compare("Bone.005") == 0 ) { 
			joint->addDebugAxises(8,0.25);
		}
		if (bone->getName().compare("Bone.006") == 0 ) { 
			joint->addDebugAxises(8,0.25);
		}
		*/

	}
	return joint;
}

void	EngineMesh::checkForJointCollision(Bone* bone){
	Bone* parentBone = getBoneParent(bone);
	EngineBody* body = getBodyOfBone(bone);
	if (body && parentBone && (parentBone->numChildren()>1) ) {
		Logger::debug(format("parent of: %1% is: %2% and has children: %3% ") % bone->getName() % parentBone->getName() % parentBone->numChildren());
		if (isInBoneNames(bone->getName())) {
			body->setSize( body->getSize() * Vec3(0.3,0.6,0.6) );
		} else {
			body->setSize( body->getSize() * Vec3(0.3,0.6,0.6) );
			//body->setSize( body->getSize() * Vec3(0.6,0.3,0.6) ); //Y
		}
		EngineJoint* joint = getJointOfBone(bone);
		if ( joint ) {
			//joint->setLimits(30,30);
		}
	}
}


