import random

FallingAnimTime = 1000

FallingSpring = 0.1
FallingDamping = 0.5

FallingSpring = 0
FallingDamping = 0

FallingSpring = 50
FallingDamping = 100

FallingSpring = 25
FallingDamping = 50

FallingSpring = 5
FallingDamping = 50

FallingSpring = 10
FallingDamping = 3000000


FallingSpring = 10
FallingDamping = 20

FallingSpring = 1000
FallingDamping = 3000

SimpleAnimation = [
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
		'time':1500,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			#groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
			groupPart.setMotorValues(5,50,True)),
			(lambda Engine,EngineModule,objects,groupPart:
				addRandomFallingForce(Engine,EngineModule,objects)
			],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			#groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
			groupPart.setMotorValues(5,50,True))],
		},
	{'groups':[
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
		'time':50,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(1,10,True))],
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			#groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
			groupPart.setMotorValues(500,5000,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(1,10,True))],
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			#groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
			groupPart.setMotorValues(500,5000,True))],
		}
	]
"""

	{'groups':[
		"belly","root"
		],
		'time':1500,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart),
			(lambda Engine,EngineModule,objects,groupPart:
				#addRandomFallingForce(Engine,EngineModule,objects)
				groupPart)
			)
			],
			#groupPart.addForce(EngineModule.Vec3(0,-40000,0)))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart)],
			#groupPart.addForce(EngineModule.Vec3(0,-40000,0)))],
		},
	{'groups':[
		"foot-joint",
		"lleg-joint",
		"uleg-joint",
		"belly-joint",
		"breast-joint",
		"shoulder-joint",
		"neck-joint",
		"head-joint"
		#"uarm-joint",
		#"larm-joint",
		#"hand-joint"
		],
		'time':50,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		},

"""
FallingAnim = [
	{'groups':[
		"foot-joint",
		"lleg-joint",
		"uleg-joint",
		#"belly-joint"
		#"breast-joint",
		#"shoulder-joint",
		#"neck-joint",
		#"head-joint",
		#"uarm-joint",
		#"larm-joint",
		#"hand-joint"
		],
		'time':1500,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(5,FallingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(5,FallingDamping,True))],
		},
	{'groups':[
		#"uleg-joint",
		#"lleg-joint",
		#"foot-joint",
		"head-joint",
		"neck-joint",
		"breast-joint"
		],
		'time':50,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		},
	{'groups':[
		#"foot-joint",
		"lleg-joint",
		"uleg-joint",
		#"belly-joint",
		"breast-joint",
		"shoulder-joint",
		"neck-joint",
		"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
		'time':500,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		},
	{'groups':[
		"belly-joint",
		"foot-joint"
		],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
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
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(20,FallingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(20,FallingDamping,True))],
		}
	]

def addRandomFallingForce(Engine,EngineModule,objects):
	print("add random force")
	"""
	randRange = 150
	randStep = 20
	#getRandVal = lambda : random.choice([ -randRange, randRange, -randRange * 0.5, randRange * 0.5, 0])
	getRandVal = lambda : random.choice([-randRange,randRange,0])
	#getRandVal = lambda : random.uniform(-randRange,randRange),
	#getRandVal = lambda : random.randrange(-randRange,randRange,randStep))
	partsList = objects.get()["head"]
	for part in partsList:
		force = EngineModule.Vec3(getRandVal(),0,getRandVal())
		part.addForce(force)

	partsList = objects.get()["breast"]
	for part in partsList:
		force = EngineModule.Vec3(getRandVal(),0,getRandVal())
		part.addForce(force)
		"""



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
	"""
	if "head-debug" in objects.get():
		debug = objects.get()["head-debug"]
		debug.setPosition(middlePos)
	else:
	"""
	if not "head-debug" in objects.get():
		b = Engine.createGuiBox()
		b.setColour(0,0,1,0.5)
		b.setSize(EngineModule.Vec3(10,10,10))
		b.setPosition(EngineModule.Vec3(0,200,0))
		objects.get()["head-debug"] = b

	debug = objects.get()["head-debug"]
	debug.setPosition(middlePos)

	angleRand = 70
	maxMult = 39
	minMult = 5.0

	angleRand = 60
	maxMult = 90
	minMult = 30.0


	for part in partsList:
		relVec = middlePos - part.getPosition()
		relVec = EngineModule.Quat().fromAngles(
			0,random.uniform(-angleRand,angleRand),0) * relVec
		#part.addForce(relVec * 100)
		part.addForce(relVec * random.uniform(minMult,maxMult))
		#part.addForce(relVec * 0.5)

	partsList = objects.get()["breast"]
	for part in partsList:
		relVec = middlePos - part.getPosition()
		relVec = EngineModule.Quat().fromAngles(
			0,random.uniform(-angleRand,angleRand),0) * relVec
		#part.addForce(relVec * 100)
		part.addForce(relVec * random.uniform(minMult,maxMult))
		#part.addForce(relVec * 0.5)



