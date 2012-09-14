"""temp:
	,:
	.:
	/:
"""
import createobjects as create
import helpers
import datetime

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass

def calcMasses(Engine,EngineModule,bodies,factor):
		for i in range(0,len(bodies)):
			bodyName = bodies[i]
			body = helpers.getBodyFromName(Engine,EngineModule,bodyName)
			bodyMass = body.getMass()
			if i > 0:
				otherBodyName = bodies[i-1]
				otherBody = helpers.getBodyFromName(Engine,EngineModule,otherBodyName)
				otherBodyMass = otherBody.getMass()
				body.setMass( otherBodyMass * factor);

def readMasses(Engine,EngineModule,bodies):
		for i in range(0,len(bodies)):
			bodyName = bodies[i]
			body = helpers.getBodyFromName(Engine,EngineModule,bodyName)
			bodyMass = body.getMass()
			if i > 0:
				otherBodyName = bodies[i-1]
				otherBody = helpers.getBodyFromName(Engine,EngineModule,otherBodyName)
				otherBodyMass = otherBody.getMass()
				#factor = otherBodyMass / bodyMass
				factor = bodyMass / otherBodyMass

				print(bodyName + " : " + str(bodyMass) + " * " + str(factor))
			else:
				print(bodyName + " : " + str(bodyMass))


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
		"""
		if not Engine.getTimeDifference() == 0:
			print("fps: " + str(float(1000.0 / Engine.getTimeDifference())))
		else:
			print("fps: 0")
			"""

		"""
		parts = ["feet","lleg","uleg","root","belly",
			"breast","shoulder","neck","uarm","larm","head","hand"]

		parts = ["feet","lleg","uleg","root","belly",
			"breast","neck","head"]
		group = {}
		for p in parts:
			bodyList = objects.get()[p]
			for b in bodyList:
				group[p] = b
				print(str(p) + " - " + str(b))
				break
		print(str(group))
		for p in parts:
			b = group[p]
			print(str(p) + " - " + str(b))
			print(b.getMass())

		print("now the group ------------")
		for i in range(0,len(parts)):
			b = group[parts[i]]
			print(str(p) + " - " + str(b))
			print(b.getMass())
			print(b.getName())
			if i > 0:
				otherMass = group[parts[i-1]].getMass()
				factor = b.getMass() / otherMass
				print("factor: " + str(factor))
				helpers.storeOperation(str(parts[i]) + " : " + str(b.getName()))
				"""


		#bodies = ["Bone.012", "Bone.010", "Bone", "Bone.002", "Bone.003", "Bone.007", "Bone.008"]
		helpers.storeOperation(str(datetime.datetime.now()))
		bodies = ["toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head"]
		calcMasses(Engine,EngineModule,bodies,0.7)

		bodies = ["toes-r", "foot-r", "lleg-r", "uleg-r", "root", "belly", "cheast", "breast", "neck", "head"]
		calcMasses(Engine,EngineModule,bodies,0.7)

		parts = ["feet","lleg","uleg","root","belly",
			"breast","shoulder","neck","uarm","larm","head","hand"]
		for p in parts:
			bodyList = objects.get()[p]
			for b in bodyList:
				newMass = b.getMass() * 0.01
				b.setMass(newMass)



		"""
		print("---------mass relationships----------------")
		helpers.storeOperation("---------mass relationships----------------")
		for i in range(0,len(bodies)):
			bodyName = bodies[i]
			print(bodyName)
			body = helpers.getBodyFromName(Engine,EngineModule,bodyName)
			#body.resetMass()
			bodyMass = body.getMass()
			if i > 0:
				otherBodyName = bodies[i-1]
				otherBody = helpers.getBodyFromName(Engine,EngineModule,otherBodyName)
				otherBodyMass = otherBody.getMass()

				factor = bodyMass / otherBodyMass
				helpers.storeOperation(bodyName + " : " + str(bodyMass) + " * " + str(factor))
				body.setMass( otherBodyMass * 1.5);
			else:
				helpers.storeOperation(bodyName + " : " + str(bodyMass))
				"""


	if key == EngineModule.Keys.K_PERIOD:
		pass
		helpers.storeOperation(str(datetime.datetime.now()))
		bodies = ["toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head"]
		readMasses(Engine,EngineModule,bodies)
		"""
		print(type(EngineModule.Vec3()))
		print(type(EngineModule.Quat()))

		v = EngineModule.Vec3()
		q = EngineModule.Quat()

		if type(v) == EngineModule.Vec3:
			print("is Vector")
		if type(q) == EngineModule.Quat:
			print("is Quat")

		if type(q) == EngineModule.Vec3:
			print("is Vector ?")
		if type(v) == EngineModule.Quat:
			print("is Quat ?")
			"""

		

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

		a = Engine.createDynamicActor()
		s = a.addCapsule(EngineModule.Vec3(60,20,20))
		s = a.addBox(EngineModule.Vec3(60,20,20))
		s.setLocalPosition(EngineModule.Vec3(0,10,0))
		"""

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
		parts = ["feet","lleg","uleg","root","belly",
			"breast","shoulder","neck","uarm","larm","head","hand"]
		for p in parts:
			bodyList = objects.get()[p]
			for b in bodyList:
				b.resetMass()

		"""
		print("set Solver Iterations")
		#for o in selection.get():
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)
			#if o.isBody():
			if False:
				b = o.isBody()
				b.dsetSolverIterations(4,1)
				#b.dsetSolverIterations(4,4)
				#b.dsetSolverIterations(32,8)
				#b.dsetSolverIterations(4,8)
				#b.dsetSolverIterations(16,1)
			if o.isGuiShape():
				o.setMaterialName("SSAO/GBuffer")
				#o.setMaterialName("Body")
				"""



