import scripts.createobjects as create
import scripts.ragdoll as ragdoll
import scripts.saveload as saveload

import scripts.temp as temp
import scripts.navigate as navigate
import scripts.bonescale as bonescale
import scripts.select as select

objects = {}

doll = None
dolls = []
dollsPowered = False

selectContainers = []

modules = []
modules.append(select)
modules.append(navigate)
modules.append(bonescale)
modules.append(temp)

def createMainRagdoll():
	global dolls
	doll = ragdoll.createHumanBodyParts(Engine,EngineModule,size=5)
	ragdoll.createHumanJoints(Engine,EngineModule,doll)
	ragdoll.createLimits(Engine,EngineModule,doll,45)
	ragdoll.createLimitsHuman(Engine,EngineModule,doll)
	dolls.append(doll)


def init():
	for m in modules:
		if hasattr(m,"init"):
			m.init(Engine,EngineModule)

def keyDown(key):
	for m in modules:
		if hasattr(m,"keyDown"):
			reload(m)
			m.keyDown(Engine,EngineModule,key,selectContainers)


def keyPressed(key):
	for m in modules:
		if hasattr(m,"keyPressed"):
			reload(m)
			m.keyPressed(Engine,EngineModule,key,selectContainers)

	if key == EngineModule.Keys.K_R:
		if len(selectContainers) > 0:
			for o in selectContainers:
				o.setSize( o.getSize() * 1.1)


	if key == EngineModule.Keys.K_1:
		o = create.createPhysicBoxFinal(Engine,EngineModule)
		o.setPosition(EngineModule.Vec3(0,150,0))
		o.setSize(EngineModule.Vec3(10,10,10))

	if key == EngineModule.Keys.K_5:
		a = create.createPhysicBoxFinal(Engine,EngineModule)
		b = create.createPhysicBoxFinal(Engine,EngineModule)

		j = Engine.createJoint(a,b)
		j.setAnchor1Size( EngineModule.Vec3(1,0,0) )
		j.setAnchor2Size( EngineModule.Vec3(-1,0,0) )
		j.setLimits(20,20)
		j.setAnchor1Orientation(
			EngineModule.Quat().fromAngles(0,0,45) )

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

		if len(dolls) == 0:
			createMainRagdoll()
		elif len(dolls) == 1:

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
		create.createSpaceCage(Engine,EngineModule,EngineModule.Vec3(600,600,600))

	if key == EngineModule.Keys.K_P:
		Engine.physicPauseToggle()

	if key == EngineModule.Keys.K_K:
		saveload.save(Engine,EngineModule,"xmlscene/file1.xml")

	if key == EngineModule.Keys.K_L:
		saveload.load(Engine,EngineModule,"xmlscene/file1.xml")

def keyReleased(key):
	for m in modules:
		if hasattr(m,"keyReleased"):
			reload(m)
			m.keyReleased(Engine,EngineModule,key,selectContainers)

def guiUpdate():
	pass

def physicUpdate():
	pass

