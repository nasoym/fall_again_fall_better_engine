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
import animation_helper
import helpers

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

def init(Engine,EngineModule,objects):
	objects.get()["anims"] = {}
	objects.setUnsavable("anims")

def guiUpdate(Engine,EngineModule,selection,objects):
	for k,v in objects.get()["anims"].items():
		animName = v["name"]
		if animName in animLists:
			animList = animLists[animName]
			animation_helper.playAnimation(Engine,EngineModule,objects,v,animList)

def keyPressed(Engine,EngineModule,key,selection,objects):
	allbodies = ["toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head","shoulder-l","uarm-l","larm-l","hand-l", "thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]

	if key == EngineModule.Keys.K_SPACE:
		if not "head" in objects.get():
			return

		fallingMass = 1.5

		if not "stand" in objects.get()["anims"]:
			print("toggle animation: to falling")
			objects.get()["anims"]["stand"] = {
				"name":"falling","index":0,"starttime":Engine.getTime()}
			setMasses(Engine,EngineModule,selection,objects,fallingMass)
		else:
			if objects.get()["anims"]["stand"]["name"] == "falling":
				print("toggle animation: to rising")
				objects.get()["anims"]["stand"] = {
					"name":"rising","index":0,"starttime":Engine.getTime()}

				#setMasses(Engine,EngineModule,selection,objects,0.01)

				"""
				setMassesList(Engine,EngineModule,selection,
					objects,10,["feet","lleg"])
				setMassesList(Engine,EngineModule,selection,
					objects,20,["uleg"])

				setMassesList(Engine,EngineModule,selection,
					objects,0.02,["root","belly","breast"])

				setMassesList(Engine,EngineModule,selection,
					objects,0.1,["uarm","larm","hand","shoulder","neck"])

				setMassesList(Engine,EngineModule,selection,
					objects,0.01,["head"])

				bodies = ["toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head","shoulder-l","uarm-l","larm-l","hand-l", "thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]
				calcMasses(Engine,EngineModule,bodies,0.2)

				bodies = ["toes-r", "foot-r", "lleg-r", "uleg-r", "root", "belly", "cheast", "breast", "neck", "head","shoulder-r","uarm-r","larm-r","hand-r", "thumb-high-r", "finger-index-high-r", "finger-middle-high-r", "finger-ring-high-r", "finger-little-high-r"]
				calcMasses(Engine,EngineModule,bodies,0.2)
					"""


				parts = ["feet","lleg","uleg","root","belly",
					"breast","shoulder","neck","uarm","larm","head","hand"]
				for p in parts:
					bodyList = objects.get()[p]
					for b in bodyList:
						newMass = b.getMass() * 0.5
						b.setMass(newMass)

				bodies = ["toes-l", "foot-l", "lleg-l", "uleg-l"]
				calcMasses(Engine,EngineModule,bodies,0.2)

				bodies = ["toes-r", "foot-r", "lleg-r", "uleg-r"]
				calcMasses(Engine,EngineModule,bodies,0.2)

				bodies = ["uleg-l", "root", "belly", "cheast", "breast", "neck", "head","shoulder-l","uarm-l","larm-l","hand-l", "thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]
				calcMasses(Engine,EngineModule,bodies,0.5)

				bodies = ["uleg-r", "root", "belly", "cheast", "breast", "neck", "head","shoulder-r","uarm-r","larm-r","hand-r", "thumb-high-r", "finger-index-high-r", "finger-middle-high-r", "finger-ring-high-r", "finger-little-high-r"]
				calcMasses(Engine,EngineModule,bodies,0.5)

			elif objects.get()["anims"]["stand"]["name"] == "rising":
				print("toggle animation: to falling")

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
					"""




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



def setMasses(Engine,EngineModule,selection,objects,factor):
	parts = ["feet","lleg","uleg","root","belly",
		"breast","shoulder","neck","uarm","larm","head","hand"]
	for p in parts:
		bodyList = objects.get()[p]
		for b in bodyList:
			b.resetMass()
			newMass = b.getMass() * factor
			b.setMass(newMass)

def setMassesList(Engine,EngineModule,selection,objects,parts,factor):
	for p in parts:
		if p in objects.get():
			bodyList = objects.get()[p]
			if bodyList:
				for b in bodyList:
					if b:
						b.setMass(b.getMass() * factor)

def calcMasses(Engine,EngineModule,bodies,factor):
	for i in range(0,len(bodies)):
		bodyName = bodies[i]
		body = helpers.getBodyFromName(Engine,EngineModule,bodyName)
		if body:
			bodyMass = body.getMass()
			if i > 0:
				otherBodyName = bodies[i-1]
				otherBody = helpers.getBodyFromName(Engine,EngineModule,otherBodyName)
				otherBodyMass = otherBody.getMass()
				body.setMass( otherBodyMass * factor);

