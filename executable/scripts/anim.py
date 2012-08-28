

AnimStateIdle = 0
AnimStateFalling = 1
AnimStateRising = 2

def init(Engine,EngineModule,objects):
	pass
	objects.get()["animstate"] = AnimStateIdle
	objects.get()["animtime"] = 0

def guiUpdate(Engine,EngineModule,selection,objects):
	pass

	animstate = objects.get()["animstate"]
	currentTime = Engine.getTime()
	startTime = objects.get()["animtime"]
	elapsedTime = currentTime - startTime

	if animstate == AnimStateIdle:
		pass
	
	elif animstate == AnimStateFalling:
		print(str(elapsedTime))
		pass

	elif animstate == AnimStateRising:
		pass

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
		print("animstate: " + str(animstate))
		print("time: " + str(Engine.getTime()))
		objects.get()["animtime"] = Engine.getTime()

		if animstate == AnimStateIdle:
			objects.get()["animstate"] = AnimStateFalling
		
		elif animstate == AnimStateFalling:
			objects.get()["animstate"] = AnimStateRising

		elif animstate == AnimStateRising:
			objects.get()["animstate"] = AnimStateFalling


	if key == EngineModule.Keys.K_SEMICOLON:
		parts = ["feet","lleg","uleg","hip","root","belly",
			"breast","shoulder","neck","uarm","larm","head","hand"]
		#i = 1
		i = len(parts)
		for p in parts:
			bodyList = objects.get()[p]
			#print(str(p) + " : " + str(bodyList))

			for b in bodyList:
				#newMass = i * 50 + 100
				newMass = i * 5 + 0
				newMass = 5
				newMass = b.getMass() * 0.1
				print(str(i) + " - " + str(b.getMass()) + " : " + str(newMass))
				b.setMass(newMass)
				
			i -= 1

	if key == EngineModule.Keys.K_RETURN:
		objects.append('base', [e for e in selection.get()])

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

