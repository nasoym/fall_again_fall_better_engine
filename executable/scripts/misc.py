"""misc:
	k: save
		1: scene.xml
		2: ragdoll.xml
		3: test.xml
	l: load 
		1: scene.xml
		2: ragdoll.xml
		3: test.xml
	f: add force default y+ 
		x+:1, y+:2, z+:3, x-:4, y-:5, z-:6 
	z: switch material 
		1: set custom material
		2: set material "body"
		3: set final shape
		4: set non final shape
		5: hide non final shapes
		6: show all shapes
	n: set timingfactor 1:*0.9 2:*1.1
	i: show object info

	r: set ambient light
	y: set camera fov
	u: set gravity
"""
import saveload
import bodyjoint

def keyDown(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_F:
		forceValue = 1000
		force = EngineModule.Vec3(0,forceValue,0)

		if Engine.isKeyDown(EngineModule.Keys.K_EQUALS):
			forceValue *= 10
		if Engine.isKeyDown(EngineModule.Keys.K_MINUS):
			forceValue *= 0.5

		if Engine.isKeyDown(EngineModule.Keys.K_1):
			force = EngineModule.Vec3(forceValue,0,0)
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			force = EngineModule.Vec3(0,forceValue,0)
		if Engine.isKeyDown(EngineModule.Keys.K_3):
			force = EngineModule.Vec3(0,0,forceValue)
		if Engine.isKeyDown(EngineModule.Keys.K_4):
			force = EngineModule.Vec3(-forceValue,0,0)
		if Engine.isKeyDown(EngineModule.Keys.K_5):
			force = EngineModule.Vec3(0,-forceValue,0)
		if Engine.isKeyDown(EngineModule.Keys.K_6):
			force = EngineModule.Vec3(0,0,-forceValue)

		for o in selection.get():
			if o.isActor():
				o.isActor().addForce(force)


def vecclamp(vec):
	if vec.x > 1.0:
		vec.x = 1.0
	if vec.y > 1.0:
		vec.y = 1.0
	if vec.z > 1.0:
		vec.z = 1.0
	
	if vec.x < 0.0:
		vec.x = 0.0
	if vec.y < 0.0:
		vec.y = 0.0
	if vec.z < 0.0:
		vec.z = 0.0
	return vec

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	"""
	if key == EngineModule.Keys.K_R:
		ambient = Engine.getAmbientLight()
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			ambient.x += 0.05
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			ambient.y += 0.05
		if Engine.isKeyDown(EngineModule.Keys.K_3):
			ambient.z += 0.05
		if Engine.isKeyDown(EngineModule.Keys.K_4):
			ambient.x -= 0.05
		if Engine.isKeyDown(EngineModule.Keys.K_5):
			ambient.y -= 0.05
		if Engine.isKeyDown(EngineModule.Keys.K_6):
			ambient.z -= 0.05
		vecclamp(ambient)
		print("set ambient light to: " + str(ambient))
		Engine.setAmbientLight(ambient)
		"""

	"""
	if key == EngineModule.Keys.K_Y:
		fov = Engine.getCameraFOV()
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			fov += 2
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			fov -= 2
		if fov < 0:
			fov = 0
		if fov > 180:
			fov = 180
		print("set FieldOfView to: " + str(fov))
		Engine.setCameraFOV(fov)
		"""

	if key == EngineModule.Keys.K_U:
		gravity = Engine.getGravity()
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			gravity.x += 0.5
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			gravity.y += 0.5
		if Engine.isKeyDown(EngineModule.Keys.K_3):
			gravity.z += 0.5
		if Engine.isKeyDown(EngineModule.Keys.K_4):
			gravity.x -= 0.5
		if Engine.isKeyDown(EngineModule.Keys.K_5):
			gravity.y -= 0.5
		if Engine.isKeyDown(EngineModule.Keys.K_6):
			gravity.z -= 0.5
		print("set gravity to: " + str(gravity))
		Engine.setGravity(gravity)


	if key == EngineModule.Keys.K_K:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			print("save scene.xml")
			saveload.save(Engine,EngineModule,"xmlscene/scene.xml",objects)
			print("done")
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			print("save ragdoll.xml")
			saveload.save(Engine,EngineModule,"xmlscene/ragdoll.xml",objects)
			print("done")
		if Engine.isKeyDown(EngineModule.Keys.K_3):
			print("save test.xml")
			saveload.save(Engine,EngineModule,"xmlscene/test.xml",objects)
			print("done")

	if key == EngineModule.Keys.K_L:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			print("load scene.xml")
			saveload.load(Engine,EngineModule,"xmlscene/scene.xml",objects)
			print("done")
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			print("load ragdoll.xml")
			saveload.load(Engine,EngineModule,"xmlscene/ragdoll.xml",objects)
			print("done")
		if Engine.isKeyDown(EngineModule.Keys.K_3):
			print("load test.xml")
			saveload.load(Engine,EngineModule,"xmlscene/test.xml",objects)
			print("done")

	if key == EngineModule.Keys.K_Z:
		print("change material and visibilty")
		#if len(selection.get()) == 1:
		#	o = selection.get()[0]
		if (Engine.isKeyDown(EngineModule.Keys.K_1) or 
			Engine.isKeyDown(EngineModule.Keys.K_2) or
			Engine.isKeyDown(EngineModule.Keys.K_3) or
			Engine.isKeyDown(EngineModule.Keys.K_4)):
			materialName = "Body"
			#materialName = "test2"
			for o in selection.get():
				if o and o.isGuiContainer():
					shapesNumber = o.howManyShapes()
					shapesList = []
					for i in range(0,shapesNumber):
						shape = o.getShapeByIndex(i)
						if Engine.isKeyDown(EngineModule.Keys.K_1):
							shape.setCustomMaterial()
						elif Engine.isKeyDown(EngineModule.Keys.K_2):
							shape.setMaterialName(materialName)
						elif Engine.isKeyDown(EngineModule.Keys.K_3):
							shape.setFinalShape()
						elif Engine.isKeyDown(EngineModule.Keys.K_4):
							shape.setNonFinalShape()
				elif o and o.isGuiShape():
					if Engine.isKeyDown(EngineModule.Keys.K_1):
						o.setCustomMaterial()
					elif Engine.isKeyDown(EngineModule.Keys.K_2):
						o.setMaterialName(materialName)
					elif Engine.isKeyDown(EngineModule.Keys.K_3):
						o.setFinalShape()
					elif Engine.isKeyDown(EngineModule.Keys.K_4):
						o.setNonFinalShape()

		if Engine.isKeyDown(EngineModule.Keys.K_5) or Engine.isKeyDown(EngineModule.Keys.K_6):
			if Engine.isKeyDown(EngineModule.Keys.K_5):
				objectsNumber = Engine.howManyObjects()
				for i in range(0,objectsNumber):
					o = Engine.getObject(i)
					if o.isGuiShape():
						if not o.isFinalShape():
							o.hide()
			elif Engine.isKeyDown(EngineModule.Keys.K_6):
				objectsNumber = Engine.howManyObjects()
				for i in range(0,objectsNumber):
					o = Engine.getObject(i)
					if o.isGuiShape():
						o.show()

	if key == EngineModule.Keys.K_N:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			Engine.setTimingFactor(Engine.getTimingFactor() * 0.9)
			print("set timingfactor: " +str(Engine.getTimingFactor()))
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			Engine.setTimingFactor(Engine.getTimingFactor() * 1.1)
			print("set timingfactor: " +str(Engine.getTimingFactor()))


	if key == EngineModule.Keys.K_I:
		for o in selection.get():
			print("object: " + str(o))
			print("    name: " + str(o.getName()))
			print("    uuid: " + str(o.readUuid()))
			if o.isJoint():
				print("    yLimit: " + str(o.isJoint().getYLimit()))
				print("    zLimit: " + str(o.isJoint().getZLimit()))
				print("    anchor 1: " + str(o.isJoint().getAnchor1()))
				print("    anchor 2: " + str(o.isJoint().getAnchor2()))
				print("    anchor 1 orien: " + str(o.isJoint().getAnchor1Orientation().toAngles()))
				print("    anchor 2 orien: " + str(o.isJoint().getAnchor2Orientation().toAngles()))
				print("    motorOn: " + str(o.isJoint().isMotorOn()))
				print("    motor target: " + str(o.isJoint().getMotorTarget().toAngles()))

		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			pass
			jointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
			print("body joint size pos: " + str(jointPos))

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass

