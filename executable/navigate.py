transformFactor = 0.7

forwardDir=None
backwardDir=None
upDir=None
downDir=None
leftDir=None
rightDir=None

#global forwardDir,backwardDir,upDir,downDir,leftDir,rightDir

def moveCamera(Engine,EngineModule,direction):
	global forwardDir,backwardDir,upDir,downDir,leftDir,rightDir

	localDir = direction * transformFactor
	globalDir = Engine.getCameraOrientation() * localDir
	Engine.setCameraPosition( Engine.getCameraPosition() + globalDir)

def init(Engine,EngineModule,objects):
	global forwardDir,backwardDir,upDir,downDir,leftDir,rightDir
	forwardDir = EngineModule.Vec3(0,0,-1)
	backwardDir = EngineModule.Vec3(0,0,1)
	upDir = EngineModule.Vec3(0,1,0)
	downDir = EngineModule.Vec3(0,-1,0)
	leftDir = EngineModule.Vec3(-1,0,0)
	rightDir = EngineModule.Vec3(1,0,0)
	Engine.setCameraPosition(EngineModule.Vec3(0,100,300))

def keyDown(Engine,EngineModule,objects,key):
	pass
	if (key == EngineModule.Keys.K_W or
		key == EngineModule.Keys.K_UP):
		moveCamera(Engine,EngineModule,forwardDir)
	if (key == EngineModule.Keys.K_S or
		key == EngineModule.Keys.K_DOWN):
		moveCamera(Engine,EngineModule,backwardDir)
	if (key == EngineModule.Keys.K_A or
		key == EngineModule.Keys.K_LEFT):
		moveCamera(Engine,EngineModule,leftDir)
	if (key == EngineModule.Keys.K_D or
		key == EngineModule.Keys.K_RIGHT):
		moveCamera(Engine,EngineModule,rightDir)
	if (key == EngineModule.Keys.K_Q or
		key == EngineModule.Keys.K_PGDOWN):
		moveCamera(Engine,EngineModule,downDir)
	if (key == EngineModule.Keys.K_E or
		key == EngineModule.Keys.K_PGUP):
		moveCamera(Engine,EngineModule,upDir)

def keyPressed(Engine,EngineModule,objects,key):
	pass

def keyReleased(Engine,EngineModule,objects,key):
	pass


