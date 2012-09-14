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
				create.createSpaceCage(Engine,EngineModule,EngineModule.Vec3(6000,600,600))

			elif Engine.isKeyDown(EngineModule.Keys.K_6):
				print("create ragdoll")
				char = ragdoll.createHumanBodyParts(Engine,
					EngineModule,size=5,
					pos=EngineModule.Vec3(0,150,0),
					base=False)
				ragdoll.createHumanJoints(Engine,EngineModule,char)
				ragdoll.createLimits(Engine,EngineModule,char,45)
				ragdoll.createLimitsHuman(Engine,EngineModule,char)

			elif Engine.isKeyDown(EngineModule.Keys.K_7):
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(40.076103210,0.085070647,-4.459388256),EngineModule.Quat(0.999048233,0.000000000,-0.043619387,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(-92.474678040,0.085070647,-33.463573456),EngineModule.Quat(0.953717113,0.000000000,-0.300705880,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(100.000000000,0.094522946,-42.716278076),EngineModule.Quat(0.866025507,0.000000000,0.500000119,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(18.637054443,0.085070647,-93.069076538),EngineModule.Quat(0.608761549,0.000000000,0.793353617,0.000000000))
				"""
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(60.000000000,0.094522946,57.283725739),EngineModule.Quat(0.866025507,0.000000000,0.500000119,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(-98.567276001,0.094522946,103.246383667),EngineModule.Quat(0.965926170,0.000000000,-0.258819163,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(0.000000000,0.094522946,117.283714294),EngineModule.Quat(1.000000000,0.000000000,0.000000000,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(-20.000000000,0.094522946,17.283725739),EngineModule.Quat(0.923879683,0.000000000,-0.382683575,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(120.000000000,0.094522946,57.283725739),EngineModule.Quat(0.953717053,0.000000000,0.300705850,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(-150.000000000,0.094522946,57.283725739),EngineModule.Quat(-0.130526334,0.000000000,-0.991445363,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(-80.000000000,0.050233360,37.283725739),EngineModule.Quat(-0.608761787,0.000000000,-0.793353677,0.000000000))
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(-4.641016006,0.062016498,-40.036834717),EngineModule.Quat(0.500000119,0.000000000,-0.866025686,0.000000000))
				"""

			elif Engine.isKeyDown(EngineModule.Keys.K_5):
				pass
				createFigure(Engine,EngineModule,objects,EngineModule.Vec3(0,0,0),EngineModule.Quat())

def createFigure(Engine,EngineModule,objects,position,quaternion):
	print("create character mesh")
	o = Engine.createMesh("figure.mesh")
	#o = Engine.createMesh("Character.mesh")
	o.setName("figure.mesh")
	#o = Engine.createMesh("tube.mesh")
	o.setMaterialName("Body")
	o.setSize(EngineModule.Vec3(1,1,1)*1000)
	#o.setPosition(EngineModule.Vec3(0,150,0))
	o.setPosition(EngineModule.Vec3(position.x,20,position.z))
	o.setOrientation(quaternion)

	dyn_mesh.createBones(Engine,EngineModule,o)
	#art_mesh.createBones(Engine,EngineModule,o)
	o.setUnselectable()
	o.calcLocalPosOfRootBone()

	ground = addMeshGround(Engine,EngineModule,o)
	ground.setPosition(position)
	ground.setOrientation(quaternion)

	Engine.physicPauseToggle()

	objects.appendList("uleg", o.getBodyOfBoneName("uleg-l"))
	objects.appendList("uleg", o.getBodyOfBoneName("uleg-r"))

	objects.appendList("lleg", o.getBodyOfBoneName("lleg-l"))
	objects.appendList("lleg", o.getBodyOfBoneName("lleg-r"))

	objects.appendList("uarm", o.getBodyOfBoneName("uarm-l"))
	objects.appendList("uarm", o.getBodyOfBoneName("uarm-r"))

	objects.appendList("larm", o.getBodyOfBoneName("larm-l"))
	objects.appendList("larm", o.getBodyOfBoneName("larm-r"))

	objects.appendList("hand", o.getBodyOfBoneName("hand-l"))
	objects.appendList("hand", o.getBodyOfBoneName("hand-r"))

	objects.appendList("hand", o.getBodyOfBoneName("thumb-high-l"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-index-high-l"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-middle-high-l"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-ring-high-l"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-little-high-l"))

	objects.appendList("hand", o.getBodyOfBoneName("thumb-high-r"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-index-high-r"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-middle-high-r"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-ring-high-r"))
	objects.appendList("hand", o.getBodyOfBoneName("finger-little-high-r"))

	objects.appendList("feet", o.getBodyOfBoneName("foot-l"))
	objects.appendList("feet", o.getBodyOfBoneName("foot-r"))

	objects.appendList("feet", o.getBodyOfBoneName("toes-l"))
	objects.appendList("feet", o.getBodyOfBoneName("toes-r"))

	objects.appendList("shoulder", o.getBodyOfBoneName("shoulder-l"))
	objects.appendList("shoulder", o.getBodyOfBoneName("shoulder-r"))

	objects.appendList("root", o.getBodyOfBoneName("root"))
	objects.appendList("belly", o.getBodyOfBoneName("belly"))
	objects.appendList("breast", o.getBodyOfBoneName("cheast"))
	objects.appendList("breast", o.getBodyOfBoneName("breast"))
	objects.appendList("neck", o.getBodyOfBoneName("neck"))
	objects.appendList("head", o.getBodyOfBoneName("head"))






	objects.appendList("uleg-joint", o.getJointOfBoneName("uleg-l"))
	objects.appendList("uleg-joint", o.getJointOfBoneName("uleg-r"))

	objects.appendList("lleg-joint", o.getJointOfBoneName("lleg-l"))
	objects.appendList("lleg-joint", o.getJointOfBoneName("lleg-r"))

	objects.appendList("uarm-joint", o.getJointOfBoneName("uarm-l"))
	objects.appendList("uarm-joint", o.getJointOfBoneName("uarm-r"))

	objects.appendList("larm-joint", o.getJointOfBoneName("larm-l"))
	objects.appendList("larm-joint", o.getJointOfBoneName("larm-r"))

	objects.appendList("hand-joint", o.getJointOfBoneName("hand-l"))
	objects.appendList("hand-joint", o.getJointOfBoneName("hand-r"))

	objects.appendList("hand-joint", o.getJointOfBoneName("thumb-high-l"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-index-high-l"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-middle-high-l"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-ring-high-l"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-little-high-l"))

	objects.appendList("hand-joint", o.getJointOfBoneName("thumb-high-r"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-index-high-r"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-middle-high-r"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-ring-high-r"))
	objects.appendList("hand-joint", o.getJointOfBoneName("finger-little-high-r"))

	objects.appendList("foot-joint", o.getJointOfBoneName("foot-l"))
	objects.appendList("foot-joint", o.getJointOfBoneName("foot-r"))

	objects.appendList("foot-joint", o.getJointOfBoneName("toes-l"))
	objects.appendList("foot-joint", o.getJointOfBoneName("toes-r"))

	objects.appendList("shoulder-joint", o.getJointOfBoneName("shoulder-l"))
	objects.appendList("shoulder-joint", o.getJointOfBoneName("shoulder-r"))

	objects.appendList("belly-joint", o.getJointOfBoneName("belly"))
	objects.appendList("breast-joint", o.getJointOfBoneName("cheast"))
	objects.appendList("breast-joint", o.getJointOfBoneName("breast"))
	objects.appendList("neck-joint", o.getJointOfBoneName("neck"))
	objects.appendList("head-joint", o.getJointOfBoneName("head"))




def addMeshGround(Engine,EngineModule,mesh):
	body14 = mesh.getBodyOfBoneName("toes-r")
	body13 = mesh.getBodyOfBoneName("toes-l")
	ground = None
	if body13 and body14:
		pos13 = body13.getPosition()
		#pos13 += body13.getOrientation() * body13.getSize() 
		pos14 = body14.getPosition()
		#pos14 += body14.getOrientation() * body14.getSize() 

		halfpos = pos14 - pos13
		halfpos = halfpos * EngineModule.Vec3(0.5,0.5,0.5)
		finalPos = pos13 + halfpos
		finalPos.y -= 2

		xySize = (halfpos.x + halfpos.y ) * 2

		#ground = create.createPhysicStaticBoxStructure(Engine,EngineModule)
		#ground.setSize(EngineModule.Vec3(xySize,1,xySize))

		#ground = Engine.createStaticActor()
		ground = Engine.createStaticActor()
		ground.setPosition(finalPos)
		shape = ground.addBox(EngineModule.Vec3(xySize,1,xySize))
		shape.setColour(0,1,0,0.5)
		shape.setScaling1To1()

		ground.setOrientation(mesh.getOrientation())






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

	return ground


