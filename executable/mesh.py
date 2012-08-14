def createBody(Engine,EngineModule):
	o = Engine.createPhysicBox()
	return o

def createStaticBody(Engine,EngineModule):
	o = Engine.createPhysicStatic()
	return o

def createBones(Engine,EngineModule,mesh):
	bonesNumber = mesh.getNumberOfBones()
	bonesList = []
	boneWidth = 2.0
	for i in range(0,bonesNumber):
		boneName = mesh.getBoneNameByIndex(i)
		boneLength = mesh.getBoneNameSize(boneName)
		#boneBody = createStaticBody(Engine,EngineModule)
		boneBody = createBody(Engine,EngineModule)
		boneBody.setSize(EngineModule.Vec3(boneLength,boneWidth,boneWidth))
		mesh.setBodyForBoneName(boneName,boneBody)
		boneParentName = mesh.getBoneNameParentName(boneName)

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

			boneBody.setOrientation(parentOrientation * rotatedLocalOrientation)

			"""
			bonePosition = parentPosition  
			bonePosition -= parentOrientation * EngineModule.Vec3(parentBoneLength,0,0)
			bonePosition += parentOrientation * scaledFlippedBoneLocalPosition
			bonePosition += boneBody.getOrientation() * EngineModule.Vec3(boneLength,0,0) 
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

			"""
			print("anchor1: " + str(parentLocalAnchor))
			print("anchor1: " + str(mesh.translateGlobalAnchorToLocal(boneParentBody,globalAnchor)))
			print("anchor2: " + str(bodyLocalAnchor))
			print("anchor2: " + str(mesh.translateGlobalAnchorToLocal(boneBody,globalAnchor)))
			"""

			joint.setAnchor1(parentLocalAnchor)
			joint.setAnchor2(bodyLocalAnchor)
			joint.setAnchor1Orientation(rotatedLocalOrientation)
			joint.setLimits(10,10)

			joint.addDebugAxises(1,0.2)
			mesh.setJointForBoneName(boneName,joint)

			parentChildren = mesh.getBoneNameChildren(boneParentName)
			if parentChildren > 1:
				boneBody.setSize( boneBody.getSize() * EngineModule.Vec3(0.3,0.6,0.6) )




