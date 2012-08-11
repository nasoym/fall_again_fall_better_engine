import temp

import ragdoll

objects = {}
#objects["ground"] = Engine.createSpaceCage(EngineModule.Vec3(400,400,400))
#objects["ground"] = Engine.createSpaceCage(EngineModule.Vec3(600,600,600))

transformFactor = 0.7
forwardDir = EngineModule.Vec3(0,0,-1)
backwardDir = EngineModule.Vec3(0,0,1)
upDir = EngineModule.Vec3(0,1,0)
downDir = EngineModule.Vec3(0,-1,0)
leftDir = EngineModule.Vec3(-1,0,0)
rightDir = EngineModule.Vec3(1,0,0)

Engine.setCameraPosition(EngineModule.Vec3(0,100,300))

def moveCamera(direction):
	localDir = direction * transformFactor
	globalDir = Engine.getCameraOrientation() * localDir
	Engine.setCameraPosition( Engine.getCameraPosition() + globalDir)

doll = None
dolls = []
dollsPowered = False

def createMainRagdoll():
	global dolls
	doll = ragdoll.createHumanBodyParts(Engine,EngineModule,size=5)
	ragdoll.createHumanJoints(Engine,EngineModule,doll)
	ragdoll.createLimits(Engine,EngineModule,doll,45)
	ragdoll.createLimitsHuman(Engine,EngineModule,doll)
	dolls.append(doll)

def createBox():
	o = Engine.createPhysicBox()
	o.setSize(EngineModule.Vec3(10,10,10))
	o.setPosition(EngineModule.Vec3(0,150,0))
	print(o.readUuid())
	o.setUuid("021e9c23-c850-434b-90dd-7fd96aa991f0")
	print(o.readUuid())
	"""
	021e9c23-c850-434b-90dd-7fd96aa991f0
	f11f6535-d602-4fee-aed5-c8befe31ca63
	2ccbce46-54e1-4d04-b461-623d2d997abb
	"""

	"""
	b = Engine.createGuiBox()
	b.setLocalPosition(EngineModule.Vec3(10,0,0))
	b.setLocalSize(EngineModule.Vec3(10,0.5,0.5))
	b.setColour(1,0,0,0.8)
	b.setScalingFixed()
	o.addShape(b)

	b = Engine.createGuiBox()
	b.setLocalPosition(EngineModule.Vec3(0,10,0))
	b.setLocalSize(EngineModule.Vec3(0.5,10,0.5))
	b.setColour(0,1,0,0.8)
	b.setScalingFixed()
	o.addShape(b)

	b = Engine.createGuiBox()
	b.setLocalPosition(EngineModule.Vec3(0,0,10))
	b.setLocalSize(EngineModule.Vec3(0.5,0.5,10))
	b.setColour(0,0,1,0.8)
	b.setScalingFixed()
	o.addShape(b)
	"""

	return o


def init():
	pass
	#createMainRagdoll()
	if hasattr(temp,"init"):
		reload(temp)
		temp.init(Engine,EngineModule,objects)

def keyDown(key):
	if hasattr(temp,"keyDown"):
		reload(temp)
		temp.keyDown(Engine,EngineModule,objects,key)

	if (key == EngineModule.Keys.K_W or
		key == EngineModule.Keys.K_UP):
		moveCamera(forwardDir)
	if (key == EngineModule.Keys.K_S or
		key == EngineModule.Keys.K_DOWN):
		moveCamera(backwardDir)
	if (key == EngineModule.Keys.K_A or
		key == EngineModule.Keys.K_LEFT):
		moveCamera(leftDir)
	if (key == EngineModule.Keys.K_D or
		key == EngineModule.Keys.K_RIGHT):
		moveCamera(rightDir)
	if (key == EngineModule.Keys.K_Q or
		key == EngineModule.Keys.K_PGDOWN):
		moveCamera(downDir)
	if (key == EngineModule.Keys.K_E or
		key == EngineModule.Keys.K_PGUP):
		moveCamera(upDir)


def keyPressed(key):
	if hasattr(temp,"keyPressed"):
		reload(temp)
		temp.keyPressed(Engine,EngineModule,objects,key)

	if key == EngineModule.Keys.K_T:
		if hasattr(temp,"launch"):
			reload(temp)
			temp.launch(Engine,EngineModule,objects)

	if key == EngineModule.Keys.K_1:
		createBox()


	if key == EngineModule.Keys.K_5:
		a = createBox()
		b = createBox()

		j = Engine.createJoint(a,b)
		j.setAnchor1Size( EngineModule.Vec3(1,0,0) )
		j.setAnchor2Size( EngineModule.Vec3(-1,0,0) )
		j.setLimits(20,20)
		j.setAnchor1Orientation(
			EngineModule.Quat().fromAngles(0,0,45) )

		b = Engine.createGuiBox()
		b.setLocalPosition(EngineModule.Vec3(10,0,0))
		b.setLocalSize(EngineModule.Vec3(10,0.5,0.5))
		b.setColour(1,0,0,0.8)
		b.setScalingFixed()
		j.addShape(b)

		b = Engine.createGuiBox()
		b.setLocalPosition(EngineModule.Vec3(0,10,0))
		b.setLocalSize(EngineModule.Vec3(0.5,10,0.5))
		b.setColour(0,1,0,0.8)
		b.setScalingFixed()
		j.addShape(b)

		b = Engine.createGuiBox()
		b.setLocalPosition(EngineModule.Vec3(0,0,10))
		b.setLocalSize(EngineModule.Vec3(0.5,0.5,10))
		b.setColour(0,0,1,0.8)
		b.setScalingFixed()
		j.addShape(b)



	if key == EngineModule.Keys.K_2:
		char = ragdoll.createHumanBodyParts(Engine,
			EngineModule,size=5,
			pos=EngineModule.Vec3(0,150,0),
			base=False)
		ragdoll.createHumanJoints(Engine,EngineModule,char)
		ragdoll.createLimits(Engine,EngineModule,char,45)
		ragdoll.createLimitsHuman(Engine,EngineModule,char)

	if key == EngineModule.Keys.K_3:
		global dolls

		for d in dolls:
			for k in d.parts.keys():
				if k != "base":
					d.parts[k].setPosition(EngineModule.Vec3(0,250,0))

		if len(dolls) == 1:

			distance = 150

			doll = ragdoll.createHumanBodyParts(Engine,
				EngineModule,size=5,
				pos=EngineModule.Vec3(distance,5,distance),
				base=True)
			ragdoll.createHumanJoints(Engine,EngineModule,doll)
			ragdoll.createLimits(Engine,EngineModule,doll,45)
			ragdoll.createLimitsHuman(Engine,EngineModule,doll)
			dolls.append(doll)

			doll = ragdoll.createHumanBodyParts(Engine,
				EngineModule,size=5,
				pos=EngineModule.Vec3(distance,5,0),
				base=True)
			ragdoll.createHumanJoints(Engine,EngineModule,doll)
			ragdoll.createLimits(Engine,EngineModule,doll,45)
			ragdoll.createLimitsHuman(Engine,EngineModule,doll)
			dolls.append(doll)

			doll = ragdoll.createHumanBodyParts(Engine,
				EngineModule,size=5,
				pos=EngineModule.Vec3(0,5,distance),
				base=True)
			ragdoll.createHumanJoints(Engine,EngineModule,doll)
			ragdoll.createLimits(Engine,EngineModule,doll,45)
			ragdoll.createLimitsHuman(Engine,EngineModule,doll)
			dolls.append(doll)


	if key == EngineModule.Keys.K_SPACE:
		global dolls,dollsPowered
		if dollsPowered:
			dollsPowered = False
			Engine.setTimingFactor(0.55)
			for d in dolls:
				ragdoll.driveJointsOff(d)
		else:
			dollsPowered = True
			Engine.setTimingFactor(2.0)
			for d in dolls:
				ragdoll.driveJoints(d)

	if key == EngineModule.Keys.K_4:
		#o = Engine.createGuiBox()
		objects["ground"] = Engine.createSpaceCage(EngineModule.Vec3(600,600,600))

	if key == EngineModule.Keys.K_P:
		Engine.physicPauseToggle()

def keyReleased(key):
	if hasattr(temp,"keyReleased"):
		reload(temp)
		temp.keyReleased(Engine,EngineModule,objects,key)

def guiUpdate():
	pass

def physicUpdate():
	pass

