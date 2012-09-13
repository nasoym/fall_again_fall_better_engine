"""temp:
	,:
	.:
	/:
"""
import createobjects as create

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):
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

	if key == EngineModule.Keys.K_COMMA:
		if not Engine.getTimeDifference() == 0:
			print("fps: " + str(float(1000.0 / Engine.getTimeDifference())))
		else:
			print("fps: 0")

	if key == EngineModule.Keys.K_PERIOD:
		pass
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()
		#for o in selection.get():
		#if Engine.isKeyDown(EngineModule.Keys.K_7):
		"""
		if len(selection.get()) > 0:
			for o in selection.get():
				if o.isActor():
					print("adding Box")
					o.isActor().addCapsule(EngineModule.Vec3(20,40,20))
		else:
			Engine.test()
			"""
		#Engine.test()

		"""
		a = Engine.createArticulation()
		a.setPosition(EngineModule.Vec3(0,200,0))
		a.addCapsule(EngineModule.Vec3(50,10,10))

		b = a.addArticulation()
		b.addCapsule(EngineModule.Vec3(50,5,5))
		b.setParentAnchor(EngineModule.Vec3(50,0,0))
		b.setChildAnchor(EngineModule.Vec3(-50,0,0))
		b.setSwingLimits(40,40)
		b.setTwistLimits(0.1,0.2)

		for i in range(0,5):
			b = b.addArticulation()
			b.addCapsule(EngineModule.Vec3(50,5,5))
			b.setParentAnchor(EngineModule.Vec3(50,0,0))
			b.setChildAnchor(EngineModule.Vec3(-50,0,0))
			b.setSwingLimits(40,40)
			b.setTwistLimits(0.1,0.2)

			b = b.addArticulation()
			b.addCapsule(EngineModule.Vec3(50,10,5))
			b.setParentAnchor(EngineModule.Vec3(50,0,0))
			b.setChildAnchor(EngineModule.Vec3(-50,0,0))
			b.setSwingLimits(40,40)
			b.setTwistLimits(0.1,0.2)

		a.addToScene()
		"""

		"""
		a = create.createPhysicBoxFinal(Engine,EngineModule)
		a.setSize(EngineModule.Vec3(50,10,10))
		a.setPosition(EngineModule.Vec3(0,200,0))


		for i in range(0,10):
			b = create.createPhysicBoxFinal(Engine,EngineModule)
			b.setSize(EngineModule.Vec3(50,5,5))
			j = Engine.createJoint(a,b)
			j.setAnchor1Size( EngineModule.Vec3(1,0,0) )
			j.setAnchor2Size( EngineModule.Vec3(-1,0,0) )
			j.setLimits(40,40)
			a=b

			b = create.createPhysicBoxFinal(Engine,EngineModule)
			b.setSize(EngineModule.Vec3(50,10,10))
			j = Engine.createJoint(a,b)
			j.setAnchor1Size( EngineModule.Vec3(1,0,0) )
			j.setAnchor2Size( EngineModule.Vec3(-1,0,0) )
			j.setLimits(40,40)
			a=b
			"""


		#b.setTwistLimitDisabled()
		#b.setSwingLimitDisabled()

			
		#Engine.callPythonKeyPressed(EngineModule.Keys.K_SPACE)
		"""
		a = Engine.createStaticActor()
		s = a.addCapsule(EngineModule.Vec3(60,20,20))
		a.setPosition(EngineModule.Vec3(0,100,0))
		"""

		a = Engine.createDynamicActor()
		s = a.addCapsule(EngineModule.Vec3(60,20,20))
		s = a.addBox(EngineModule.Vec3(60,20,20))
		s.setLocalPosition(EngineModule.Vec3(0,10,0))

		#s = a.addBox(EngineModule.Vec3(60,20,20))
		#s = a.addSphere(EngineModule.Vec3(60,20,20))
		#s.setLocalSize(EngineModule.Vec3(40,10,10))
		#s.setLocalOrientation(EngineModule.Quat().fromAngles(0,45,0))
		#s.setLocalPosition(EngineModule.Vec3(0,10,0))

		"""
		b = Engine.createDynamicActor()
		s = b.addCapsule(EngineModule.Vec3(60,20,20))

		j = Engine.createJoint(a,b)
		j.setAnchor1Size( EngineModule.Vec3(1,0,0) )
		j.setAnchor2Size( EngineModule.Vec3(-1,0,0) )
		j.setLimits(40,40)
		"""

	if key == EngineModule.Keys.K_SLASH:

		print("set Solver Iterations")
		#for o in selection.get():
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)
			"""
			if o.isBody():
				b = o.isBody()
				b.dsetSolverIterations(4,1)
				#b.dsetSolverIterations(4,4)
				#b.dsetSolverIterations(32,8)
				#b.dsetSolverIterations(4,8)
				#b.dsetSolverIterations(16,1)
				"""
			if o.isGuiShape():
				o.setMaterialName("SSAO/GBuffer")
				#o.setMaterialName("Body")



