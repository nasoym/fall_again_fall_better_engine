"""
creators:
	c: create
		1: space cage
		2: box
		3: two jointed boxes
		4: ragdoll
		5: mesh character
		6: grounded mesh character
"""

import createobjects as create
import ragdoll
import mesh

def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_C:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			create.createSpaceCage(Engine,EngineModule,EngineModule.Vec3(600,600,600))
		elif Engine.isKeyDown(EngineModule.Keys.K_2):
			o = create.createPhysicBoxFinal(Engine,EngineModule)
			#o = create.createBox(Engine,EngineModule)
			o.setPosition(EngineModule.Vec3(0,150,0))
			o.setSize(EngineModule.Vec3(10,10,10))
		elif Engine.isKeyDown(EngineModule.Keys.K_3):
			a = create.createPhysicBoxFinal(Engine,EngineModule)
			b = create.createPhysicBoxFinal(Engine,EngineModule)

			j = Engine.createJoint(a,b)
			j.setAnchor1Size( EngineModule.Vec3(1,0,0) )
			j.setAnchor2Size( EngineModule.Vec3(-1,0,0) )
			j.setLimits(20,20)
			j.setAnchor1Orientation(
				EngineModule.Quat().fromAngles(0,0,45) )

		elif Engine.isKeyDown(EngineModule.Keys.K_4):
			char = ragdoll.createHumanBodyParts(Engine,
				EngineModule,size=5,
				pos=EngineModule.Vec3(0,150,0),
				base=False)
			ragdoll.createHumanJoints(Engine,EngineModule,char)
			ragdoll.createLimits(Engine,EngineModule,char,45)
			ragdoll.createLimitsHuman(Engine,EngineModule,char)

		elif Engine.isKeyDown(EngineModule.Keys.K_5):
			o = Engine.createMesh("Character.mesh")
			o.setColour(1,0,0,0.2)
			#o.setColour(1,0,0,0.9)
			#o.setMaterialName("Body")
			o.setSize(EngineModule.Vec3(1,1,1)*1000)
			o.setPosition(EngineModule.Vec3(0,150,0))
			mesh.createBones(Engine,EngineModule,o)
			o.setUnselectable()
			o.calcLocalPosOfRootBone()

		elif Engine.isKeyDown(EngineModule.Keys.K_6):
			o = Engine.createMesh("Character.mesh")
			o.setColour(1,0,0,0.2)
			#o.setColour(1,0,0,0.9)
			#o.setMaterialName("Body")
			o.setSize(EngineModule.Vec3(1,1,1)*1000)
			o.setPosition(EngineModule.Vec3(0,150,0))
			mesh.createBones(Engine,EngineModule,o)
			o.setUnselectable()
			o.calcLocalPosOfRootBone()

			body13 = None
			body14 = None
			bonesNumber = o.getNumberOfBones()
			bonesList = []
			for i in range(0,bonesNumber):
				body = o.getBodyByIndex(i)
				if body.getName() == "Bone.014":
					body14 = body
				if body.getName() == "Bone.013":
					body13 = body
			if body13 and body14:
				pos13 = body13.getPosition()
				#pos13 += body13.getOrientation() * body13.getSize() 
				pos14 = body14.getPosition()
				#pos14 += body14.getOrientation() * body14.getSize() 

				halfpos = pos14 - pos13
				halfpos = halfpos * EngineModule.Vec3(0.5,0.5,0.5)
				finalPos = pos13 + halfpos
				finalPos.y -= 2

				xySize = (halfpos.x + halfpos.y ) * 5

				ground = create.createPhysicStaticBoxStructure(Engine,EngineModule)
				ground.setPosition(finalPos)
				ground.setSize(EngineModule.Vec3(
					xySize,1,xySize
					) )
				ground.setOrientation(o.getOrientation())


				globalAnchor = body13.getPosition()
				parentLocalAnchor = ground.getOrientation().inverse() * (globalAnchor - ground.getPosition())
				bodyPosition = body13.getPosition()
				bodyPosition += body13.getOrientation() * (body13.getSize() * EngineModule.Vec3(-1,0,0))
				bodyLocalAnchor = body13.getOrientation().inverse() * (globalAnchor - bodyPosition)

				#joint = create.createJoint(Engine,EngineModule,ground,body13)
				joint = Engine.createJoint(ground,body13)

				joint.setAnchor1(parentLocalAnchor)
				joint.setAnchor2(bodyLocalAnchor)
				#joint.setAnchor1Orientation(EngineModule.Quat().fromAngles(0,0,-90))
				#joint.setAnchor2Orientation(EngineModule.Quat().fromAngles(90,-90,0))
				joint.setAnchor1Orientation(body13.getOrientation() * ground.getOrientation().inverse() )
				#joint.setLimits(40,40)
				#joint.setLimits(10,10)
				#joint.setLimits(1,1)
				joint.setLimits(0,0)

				b = Engine.createGuiBox()
				b.setColour(0,1,1,0.5)
				b.setSize(EngineModule.Vec3(1,4,4))
				b.setScalingFixed()
				joint.addShape(b)

				globalAnchor = body14.getPosition()
				parentLocalAnchor = ground.getOrientation().inverse() * (globalAnchor - ground.getPosition())
				bodyPosition = body14.getPosition()
				bodyPosition += body14.getOrientation() * (body14.getSize() * EngineModule.Vec3(-1,0,0))
				bodyLocalAnchor = body14.getOrientation().inverse() * (globalAnchor - bodyPosition)

				#joint = create.createJoint(Engine,EngineModule,ground,body14)
				joint = Engine.createJoint(ground,body14)

				joint.setAnchor1(parentLocalAnchor)
				joint.setAnchor2(bodyLocalAnchor)
				#joint.setAnchor1Orientation(EngineModule.Quat().fromAngles(0,0,-90))
				#joint.setAnchor2Orientation(EngineModule.Quat().fromAngles(90,-90,0))
				joint.setAnchor1Orientation(body14.getOrientation() * ground.getOrientation().inverse() )
				#joint.setLimits(40,40)
				#joint.setLimits(10,10)
				#joint.setLimits(1,1)
				joint.setLimits(0,0)

				b = Engine.createGuiBox()
				b.setColour(0,1,1,0.5)
				b.setSize(EngineModule.Vec3(1,4,4))
				b.setScalingFixed()
				joint.addShape(b)


def keyReleased(Engine,EngineModule,key,selection,objects):
	pass


