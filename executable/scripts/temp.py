"""temp:
	t: run temp
		1:load
		2:save
	o: move object by step size 20 
		(x+:1, y+:2, z+:3, x-:4, y-:5, z-:6) 
		7: y*0.9
		8: step size=1
	x: work on body,joint: sizepos with all joints
	b: work on body,joint: singual anchor pos 
	n: set timingfactor 1:*0.9 2:*1.1
"""
import mesh
import createobjects as create
import saveload
import bodyjoint

def keyDown(Engine,EngineModule,key,selection,objects):
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
		if len(selection.get()) > 0:
			for o in selection.get():
				if o.isActor():
					print("adding Box")
					o.isActor().addCapsule(EngineModule.Vec3(20,40,20))
		else:
			Engine.test()
				

	if key == EngineModule.Keys.K_SLASH:
		#for o in selection.get():
		#	o.setMaterialName("SSAO/GBuffer")

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

	if key == EngineModule.Keys.K_N:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			Engine.setTimingFactor(Engine.getTimingFactor() * 0.9)
			print("set timingfactor: " +str(Engine.getTimingFactor()))
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			Engine.setTimingFactor(Engine.getTimingFactor() * 1.1)
			print("set timingfactor: " +str(Engine.getTimingFactor()))

	if key == EngineModule.Keys.K_X:
		print("edit body joint pos,size")
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			jointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
			bodySize = body.getSize()
			print("body joint size pos: " + str(jointPos))
			print("body size: " + str(bodySize))

			#jointPos = EngineModule.Vec3(-153,3,90) 
			#bodySize = EngineModule.Vec3(5,2.9,1.6) 

			bodyjoint.bodyJointScaleJointPos(body,joint, jointPos)
			bodyjoint.bodyJointScaleBody(body,joint, bodySize )

			jointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
			bodySize = body.getSize()
			print("body joint size pos: " + str(jointPos))
			print("body size: " + str(bodySize))

	if key == EngineModule.Keys.K_B:
		print("edit body joint pos")
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			jointPos = bodyjoint.getBodyJointAnchorPos(body,joint)
			bodySize = body.getSize()
			print("body joint pos: " + str(jointPos))
			print("body size: " + str(bodySize))

			#jointPos = EngineModule.Vec3(-153,3,90) 
			#jointPos.x *= 1.1
			#bodySize = EngineModule.Vec3(15,1,15)
			#jointPos.y *= 0.9

			bodyjoint.setBodyJointAnchorPos(body,joint,jointPos)
			body.setSize(bodySize)

			jointPos = bodyjoint.getBodyJointAnchorPos(body,joint)
			bodySize = body.getSize()
			print("body joint pos: " + str(jointPos))
			print("body size: " + str(bodySize))

	if key == EngineModule.Keys.K_O:
		print("move selection")
		for o in selection.get():
			step = 20
			changeVec = None
			if Engine.isKeyDown(EngineModule.Keys.K_8):
				step = 1
			if Engine.isKeyDown(EngineModule.Keys.K_1):
				changeVec = EngineModule.Vec3(step,0,0)
			if Engine.isKeyDown(EngineModule.Keys.K_2):
				changeVec = EngineModule.Vec3(0,step,0)
			if Engine.isKeyDown(EngineModule.Keys.K_3):
				changeVec = EngineModule.Vec3(0,0,step)
			if Engine.isKeyDown(EngineModule.Keys.K_4):
				changeVec = EngineModule.Vec3(-step,0,0)
			if Engine.isKeyDown(EngineModule.Keys.K_5):
				changeVec = EngineModule.Vec3(0,-step,0)
			if Engine.isKeyDown(EngineModule.Keys.K_6):
				changeVec = EngineModule.Vec3(0,0,-step)

			if changeVec:
				if o.isPhysicShape():
					o.setLocalPosition(o.getLocalPosition() + changeVec)
				if o.isActor():
					o.setPosition(o.getPosition() + changeVec)

			if Engine.isKeyDown(EngineModule.Keys.K_7):
				o.setPosition(o.getPosition() * EngineModule.Vec3(1,0.9,1))

			if Engine.isKeyDown(EngineModule.Keys.K_9):
				o.setOrientation(o.getOrientation() * EngineModule.Quat().fromAngles(0,5,0))
			if Engine.isKeyDown(EngineModule.Keys.K_0):
				o.setOrientation(o.getOrientation() * EngineModule.Quat().fromAngles(0,-5,0))

	if key == EngineModule.Keys.K_T:
		pass
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()
		#for o in selection.get():
		#if Engine.isKeyDown(EngineModule.Keys.K_7):


		if Engine.isKeyDown(EngineModule.Keys.K_1):
			print("temp loading")
			saveload.load(Engine,EngineModule,"xmlscene/ragdoll.xml",objects)
			#saveload.load(Engine,EngineModule,"xmlscene/test.xml",objects)
		elif Engine.isKeyDown(EngineModule.Keys.K_2):
			print("temp saving")
			saveload.save(Engine,EngineModule,"xmlscene/ragdoll.xml",objects)
			#saveload.save(Engine,EngineModule,"xmlscene/test.xml",objects)
		else:
			pass

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass
