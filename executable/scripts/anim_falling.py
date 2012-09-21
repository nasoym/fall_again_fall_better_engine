import random

SimpleAnimation = [
	{'groups':[
		#"foot-joint",
		#"lleg-joint",
		#"uleg-joint",
		"belly-joint",
		"breast-joint",
		"shoulder-joint",
		"neck-joint",
		#"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'time':300,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		#groupPart.setMotorOff()
		#groupPart.setMotorValues(25,50,True)
		#groupPart.setMotorValues(50,130,True)
		#groupPart.setMotorValues(5,1300,True)
		#groupPart.setMotorValues(5,1000,True)
		groupPart.setMotorValues(0,0,True)
		)],
	'start':[
		(lambda Engine,EngineModule,objects:
		[part.setMotorValues(0,0,True) for part in objects.get()["foot-joint"]]),
		(lambda Engine,EngineModule,objects:
		[part.setMotorValues(0,0,True) for part in objects.get()["lleg-joint"]]),
		(lambda Engine,EngineModule,objects:
		[part.setMotorValues(0,0,True) for part in objects.get()["uleg-joint"]]),

		(lambda Engine,EngineModule,objects:
		[part.setMotorValues(0,100,True) for part in objects.get()["head-joint"]]),

		(lambda Engine,EngineModule,objects:
		[applyForce(Engine,EngineModule,objects,part) for part in objects.get()["breast"]]),
		(lambda Engine,EngineModule,objects:
		[applyForwardForce(Engine,EngineModule,objects,part) for part in objects.get()["root"]])
		]
	},
	{'groups':[
		"foot-joint",
		"lleg-joint",
		"uleg-joint",
		"belly-joint",
		"breast-joint",
		"shoulder-joint",
		"neck-joint",
		"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'time':500,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		#groupPart.setMotorOff()
		#groupPart.setMotorValues(25,50,True)
		#groupPart.setMotorValues(50,130,True)
		#groupPart.setMotorValues(5,1300,True)
		groupPart.setMotorValues(0,250,True)
		)]
	}
	]

def applyForce(Engine,EngineModule,objects,body):
	if "head-debug" in objects.get():
		debug = objects.get()["head-debug"]
		debugPositioin = debug.getPosition()

		angleRand = 40

		relVec = debugPositioin - body.getPosition()
		relVec.normalise()
		relVec = EngineModule.Quat().fromAngles(0,random.uniform(-angleRand,angleRand),0) * relVec
		relVec = relVec * 600000.0 * random.uniform(0.1,1.0)
		relVec.y = 0
		#relVec.y = -500000
		body.addForce(relVec)

def applyForwardForce(Engine,EngineModule,objects,body):
	relVec = EngineModule.Vec3(-1,0,0)
	relVec = body.getOrientation() * relVec
	relVec.normalise()
	relVec = relVec * 60000.0
	body.addForce(relVec)

def applyDownwardForce(Engine,EngineModule,objects,body):
	relVec = EngineModule.Vec3(0,-1,0)
	relVec = body.getOrientation() * relVec
	relVec.normalise()
	relVec = relVec * 600000.0
	body.addForce(relVec)


def findMiddlePos(Engine,EngineModule,objects):

	partsList = objects.get()["head"]
	pos = partsList[0].getPosition()
	lowX = pos.x
	highX = pos.x
	lowY = pos.y
	highY = pos.y
	lowZ = pos.z
	highZ = pos.z
	for part in partsList:
		pos = part.getPosition()
		if pos.x < lowX:
			lowX = pos.x
		if pos.x > highX:
			highX = pos.x

		if pos.y < lowY:
			lowY = pos.y
		if pos.y > highY:
			highY = pos.y

		if pos.z < lowZ:
			lowZ = pos.z
		if pos.z > highZ:
			highZ = pos.z

	finalX = highX - ((highX-lowX) * 0.5)
	finalY = highY - ((highY-lowY) * 0.5)
	finalZ = highZ - ((highZ-lowZ) * 0.5)
	middlePos = EngineModule.Vec3(finalX,finalY,finalZ)
	middlePos = middlePos + EngineModule.Vec3(0,10,0)

	if not "head-debug" in objects.get():
		b = Engine.createGuiBox()
		b.setColour(0,0,1,0.5)
		b.setSize(EngineModule.Vec3(10,10,10))
		b.setPosition(EngineModule.Vec3(0,200,0))
		objects.get()["head-debug"] = b

	debug = objects.get()["head-debug"]
	debug.setPosition(middlePos)


