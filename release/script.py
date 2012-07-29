import temp
import ragdoll
#print("main.py:hello")
#print("Engine: " + str(Engine))
#print("EngineModule: " + str(EngineModule))
#print(globals())

objects = {}

"""
objects["gui1"] = Engine.createGuiBox()
o = objects["gui1"]
o.setPosition(EngineModule.Vec3(0,5,0))
#o.setOrientation(EngineModule.Quat().fromAngle(45,0,0))
o.setOrientation(EngineModule.Quat().fromAngle(0,0,45))
o.setSize(EngineModule.Vec3(20,10,20))
"""

objects["ground"] = Engine.createSpaceCage()
o = objects["ground"]
#o.setPosition(EngineModule.Vec3(0,-0.5,0))
#o.setSize(EngineModule.Vec3(200,1,200))

"""
objects["body1"] = Engine.createPhysicBox()
objects["body2"] = Engine.createPhysicBox()
o1 = objects["body1"]
o2 = objects["body2"]
objects["joint1"] = Engine.createJoint(o1,o2)
j = objects["joint1"]
j.setAnchor1Size(EngineModule.Vec3(-1,0,0))
j.setAnchor2Size(EngineModule.Vec3(1,0,0))
#o.setPosition(EngineModule.Vec3(0,150,0))
"""

class Ragdoll(object):
    def __init__(self):
        self.parts = {}
        self.joints = {}

doll = Ragdoll()
ragdoll.createHumanBodyParts(Engine,EngineModule,doll,size=5)
ragdoll.createHumanJoints(Engine,EngineModule,doll)
ragdoll.createLimits(Engine,EngineModule,doll,45)
ragdoll.createLimitsHuman(Engine,EngineModule,doll)

transformFactor = 0.5
forwardDir = EngineModule.Vec3(0,0,-1)
backwardDir = EngineModule.Vec3(0,0,1)
upDir = EngineModule.Vec3(0,1,0)
downDir = EngineModule.Vec3(0,-1,0)
leftDir = EngineModule.Vec3(-1,0,0)
rightDir = EngineModule.Vec3(1,0,0)

def moveCamera(direction):
	localDir = direction * transformFactor
	globalDir = Engine.getCameraOrientation() * localDir
	Engine.setCameraPosition( Engine.getCameraPosition() + globalDir)


def guiTest():
	o = Engine.createPhysicBox()
	o.setSize(EngineModule.Vec3(10,10,10))
	o.setPosition(EngineModule.Vec3(0,30,0))

	o = Engine.createPhysicBox()
	o.setSize(EngineModule.Vec3(10,10,10))
	o.setPosition(EngineModule.Vec3(0,35,-20))

	o = Engine.createPhysicBox()
	o.setSize(EngineModule.Vec3(10,10,10))
	o.setPosition(EngineModule.Vec3(0,35,20))

def createArm():
	o1 = Engine.createPhysicBox()
	#o2 = Engine.createPhysicBox()
	o3 = Engine.createPhysicBox()

	o1.setSize(EngineModule.Vec3(20,1,1))
	#o2.setSize(EngineModule.Vec3(10,1,1))
	o3.setSize(EngineModule.Vec3(30,5,5))

	j = Engine.createJoint(o3,o1)
	j.setAnchor1Size(EngineModule.Vec3(1,0,0))
	#j.setAnchor1(EngineModule.Vec3(30,0,0))
	j.setAnchor2Size(EngineModule.Vec3(-1,0,0))
	#j.setAnchor2(EngineModule.Vec3(-20,0,0))
	j.setLimits(5,5)

#	j = Engine.createJoint(o3,o2)
#	j.setAnchor1Size(EngineModule.Vec3(0,0,-1))
#	j.setAnchor2Size(EngineModule.Vec3(-1,0,0))
#	j.setLimits(5,5)
#	print(j.getAnchor1().toTuple())
#	print(j.getAnchor2().toTuple())




def init():
	pass

def keyDown(key):
	if key == EngineModule.Keys.K_T:
		reload(temp)
		temp.launch(Engine,objects,EngineModule)

	if key == EngineModule.Keys.K_W:
		moveCamera(forwardDir)
	if key == EngineModule.Keys.K_S:
		moveCamera(backwardDir)
	if key == EngineModule.Keys.K_A:
		moveCamera(leftDir)
	if key == EngineModule.Keys.K_D:
		moveCamera(rightDir)
	if key == EngineModule.Keys.K_Q:
		moveCamera(downDir)
	if key == EngineModule.Keys.K_E:
		moveCamera(upDir)


def keyPressed(key):
	if key == EngineModule.Keys.K_Q:
		#Engine.quit()
		pass
	if key == EngineModule.Keys.K_R:
		doll = Ragdoll()
		ragdoll.createHumanBodyParts(Engine,EngineModule,doll,size=5)
		ragdoll.createHumanJoints(Engine,EngineModule,doll)
		ragdoll.createLimits(Engine,EngineModule,doll,15)
		ragdoll.createLimitsHuman(Engine,EngineModule,doll)

	if key == EngineModule.Keys.K_Y:
		global doll
		ragdoll.driveJoints(doll)
	if key == EngineModule.Keys.K_U:
		global doll
		ragdoll.driveJointsOff(doll)


	if key == EngineModule.Keys.K_1:
		createArm()

	if key == EngineModule.Keys.K_2:
		guiTest()

	if key == EngineModule.Keys.K_3:
		o = Engine.createPhysicStatic()
		o.setSize(EngineModule.Vec3(10,10,10))
		o.setPosition(EngineModule.Vec3(0,30,0))


def keyReleased(key):
	pass

def guiUpdate():
	pass

def physicUpdate():
	pass

