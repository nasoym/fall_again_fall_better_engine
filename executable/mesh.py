def createBody(Engine,EngineModule):
	o = Engine.createPhysicBox()
	return o

def createStaticBody(Engine,EngineModule):
	o = Engine.createPhysicStatic()
	return o

def createBones(Engine,EngineModule,mesh,boneName=None):
	if not boneName:
		boneName = mesh.getRootBoneName()
	createBoneBody(Engine,EngineModule,mesh,boneName)
	childBones = mesh.getBoneNameChildren(boneName)
	for i in range(0,childBones):
		childBoneName = mesh.getBoneNameChildName(boneName,i)
		createBones(Engine,EngineModule,mesh,childBoneName)

def createBoneBody(Engine,EngineModule,mesh,boneName):
	boneWidth = 2.0
	defaultBoneLength = 5
	boneLength = mesh.getBoneNameSize(boneName)
	if boneLength == 0:
		boneLength = defaultBoneLength
	#boneBody = createStaticBody(Engine,EngineModule)
	boneBody = createBody(Engine,EngineModule)
	boneBody.setSize(EngineModule.Vec3(boneLength,boneWidth,boneWidth))
	mesh.setBodyForBoneName(boneName,boneBody)
	boneParentName = mesh.getBoneNameParentName(boneName)

	print("bone: " + str(boneName) + " parent: " + str(boneParentName))
	if boneParentName == "":
		print("create bone: " + str(boneName) )
		boneBody.setOrientation(
			mesh.getBoneNameOrientation(boneName,False)
			* EngineModule.Quat().fromAngles(0,0,90)
			)
		boneBody.setPosition(
			mesh.getBoneNamePosition(boneName)
			+ (boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) )
		)
	else:
		print("create bone: " + str(boneName) + " as child of: " + str(boneParentName) )
		boneParentBody = mesh.getBodyOfBoneName(boneParentName)
		print("parent body: " + str(boneParentBody))
		if boneParentBody:
			print("parent has body")
		else:
			print("parent has NO body")
		if not boneParentBody == 0:
			pass

		boneLocalPosition = mesh.getBoneNameLocalPosition(boneName)
		boneLocalOrientation = mesh.getBoneNameLocalOrientation(boneName)
		scaledBoneLocalPosition = boneLocalPosition * mesh.getMeshScale()
		scaledFlippedBoneLocalPosition = EngineModule.Vec3(scaledBoneLocalPosition.Y(), scaledBoneLocalPosition.X(), scaledBoneLocalPosition.Z())				

		localOrientationAxis = boneLocalOrientation.toAxis()
		localOrientationAngle = boneLocalOrientation.toAngle()

		rotatedOrientationAxis = EngineModule.Quat().fromAngles(0,0,-90) * localOrientationAxis
		rotatedLocalOrientation = EngineModule.Quat().fromAngleAxis(localOrientationAngle,rotatedOrientationAxis)

		parentOrientation = boneParentBody.getOrientation()
		parentPosition = boneParentBody.getPosition()

		parentBoneLength = mesh.getBoneNameSize(boneParentName)
		if parentBoneLength == 0:
			parentBoneLength = defaultBoneLength

		boneBody.setOrientation(parentOrientation * rotatedLocalOrientation)

		"""
		bonePosition = parentPosition  
		bonePosition -= (parentOrientation * EngineModule.Vec3(parentBoneLength,0,0))
		bonePosition += (parentOrientation * scaledFlippedBoneLocalPosition)
		bonePosition += (boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) )
		boneBody.setPosition(bonePosition)   
		"""
		boneBody.setPosition( parentPosition  
			- (parentOrientation * EngineModule.Vec3(parentBoneLength,0,0))
			+ (parentOrientation * scaledFlippedBoneLocalPosition)
			+ (boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) )
			)

		joint = Engine.createJoint(boneParentBody,boneBody)
		globalAnchor = parentPosition
		globalAnchor -= (parentOrientation * EngineModule.Vec3(parentBoneLength,0,0))
		globalAnchor += (parentOrientation * scaledFlippedBoneLocalPosition)

		parentLocalAnchor = boneParentBody.getOrientation().inverse() * (globalAnchor - boneParentBody.getPosition())
		bodyLocalAnchor = boneBody.getOrientation().inverse() * (globalAnchor - boneBody.getPosition())

		joint.setAnchor1(parentLocalAnchor)
		joint.setAnchor2(bodyLocalAnchor)
		joint.setAnchor1Orientation(rotatedLocalOrientation)
		joint.setLimits(10,10)

		joint.addDebugAxises(1,0.2)
		mesh.setJointForBoneName(boneName,joint)

		parentChildren = mesh.getBoneNameChildren(boneParentName)
		if parentChildren > 1:
			boneBody.setSize( boneBody.getSize() * EngineModule.Vec3(0.3,0.6,0.6) )




