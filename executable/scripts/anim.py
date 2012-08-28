


FallingAnimTime = 500
FallingAnim = [
	{'groups':["uarm-joint","larm-joint","head-joint","hand-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))]
		},
	{'groups':["breast-joint","shoulder-joint","neck-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))]
		},
	{'groups':["hip-joint","root-joint","belly-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))]
		},
	{'groups':["foot-joint","lleg-joint","uleg-joint"],
		'time':FallingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(0,0,True))]
		}
	]

RisingAnimTime = 500
RisingSpring=(10 ** 38) * 1.4
RisingDamping=(10 ** 38) * 1
RisingAnim = [
	{'groups':["foot-joint","lleg-joint","uleg-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
		},
	{'groups':["hip-joint","root-joint","belly-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
		},
	{'groups':["breast-joint","shoulder-joint","neck-joint"],
		'time':RisingAnimTime * 0.7,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
		},
	{'groups':["uarm-joint","larm-joint","head-joint","hand-joint"],
		'time':RisingAnimTime * 0.4,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))]
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

		if not "stand" in objects.get()["anims"]:
			objects.get()["anims"]["stand"] = {
				"name":"falling","index":0,"starttime":Engine.getTime()}
		else:
			if objects.get()["anims"]["stand"]["name"] == "falling":
				objects.get()["anims"]["stand"] = {
					"name":"rising","index":0,"starttime":Engine.getTime()}
			elif objects.get()["anims"]["stand"]["name"] == "rising":
				objects.get()["anims"]["stand"] = {
					"name":"falling","index":0,"starttime":Engine.getTime()}


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

