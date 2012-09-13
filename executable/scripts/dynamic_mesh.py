import createobjects as create

def createBones(Engine,EngineModule,mesh,boneName=None):
	if not boneName:
		boneName = mesh.getRootBoneName()
	createBoneBody(Engine,EngineModule,mesh,boneName)
	childBones = mesh.getBoneNameChildren(boneName)
	for i in range(0,childBones):
		childBoneName = mesh.getBoneNameChildName(boneName,i)
		createBones(Engine,EngineModule,mesh,childBoneName)

def getBoneLength(Engine,EngineModule,mesh,boneName):
	defaultBoneLength = 1
	boneLength = mesh.getBoneNameSize(boneName)
	if boneLength == 0:
		boneLength = defaultBoneLength
	return boneLength

def calcBoneGlobalPosRot(Engine,EngineModule,mesh,boneName):
	boneLocalRotation = EngineModule.Quat()
	boneBody = mesh.getBodyOfBoneName(boneName)
	if boneBody:
		print("found boneBody: " + str(boneBody))
		boneOrientation = boneBody.getOrientation()
		bonePosition = boneBody.getPosition()
	else:
		boneParentName = mesh.getBoneNameParentName(boneName)
		boneLength = getBoneLength(Engine,EngineModule,mesh,boneName)
		if boneParentName == "":
			#this is the root bone
			print("root bone: " + str(boneName) )
			boneOrientation = (mesh.getBoneNameOrientation(boneName,False) *
				EngineModule.Quat().fromAngles(0,0,90))
			bonePosition = (mesh.getBoneNamePosition(boneName) +
				(boneOrientation * EngineModule.Vec3(
					getBoneLength(Engine,EngineModule,mesh,boneName),0,0) ))

		else:
			boneLocalPosition = mesh.getBoneNameLocalPosition(boneName)
			boneLocalOrientation = mesh.getBoneNameLocalOrientation(boneName)
			scaledBoneLocalPosition = boneLocalPosition * mesh.getMeshScale()
			scaledFlippedBoneLocalPosition = EngineModule.Vec3(scaledBoneLocalPosition.Y(), scaledBoneLocalPosition.X(), scaledBoneLocalPosition.Z())				

			localOrientationAxis = boneLocalOrientation.toAxis()
			localOrientationAngle = boneLocalOrientation.toAngle()

			rotatedOrientationAxis = EngineModule.Quat().fromAngles(0,0,-90) * localOrientationAxis
			rotatedLocalOrientation = EngineModule.Quat().fromAngleAxis(localOrientationAngle,rotatedOrientationAxis)

			#parentOrientation = boneParentBody.getOrientation()
			#parentPosition = boneParentBody.getPosition()

			parentPosition,parentOrientation,parentLocalRotation = calcBoneGlobalPosRot(Engine,EngineModule,mesh,boneParentName)

			parentBoneLength = getBoneLength(Engine,EngineModule,mesh,boneParentName)
			#parentBoneLength = mesh.getBoneNameSize(boneParentName)
			#if parentBoneLength == 0:
			#	parentBoneLength = defaultBoneLength

			boneOrientation = parentOrientation * rotatedLocalOrientation

			"""
			#TODO why is this calculation working
			bonePosition = parentPosition  
			bonePosition -= (parentOrientation * EngineModule.Vec3(parentBoneLength,0,0))
			bonePosition += (parentOrientation * scaledFlippedBoneLocalPosition)
			bonePosition += (boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) )
			boneBody.setPosition(bonePosition)   
			"""
			bonePosition = (parentPosition  - 
				(parentOrientation * EngineModule.Vec3(parentBoneLength,0,0)) +
				(parentOrientation * scaledFlippedBoneLocalPosition) +
				(boneOrientation * EngineModule.Vec3(boneLength,0,0) ))
			boneLocalRotation = rotatedLocalOrientation

	return bonePosition,boneOrientation,boneLocalRotation
			

def getClosestBoneParentBody(Engine,EngineModule,mesh,boneName):
	boneBody = mesh.getBodyOfBoneName(boneName)
	if boneBody:
		return boneBody
	else:
		boneParentName = mesh.getBoneNameParentName(boneName)
		if boneParentName == "":
			return None
		else:
			return getClosestBoneParentBody(Engine,EngineModule,mesh,boneParentName)


def createBoneBody(Engine,EngineModule,mesh,boneName):
	print("create bone: " + str(boneName) )
	boneWidth = 1.0
	boneLength = getBoneLength(Engine,EngineModule,mesh,boneName)
	#boneLength = mesh.getBoneNameSize(boneName)
	#if boneLength == 0:
	#	boneLength = defaultBoneLength
	boneBody = Engine.createDynamicActor()
	boneBody.setName(str(boneName))


	bonePosition,boneOrientation,boneLocalRotation=calcBoneGlobalPosRot(Engine,EngineModule,mesh,boneName)
	boneBody.setOrientation(boneOrientation)
	boneBody.setPosition(bonePosition)  

	mesh.setBodyForBoneName(boneName,boneBody)

	s = boneBody.addCapsule(EngineModule.Vec3(1,1,1))
	#s = boneBody.addBox(EngineModule.Vec3(1,1,1))
	localBoneWidth = boneWidth
	#localBoneWidth = boneLength * 0.25
	if localBoneWidth > (boneLength * 0.25):
		localBoneWidth = boneLength * 0.25
	s.setLocalSize(EngineModule.Vec3(boneLength,localBoneWidth,localBoneWidth))

	"""
	#print("bone: " + str(boneName) + " parent: " + str(boneParentName))
	if boneParentName == "":
		#this is the root bone
		#print("create bone: " + str(boneName) )
		boneBody.setOrientation(
			mesh.getBoneNameOrientation(boneName,False)
			* EngineModule.Quat().fromAngles(0,0,90)
			)
		boneBody.setPosition(
			mesh.getBoneNamePosition(boneName)
			+ (boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) )
		)
	else:
		#print("create bone: " + str(boneName) + " as child of: " + str(boneParentName) )
		boneParentBody = mesh.getBodyOfBoneName(boneParentName)
		#print("parent body: " + str(boneParentBody))
		if not boneParentBody:
			#print("parent has no body")
			pass
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

		boneBody.setPosition( parentPosition  
			- (parentOrientation * EngineModule.Vec3(parentBoneLength,0,0))
			+ (parentOrientation * scaledFlippedBoneLocalPosition)
			+ (boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) )
			)
		"""
	boneParentName = mesh.getBoneNameParentName(boneName)
	if boneParentName != "":
		boneParentBody = getClosestBoneParentBody(Engine,EngineModule,mesh,boneParentName)
		boneParentPosition,boneParentOrientation,boneParentLocalRotation = calcBoneGlobalPosRot(
			Engine,EngineModule,mesh,boneParentName)
		parentBoneLength = mesh.getBoneNameSize(boneParentName)
		if parentBoneLength == 0:
			parentBoneLength = defaultBoneLength
		if boneParentBody:

			joint = Engine.createJoint(boneParentBody,boneBody)
			#globalAnchor = boneParentPosition
			#globalAnchor -= (boneParentOrientation * EngineModule.Vec3(parentBoneLength,0,0))
			#globalAnchor += (boneParentOrientation * scaledFlippedBoneLocalPosition)

			globalAnchor = bonePosition - (boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) )

			parentLocalAnchor = (boneParentOrientation.inverse() * 
				(globalAnchor - boneParentPosition))
			bodyLocalAnchor = (boneOrientation.inverse() * 
				(globalAnchor - bonePosition))

			joint.setAnchor1(parentLocalAnchor)
			joint.setAnchor2(bodyLocalAnchor)
			#joint.setAnchor1Orientation(rotatedLocalOrientation)
			joint.setAnchor1Orientation(boneLocalRotation)
			#joint.setLimits(1,1)
			joint.setLimits(0,0)
			#joint.setLimits(10,10)
			#joint.setLimits(50,50)
		
			b = Engine.createGuiBox()
			b.setColour(0,0,1,0.2)
			b.setSize(EngineModule.Vec3(boneWidth*0.25,boneWidth*2,boneWidth*2))
			b.setScalingFixed()
			joint.addShape(b)
			#joint.addDebugAxises(1,0.2)
			mesh.setJointForBoneName(boneName,joint)

			parentChildren = mesh.getBoneNameChildren(boneParentName)
			if parentChildren > 1:
				boneBody.getShapeByIndex(0).setLocalSize( boneBody.getSize() * EngineModule.Vec3(0.3,0.6,0.6) )


