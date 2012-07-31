import temp

import ragdoll

objects = {}
objects["ground"] = Engine.createSpaceCage(EngineModule.Vec3(400,400,400))

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

def init():
	pass
	createMainRagdoll()

def keyDown(key):

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
	if key == EngineModule.Keys.K_T:
		pass
		reload(temp)
		temp.launch(Engine,objects,EngineModule)

	if key == EngineModule.Keys.K_1:
		o = Engine.createPhysicBox()
		o.setSize(EngineModule.Vec3(10,10,10))
		o.setPosition(EngineModule.Vec3(0,150,0))

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

def keyReleased(key):
	pass

def guiUpdate():
	pass

def physicUpdate():
	pass
