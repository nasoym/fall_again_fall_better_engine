import temp
import ragdoll
import saveload
import navigate
#import mesh

objects = {}
#objects["ground"] = Engine.createSpaceCage(EngineModule.Vec3(400,400,400))
#objects["ground"] = Engine.createSpaceCage(EngineModule.Vec3(600,600,600))

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
	if hasattr(temp,"init"):
		reload(temp)
		temp.init(Engine,EngineModule,objects)

	if hasattr(navigate,"init"):
		navigate.init(Engine,EngineModule,objects)

def keyDown(key):
	if hasattr(temp,"keyDown"):
		reload(temp)
		temp.keyDown(Engine,EngineModule,objects,key)

	if hasattr(navigate,"keyDown"):
		navigate.keyDown(Engine,EngineModule,objects,key)

def keyPressed(key):
	if hasattr(temp,"keyPressed"):
		reload(temp)
		temp.keyPressed(Engine,EngineModule,objects,key)

	if key == EngineModule.Keys.K_1:
		createobjects.createBox()

	if key == EngineModule.Keys.K_5:
		a = createobjects.createBox()
		b = createobjects.createBox()

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
		#o = Engine.createGuiBox()
		objects["ground"] = Engine.createSpaceCage(EngineModule.Vec3(600,600,600))

	if key == EngineModule.Keys.K_P:
		Engine.physicPauseToggle()

	if key == EngineModule.Keys.K_S:
		saveload.save(Engine,EngineModule,"xmlscene/file1.xml")

	if key == EngineModule.Keys.K_L:
		saveload.load(Engine,EngineModule,"xmlscene/file1.xml")

def keyReleased(key):
	if hasattr(temp,"keyReleased"):
		reload(temp)
		temp.keyReleased(Engine,EngineModule,objects,key)

def guiUpdate():
	pass

def physicUpdate():
	pass

