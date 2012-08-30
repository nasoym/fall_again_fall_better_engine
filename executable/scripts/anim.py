"""
anim:

"""

import random


FallingAnimTime = 450

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

FallingSpring = 0
FallingDamping = 30

FallingAnim = [
	{'groups':[
		"lleg-joint",
		"uleg-joint",
		"hip-joint",
		"root-joint",
		"belly-joint",
		"breast-joint",
		"shoulder-joint",
		"neck-joint",
		"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(FallingSpring,FallingDamping,True))],
		},
	{'groups':["foot-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))],
		}
	]

RisingAnimTime = 200
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

	{'groups':["hip-joint","root-joint"],
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

	{'groups':["shoulder-joint","neck-joint","head-joint","uarm-joint","larm-joint","hand-joint"],
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
	Engine.setTimingFactor(5.0)

def guiUpdate(Engine,EngineModule,selection,objects):
	for k,v in objects.get()["anims"].items():
		playAnimation(Engine,EngineModule,objects,v)



def setMasses(Engine,EngineModule,selection,objects,factor):
	parts = ["feet","lleg","uleg","hip","root","belly",
		"breast","shoulder","neck","uarm","larm","head","hand"]
	for p in parts:
		bodyList = objects.get()[p]
		for b in bodyList:
			b.resetMass()
			newMass = b.getMass() * factor
			b.setMass(newMass)
"""
RANDOM MODULE:
import random
random.random() = 0.0 -> 1.0
random.uniform(0.5,20.4)
random.randint(44,8994)
random.randrange(0,5,2) = 0,2,4
random.choice([1,4,5,645])
"""

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	"""
	if key == EngineModule.Keys.K_COMMA:
	if key == EngineModule.Keys.K_PERIOD:
	if key == EngineModule.Keys.K_SLASH:

	if key == EngineModule.Keys.K_SEMICOLON:
	if key == EngineModule.Keys.K_APOSTROPHE:
	if key == EngineModule.Keys.K_BACKSLASH:

	if key == EngineModule.Keys.K_LBRACKET:
	if key == EngineModule.Keys.K_RBRACKET:

	if key == EngineModule.Keys.K_MINUS:
	if key == EngineModule.Keys.K_EQUALS:
	"""

	if key == EngineModule.Keys.K_SPACE:

		fallingMass = 1.0
		risingMass = 0.01
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


				randRange = 100
				force = EngineModule.Vec3(
					random.uniform(-randRange,randRange),
					0,
					random.uniform(-randRange,randRange))
				for o in selection.get():
					if o.isBody():
						o.isBody().addForce(force)
				partsList = objects.get()["head"]
				for part in partsList:
					part.addForce(force)

				force = EngineModule.Vec3(
					random.uniform(-randRange,randRange),
					0,
					random.uniform(-randRange,randRange))
				for o in selection.get():
					if o.isBody():
						o.isBody().addForce(force)
				partsList = objects.get()["breast"]
				for part in partsList:
					part.addForce(force)


				setMasses(Engine,EngineModule,selection,objects,fallingMass)
				objects.get()["anims"]["stand"] = {
					"name":"falling","index":0,"starttime":Engine.getTime()}


	"""
	if key == EngineModule.Keys.K_SEMICOLON:
		parts = ["feet","lleg","uleg","hip","root","belly",
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

		selection.clear()
		for o in objects.get()["belly-joint"]:
			selection.add(o)

	if key == EngineModule.Keys.K_LBRACKET:
		print(objects)

	if key == EngineModule.Keys.K_M:
        #void        dsetContactDistance(float);
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)

			if o.isJoint():
				j = o.isJoint()

				if Engine.isKeyDown(EngineModule.Keys.K_1):
					j.setMotorOn()

				if Engine.isKeyDown(EngineModule.Keys.K_2):
					j.setMotorOff()

				if Engine.isKeyDown(EngineModule.Keys.K_3):
					exp = 38
					spring = (10 ** exp) * 1.4
					damping = (10 ** exp) * 1
					#spring = (10 ** 10) * 1
					#damping = (10 ** 8) * 1

					j.dsetMotorSpring(spring)
					j.dsetMotorDamping(damping)
					j.dsetMotorAccel(True)
				if Engine.isKeyDown(EngineModule.Keys.K_4):
					spring = (10 ** 1) * 1
					damping = (10 ** 1) * 4
					spring = 2
					damping = 5
					j.dsetMotorSpring(spring)
					j.dsetMotorDamping(damping)
					j.dsetMotorAccel(True)

				if Engine.isKeyDown(EngineModule.Keys.K_5):
					spring = (10 ** 15) * 1
					damping = (10 ** 14) * 1
					damping = (10 ** 13) * 1
					j.dsetMotorSpring(spring)
					j.dsetMotorDamping(damping)
					j.dsetMotorAccel(False)
		"""
