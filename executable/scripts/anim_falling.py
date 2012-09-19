import random

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
		'end':[],'time':1500,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			#groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
			groupPart.setMotorValues(5,50,True))]
		},
	{'groups':[
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
		'end':[],'time':50,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			#groupPart.setMotorValues(1,10,True))],
			#groupPart.setMotorValues(0,0,True))],
			#groupPart.setMotorOff())],
			#groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
			groupPart.setMotorValues(500,5000,True))]
		}
	]

def addRandomFallingForce(Engine,EngineModule,objects):
	print("add random force")

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
	middlePos = middlePos + EngineModule.Vec3(100,0,0)
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

	angleRand = 60
	maxMult = 800
	minMult = 200

	"""
	partsList = objects.get()["root"]
	for part in partsList:
		part.addForce(EngineModule.Vec3(0,-3000,0))

	partsList = objects.get()["belly"]
	for part in partsList:
		part.addForce(EngineModule.Vec3(0,-3000,0))
		"""

	partsList = objects.get()["head"]
	for part in partsList:
		relVec = middlePos - part.getPosition()
		relVec = EngineModule.Quat().fromAngles(
			0,random.uniform(-angleRand,angleRand),0) * relVec
		force = relVec * random.uniform(minMult,maxMult)
		#print("add force to head: " + str(force))
		#part.addForce(relVec * 100)
		part.addForce(force)
		#part.addForce(relVec * 0.5)

	"""
	partsList = objects.get()["breast"]
	for part in partsList:
		relVec = middlePos - part.getPosition()
		relVec = EngineModule.Quat().fromAngles(
			0,random.uniform(-angleRand,angleRand),0) * relVec
		force = relVec * random.uniform(minMult,maxMult)
		print("add force to breast: " + str(force))
		#part.addForce(relVec * 100)
		part.addForce(force)
		#part.addForce(relVec * 0.5)
		"""



