"""creators:
	c: create
		1: cube
		2: capsule
		3: sphere 
		4: space cage
		5: mesh character
		6: ragdoll
		
		0: static modifier
"""

import createobjects as create
import ragdoll
import dynamic_mesh as dyn_mesh
import articulation_mesh as art_mesh
import helpers

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_C:
		if len(selection.get()) == 1:
			if selection.get()[0].isActor(): 
				o = selection.get()[0]
				numShapes = o.howManyPhysicShapes()
				size = EngineModule.Vec3(10,10,10)
				size = EngineModule.Vec3(1,1,1)

				method=""
				firstShape = o.getShapeByIndex(0)

				if Engine.isKeyDown(EngineModule.Keys.K_1):
					shape = o.addBox(size)
					method = "addBox"
				if Engine.isKeyDown(EngineModule.Keys.K_2):
					shape = o.addCapsule(size)
					method = "addCapsule"
				if Engine.isKeyDown(EngineModule.Keys.K_3):
					shape = o.addSphere(size)
					method = "addSphere"

				if firstShape.hasColour():
					colour = firstShape.getColour()
					alpha = firstShape.getAlpha()
					shape.setColour(colour.x,colour.y,colour.z,alpha)

				shape.setName(str(numShapes+1))

				selection.clear()
				selection.add(shape)

				text = method + "(Engine,EngineModule"
				text += ",bodyName='" + o.getName() + "'"
				text += ",shapeName='" + shape.getName() + "'"
				text += ",size=EngineModule.Vec3(" + str(size) + ")"
				text += ",r=" + str(colour.x)
				text += ",g=" + str(colour.y)
				text += ",b=" + str(colour.z)
				text += ",a=" + str(alpha)
				text += ")"
				helpers.storeOperation(text)

		else:

			if (Engine.isKeyDown(EngineModule.Keys.K_1)
				or Engine.isKeyDown(EngineModule.Keys.K_2)
				or Engine.isKeyDown(EngineModule.Keys.K_3) ):

				size = EngineModule.Vec3(10,10,10)
				if Engine.isKeyDown(EngineModule.Keys.K_0):
					o = Engine.createStaticActor()
				else:
					o = Engine.createDynamicActor()

				if Engine.isKeyDown(EngineModule.Keys.K_1):
					shape = o.addBox(size)
				elif Engine.isKeyDown(EngineModule.Keys.K_2):
					shape = o.addCapsule(size)
				elif Engine.isKeyDown(EngineModule.Keys.K_3):
					shape = o.addSphere(size)
				shape.setMaterialName("Body")
				shape.setName("1")
				o.setPosition(EngineModule.Vec3(0,200,0))

			if Engine.isKeyDown(EngineModule.Keys.K_4):
				print("create spacecage")
				create.createSpaceCage(Engine,EngineModule,EngineModule.Vec3(600,600,600))


			elif Engine.isKeyDown(EngineModule.Keys.K_6):
				print("create ragdoll")
				char = ragdoll.createHumanBodyParts(Engine,
					EngineModule,size=5,
					pos=EngineModule.Vec3(0,150,0),
					base=False)
				ragdoll.createHumanJoints(Engine,EngineModule,char)
				ragdoll.createLimits(Engine,EngineModule,char,45)
				ragdoll.createLimitsHuman(Engine,EngineModule,char)

			elif Engine.isKeyDown(EngineModule.Keys.K_5):

				if not Engine.isKeyDown(EngineModule.Keys.K_0):
					print("create character mesh")
					o = Engine.createMesh("Character.mesh")
					o.setName("Character.mesh")
					#o = Engine.createMesh("tube.mesh")
					#o.setColour(1,0,0,0.2)
					#o.setColour(1,0,0,0.9)
					o.setMaterialName("Body")
					o.setSize(EngineModule.Vec3(1,1,1)*1000)
					o.setPosition(EngineModule.Vec3(0,150,0))

					dyn_mesh.createBones(Engine,EngineModule,o)
					#art_mesh.createBones(Engine,EngineModule,o)
					o.setUnselectable()
					o.calcLocalPosOfRootBone()

					Engine.physicPauseToggle()
				else:
		
					print("create character mesh with ground")
					o = Engine.createMesh("Character.mesh")
					o.setName("Character.mesh")
					#o.setColour(1,0,0,0.2)
					#o.setColour(1,0,0,0.9)
					#o.setMaterialName("SSAO/GBuffer")
					o.setSize(EngineModule.Vec3(1,1,1)*1000)
					o.setPosition(EngineModule.Vec3(0,150,0))
					rotationVec = EngineModule.Vec3(0,0,90)
					dyn_mesh.createBones(Engine,EngineModule,o)
					o.setUnselectable()
					o.calcLocalPosOfRootBone()
					o.setRotationX(rotationVec.x)
					o.setRotationY(rotationVec.y)
					o.setRotationZ(rotationVec.z)
					Engine.physicPauseToggle()

					body13 = None
					body14 = None
					body14 = o.getBodyOfBoneName("toes-r")
					body13 = o.getBodyOfBoneName("toes-l")
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



