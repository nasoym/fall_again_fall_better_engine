"""
misc:
	k: save
	l: load 
	f: add force default y+ (x+:1, y+:2, z+:3, x-:4, y-:5, z-:6 , spped*10:7, speed*0.5:8)
	y: rotate joint in 10 degree steps (x+:1, y+:2, z+:3, x-:4, y-:5, z-:6, degree step * 0.5:7)
	u: set joint limits in 5 unit steps y+:1, y-:2 z+:3, z-:4, reset:5, step size*0.5:7
	z: switch material 
		1: set custom material
		2: set material "body"
		3: set final shape
		4: set non final shape
		5: hide non final shapes
		6: show all shapes
"""
import saveload
import bodyjoint

def keyDown(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_F:
		forceValue = 5000
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
			if o.isBody():
				o.isBody().addForce(force)

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_K:
		saveload.save(Engine,EngineModule,"xmlscene/file2.xml")

	if key == EngineModule.Keys.K_L:
		saveload.load(Engine,EngineModule,"xmlscene/file2.xml")



	if key == EngineModule.Keys.K_Y:
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

	if key == EngineModule.Keys.K_Z:
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

