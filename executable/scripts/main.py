import saveload

def init(Engine,EngineModule,objects):
	#saveload.load(Engine,EngineModule,"xmlscene/file2.xml")
	saveload.load(Engine,EngineModule,"xmlscene/ragdoll_02.xml")
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isGuiShape():
			if not o.isFinalShape():
				o.hide()

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	"""
	if key == EngineModule.Keys.K_1:
		print("set all motor target on")
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)
			if o.isJoint():
				o.isJoint().setMotorOn()

	if key == EngineModule.Keys.K_2:
		print("set all motor target off")
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)
			if o.isJoint():
				o.isJoint().setMotorOff()
				"""

