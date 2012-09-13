"""misc:
	k: save
	l: load 
	f: add force default y+ 
		(x+:1, y+:2, z+:3, x-:4, y-:5, z-:6 , 
		speed*10:7, speed*0.5:8)
	y: rotate joint in 10 degree steps 
		(x+:1, y+:2, z+:3, x-:4, y-:5, z-:6, 
		degree step*0.5:7)
	u: set joint limits in 5 unit steps 
		y+:1, y-:2 z+:3, z-:4, reset:5, step size*0.5:7
	z: switch material 
		1: set custom material
		2: set material "body"
		3: set final shape
		4: set non final shape
		5: hide non final shapes
		6: show all shapes
	r: change joint motor target by 10 degree steps
		(x+:1, y+:2, z+:3, x-:4, y-:5, z-:6 , 
		half stepsize:7)
		-: reset target
		8: motor on
		9: motor off
"""
import saveload
import bodyjoint

def keyDown(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_F:
		forceValue = 1000
		force = EngineModule.Vec3(0,forceValue,0)
		if Engine.isKeyDown(EngineModule.Keys.K_7):
			forceValue *= 10
		if Engine.isKeyDown(EngineModule.Keys.K_8):
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

	if key == EngineModule.Keys.K_MLEFT:
		mx = Engine.getMouseRelX()	
		my = Engine.getMouseRelY()	
		factor = 0.1
		Engine.cameraRotateY(mx * -factor)
		Engine.cameraRotateZ(my * -factor)

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
		print("save scene")
		saveload.save(Engine,EngineModule,"xmlscene/scene.xml",objects)
		print("done")

	if key == EngineModule.Keys.K_L:
		print("load scene")
		saveload.load(Engine,EngineModule,"xmlscene/scene.xml",objects)
		print("done")

	"""
	if key == EngineModule.Keys.K_R:
		print("change joint motor target orientation")
		j = None
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			j = joint
		if not j:
			if len(selection.get()) == 1:
				o = selection.get()[0]
				if o and o.isJoint():
					j = o.isJoint()
		if j:
			angleStep = 10
			#angle = EngineModule.Quat().fromAngles(0,0,0)
			angle = None
			if Engine.isKeyDown(EngineModule.Keys.K_7):
				angleStep *= 0.5
			if Engine.isKeyDown(EngineModule.Keys.K_1):
				angle = EngineModule.Quat().fromAngles(angleStep,0,0)
			if Engine.isKeyDown(EngineModule.Keys.K_2):
				angle = EngineModule.Quat().fromAngles(0,angleStep,0)
			if Engine.isKeyDown(EngineModule.Keys.K_3):
				angle = EngineModule.Quat().fromAngles(0,0,angleStep)
			if Engine.isKeyDown(EngineModule.Keys.K_4):
				angle = EngineModule.Quat().fromAngles(-angleStep,0,0)
			if Engine.isKeyDown(EngineModule.Keys.K_5):
				angle = EngineModule.Quat().fromAngles(0,-angleStep,0)
			if Engine.isKeyDown(EngineModule.Keys.K_6):
				angle = EngineModule.Quat().fromAngles(0,0,-angleStep)
				
			if angle:
				motorTarget = j.getMotorTarget() * angle
				j.setMotorTarget(motorTarget)
				if j.isMotorOn():
					j.setMotorOn()

			if Engine.isKeyDown(EngineModule.Keys.K_MINUS):
				print("reset motor target")
				j.setMotorTarget(EngineModule.Quat())

			if Engine.isKeyDown(EngineModule.Keys.K_8):
				print("set motor target on")
				j.setMotorOn()

			if Engine.isKeyDown(EngineModule.Keys.K_9):
				print("set motor target off")
				j.setMotorOff()

	if key == EngineModule.Keys.K_Y:
		print("change joint orientation")
		j = None
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			j = joint
		if not j:
			if len(selection.get()) == 1:
				o = selection.get()[0]
				if o and o.isJoint():
					j = o.isJoint()
		if j:
			angleStep = 10
			angle = EngineModule.Quat().fromAngles(0,0,0)
			if Engine.isKeyDown(EngineModule.Keys.K_7):
				angleStep *= 0.5
			if Engine.isKeyDown(EngineModule.Keys.K_1):
				angle = EngineModule.Quat().fromAngles(angleStep,0,0)
			if Engine.isKeyDown(EngineModule.Keys.K_2):
				angle = EngineModule.Quat().fromAngles(0,angleStep,0)
			if Engine.isKeyDown(EngineModule.Keys.K_3):
				angle = EngineModule.Quat().fromAngles(0,0,angleStep)
			if Engine.isKeyDown(EngineModule.Keys.K_4):
				angle = EngineModule.Quat().fromAngles(-angleStep,0,0)
			if Engine.isKeyDown(EngineModule.Keys.K_5):
				angle = EngineModule.Quat().fromAngles(0,-angleStep,0)
			if Engine.isKeyDown(EngineModule.Keys.K_6):
				angle = EngineModule.Quat().fromAngles(0,0,-angleStep)
			newOri = j.getAnchor1Orientation() * angle
			j.setAnchor1Orientation(newOri)

	if key == EngineModule.Keys.K_U:
		print("change joint limits")
		j = None
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			j = joint
		if not j:
			if len(selection.get()) == 1:
				o = selection.get()[0]
				if o and o.isJoint():
					j = o.isJoint()
		if j:
			yLimit = j.getYLimit()
			zLimit = j.getZLimit()

			limitStep = 5
			if Engine.isKeyDown(EngineModule.Keys.K_7):
				limitStep *= 0.5
			if Engine.isKeyDown(EngineModule.Keys.K_1):
				yLimit += limitStep
			if Engine.isKeyDown(EngineModule.Keys.K_2):
				if yLimit <= limitStep:
					yLimit = 0
				else:
					yLimit -= limitStep
				
			if Engine.isKeyDown(EngineModule.Keys.K_3):
				zLimit += limitStep
			if Engine.isKeyDown(EngineModule.Keys.K_4):
				if zLimit <= limitStep:
					zLimit = 0
				else:
					zLimit -= limitStep

			if Engine.isKeyDown(EngineModule.Keys.K_5):
				yLimit = 0
				zLimit = 0

			j.setLimits(yLimit,zLimit)
			"""

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

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass

