"""anim:
	[: select set of objects
	]: print all objects
	;: set masses of body parts
		1:set by fixed factor (0.02)
		2:double 3:half
		else:print masses
	space: toggle animation

"""

import random
random.seed()
#random.seed(12345)
random.jumpahead(random.uniform(12345,9994949))



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

FallingSpring = 5
FallingDamping = 30

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

RisingAnimTime = 200
RisingAnimTime = 150
exp=38
RisingSpring=(10 ** exp) * 1.2
RisingDamping=(10 ** exp) * 1.0

RisingStandSpring=(10 ** exp) * 1.2
RisingStandDamping=(10 ** exp) * 1.0

RisingAnim = [
	{'groups':["foot-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},
	{'groups':["lleg-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},
	{'groups':["uleg-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},

	{'groups':["belly-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},

	{'groups':["breast-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},

	{'groups':["shoulder-joint","neck-joint","head-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		}
	]

animLists={}
animLists["falling"] = FallingAnim
animLists["rising"] = RisingAnim


def runMethods(Engine,EngineModule,objects,animList,index,methodName):
	for groupName in animList[index]['groups']:
		partsList = objects.get()[groupName]
		#print("group: " + str(groupName))
		for part in partsList:
			methods = animList[index][methodName]
			for method in methods:
				method(Engine,EngineModule,objects,part)

def playAnimation(Engine,EngineModule,objects,animData):
	animName = animData["name"]
	if animName in animLists:
		startTime = animData["starttime"]
		animIndex = animData["index"]
		animList = animLists[animName]
		animListSize = len(animList)
		currentTime = Engine.getTime()
		if animIndex < animListSize:
			endTime = startTime + animList[animIndex]['time']
			if ((currentTime > startTime) and
				(currentTime < endTime)):
				if animIndex != 0:
					#print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
					runMethods(Engine,EngineModule,
						objects,animList,animIndex-1,"end")
				#print("run anim start: " + str(animName) + " index : " + str(animIndex))
				runMethods(Engine,EngineModule,
					objects,animList,animIndex,"start")
				animData["index"] = animIndex + 1
				animData["starttime"] = endTime
		elif animIndex == animListSize:
			if currentTime > startTime:
				#print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
				runMethods(Engine,EngineModule,
					objects,animList,animIndex-1,"end")
				animData["index"] = animIndex + 1
				#print("done")

def init(Engine,EngineModule,objects):
	objects.get()["anims"] = {}
	objects.setUnsavable("anims")

def guiUpdate(Engine,EngineModule,selection,objects):
	for k,v in objects.get()["anims"].items():
		playAnimation(Engine,EngineModule,objects,v)


def setMasses(Engine,EngineModule,selection,objects,factor):
	parts = ["feet","lleg","uleg","root","belly",
		"breast","shoulder","neck","uarm","larm","head","hand"]
	for p in parts:
		bodyList = objects.get()[p]
		for b in bodyList:
			b.resetMass()
			newMass = b.getMass() * factor
			b.setMass(newMass)


def keyPressed(Engine,EngineModule,key,selection,objects):
	pass

	if key == EngineModule.Keys.K_SPACE:
		if not "head" in objects.get():
			return

		fallingMass = 2.0
		risingMass = 0.0001
		if not "stand" in objects.get()["anims"]:
			setMasses(Engine,EngineModule,selection,objects,fallingMass)
			objects.get()["anims"]["stand"] = {
				"name":"falling","index":0,"starttime":Engine.getTime()}
		else:
			if objects.get()["anims"]["stand"]["name"] == "falling":


				setMasses(Engine,EngineModule,selection,objects,risingMass)
				objects.get()["anims"]["stand"] = {
					"name":"rising","index":0,"starttime":Engine.getTime()}
			elif objects.get()["anims"]["stand"]["name"] == "rising":

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
				if "head-debug" in objects.get():
					debug = objects.get()["head-debug"]
					debug.setPosition(middlePos)

				angleRand = 70
				maxMult = 9
				minMult = 1.0
				for part in partsList:
					relVec = middlePos - part.getPosition()
					relVec = EngineModule.Quat().fromAngles(
						0,random.uniform(-angleRand,angleRand),0) * relVec
					#part.addForce(relVec * 10)
					part.addForce(relVec * random.uniform(minMult,maxMult))
					#part.addForce(relVec * 0.5)

				partsList = objects.get()["breast"]
				for part in partsList:
					relVec = middlePos - part.getPosition()
					relVec = EngineModule.Quat().fromAngles(
						0,random.uniform(-angleRand,angleRand),0) * relVec
					part.addForce(relVec * random.uniform(minMult,maxMult))
					#part.addForce(relVec * 0.5)




				setMasses(Engine,EngineModule,selection,objects,fallingMass)

				partsList = objects.get()["head"]
				for part in partsList:
					part.setMass(part.getMass() * 0.3)

				partsList = objects.get()["breast"]
				for part in partsList:
					part.setMass(part.getMass() * 0.3)

				objects.get()["anims"]["stand"] = {
					"name":"falling","index":0,"starttime":Engine.getTime()}


	if key == EngineModule.Keys.K_SEMICOLON:
		parts = ["feet","lleg","uleg","root","belly",
			"breast","shoulder","neck","uarm","larm","head","hand"]
		i = len(parts)
		print("resetting body masses")
		for p in parts:
			bodyList = objects.get()[p]
			for b in bodyList:
				if Engine.isKeyDown(EngineModule.Keys.K_1):
					#newMass = i * 50 + 100
					#newMass = i * 5 + 0
					#newMass = 5
					b.resetMass()
					#newMass = b.getMass() * 0.1
					newMass = b.getMass() * 0.02
					print(str(i) + " old: " + str(b.getMass()) + " new: " + str(newMass))
					b.setMass(newMass)
				elif Engine.isKeyDown(EngineModule.Keys.K_2):
					newMass = b.getMass() * 2
					print(str(i) + " old: " + str(b.getMass()) + " new: " + str(newMass))
					b.setMass(newMass)
				elif Engine.isKeyDown(EngineModule.Keys.K_3):
					newMass = b.getMass() * 0.5
					print(str(i) + " old: " + str(b.getMass()) + " new: " + str(newMass))
					b.setMass(newMass)
				else:
					print(str(i) + "mass: " + str(b.getMass()))
			i -= 1

	if key == EngineModule.Keys.K_RBRACKET:
		pass
		#objects.append('hand-joint', [e for e in selection.get()])
		#objects.get()["hip-joint"] = [e for e in selection.get()]

		b = Engine.createGuiBox()
		b.setColour(0,0,1,0.5)
		b.setSize(EngineModule.Vec3(10,10,10))
		b.setPosition(EngineModule.Vec3(0,200,0))
		objects.get()["head-debug"] = b

		"""
		for o in objects.get()["shoulder"]:
			print(str(o))
			selection.add(o)
			"""

		"""
		if len(selection.get()) > 0:
			for o in selection.get():
				o.setPosition( o.getPosition() * EngineModule.Vec3(1,0,1))
				o.setPosition( o.getPosition() + EngineModule.Vec3(0,-0.5,0))
				print(str(o.getPosition()))
				print(str(o.getSize()))
				"""


	if key == EngineModule.Keys.K_LBRACKET:
		print(objects)

