


FallingAnimTime = 1000
FallingAnim = [
	{'groups':["foot-joint","lleg-joint","uleg-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))]
		},
	{'groups':["hip-joint","root-joint","belly-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))]
		},
	{'groups':["breast-joint","shoulder-joint","neck-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))]
		},
	{'groups':["uarm-joint","larm-joint","head-joint","hand-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(0,0,True))]
		}
	]

RisingAnimTime = 500
RisingSpring=(10 ** 38) * 1.4
RisingDamping=(10 ** 38) * 1
RisingAnim = [
	{'groups':["foot-joint","lleg-joint","uleg-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
		},
	{'groups':["hip-joint","root-joint","belly-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
		},
	{'groups':["breast-joint","shoulder-joint","neck-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
		},
	{'groups':["uarm-joint","larm-joint","head-joint","hand-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
		}
	]

animLists={}
animLists["falling"] = FallingAnim
animLists["rising"] = RisingAnim

AnimStateIdle = 0
AnimStateFalling = 1
AnimStateRising = 2

def init(Engine,EngineModule,objects):
	objects.get()["animstate"] = AnimStateIdle
	objects.get()["animtime"] = 0
	objects.get()["animindex"] = 0
	objects.get()["animname"] = ""

def guiUpdate(Engine,EngineModule,selection,objects):
	if type(objects.get()["animstate"]) == list:
		objects.get()["animstate"] = AnimStateIdle
	if type(objects.get()["animtime"]) == list:
		objects.get()["animtime"] = 0
	if type(objects.get()["animindex"]) == list:
		objects.get()["animindex"] = 0
	if type(objects.get()["animname"]) == list:
		objects.get()["animname"] = ""

	animName = objects.get()["animname"]

	if animName in animLists:
		startTime = objects.get()["animtime"]
		animIndex = objects.get()["animindex"]
		
		animList = animLists[animName]
		animListSize = len(animList)
		currentTime = Engine.getTime()

		if animIndex < animListSize:
			endTime = startTime + animList[animIndex]['time']
			if ((currentTime > startTime) and
				(currentTime < endTime)):
				if animIndex != 0:
					print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
					for groupName in animList[animIndex-1]['groups']:
						partsList = objects.get()[groupName]
						print("group: " + str(groupName))
						for part in partsList:
							methods = animList[animIndex-1]['end']
							for method in methods:
								method(Engine,EngineModule,objects,part)
					pass

				print("run anim start: " + str(animName) + " index : " + str(animIndex))
				for groupName in animList[animIndex]['groups']:
					partsList = objects.get()[groupName]
					print("group: " + str(groupName))
					for part in partsList:
						methods = animList[animIndex]['start']
						for method in methods:
							method(Engine,EngineModule,objects,part)

				objects.get()["animindex"] = animIndex + 1
				objects.get()["animtime"] = endTime
		elif animIndex == animListSize:
			if currentTime > startTime:
				print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
				for groupName in animList[animIndex-1]['groups']:
					partsList = objects.get()[groupName]
					print("group: " + str(groupName))
					for part in partsList:
						methods = animList[animIndex-1]['end']
						for method in methods:
							method(Engine,EngineModule,objects,part)
				objects.get()["animindex"] = animIndex + 1
				print("done")


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


	if key == EngineModule.Keys.K_APOSTROPHE:

		animstate = objects.get()["animstate"]
		if animstate == AnimStateIdle:
			objects.get()["animstate"] = AnimStateFalling
			objects.get()["animindex"] = 0
			objects.get()["animtime"] = Engine.getTime()
			objects.get()["animname"] = "falling"
		
		elif animstate == AnimStateFalling:
			objects.get()["animstate"] = AnimStateRising
			objects.get()["animindex"] = 0
			objects.get()["animtime"] = Engine.getTime()
			objects.get()["animname"] = "rising"

		elif animstate == AnimStateRising:
			objects.get()["animstate"] = AnimStateFalling
			objects.get()["animindex"] = 0
			objects.get()["animtime"] = Engine.getTime()
			objects.get()["animname"] = "falling"


	if key == EngineModule.Keys.K_SEMICOLON:
		parts = ["feet","lleg","uleg","hip","root","belly",
			"breast","shoulder","neck","uarm","larm","head","hand"]
		i = len(parts)
		print("resetting body masses")
		for p in parts:
			bodyList = objects.get()[p]
			for b in bodyList:
				#newMass = i * 50 + 100
				#newMass = i * 5 + 0
				#newMass = 5
				b.resetMass()
				newMass = b.getMass() * 0.1
				print(str(i) + " old: " + str(b.getMass()) + " new: " + str(newMass))
				b.setMass(newMass)
			i -= 1

	if key == EngineModule.Keys.K_RETURN:
		pass
		#objects.append('hand-joint', [e for e in selection.get()])
		#objects.get()["belly-joint"] = [e for e in selection.get()]

	if key == EngineModule.Keys.K_SPACE:
		print(objects)

	if key == EngineModule.Keys.K_M:
		"""
        void        dsetMotorSpring(float);
        void        dsetMotorDamping(float);
        void        dsetMotorAccel(bool);
        void        dsetContactDistance(float);
		"""
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

