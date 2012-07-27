import temp

#print("main.py:hello")
#print("Engine: " + str(Engine))
#print("EngineModule: " + str(EngineModule))
#print(globals())

objects = {}

objects["gui1"] = Engine.createGuiBox()
o = objects["gui1"]
#print(o)
#print(dir(o))
o.setPosition(EngineModule.Vec3(0,5,0))
#o.setOrientation(EngineModule.Quat().fromAngle(45,0,0))
o.setOrientation(EngineModule.Quat().fromAngle(0,0,45))
o.setSize(EngineModule.Vec3(20,10,20))

objects["ground"] = Engine.createSpaceCage()

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

def keyReleased(key):
	pass

def guiUpdate():
	pass

def physicUpdate():
	pass

