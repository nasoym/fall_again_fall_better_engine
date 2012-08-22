"""
misc:
	k: save
	l: load
	f: add force (1,2,3, 4,5,6, 7,8)
	y: rotate joint (1,2,3,4,5,6, 7) in steps of 10 degree
	u: set joint limits y:1,2 z:3,4 5 ,7 in steps of 5 units
	z: switch material (1,2)
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
		saveload.save(Engine,EngineModule,"xmlscene/file1.xml")

	if key == EngineModule.Keys.K_L:
		saveload.load(Engine,EngineModule,"xmlscene/file1.xml")



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
			Engine.isKeyDown(EngineModule.Keys.K_5) or
			Engine.isKeyDown(EngineModule.Keys.K_6)):
			for o in selection.get():
				if o and o.isGuiContainer():
					shapesNumber = o.howManyShapes()
					shapesList = []
					for i in range(0,shapesNumber):
						shape = o.getShapeByIndex(i)
						if Engine.isKeyDown(EngineModule.Keys.K_1):
							shape.setCustomMaterial()
						elif Engine.isKeyDown(EngineModule.Keys.K_2):
							shape.setMaterialName("Body")
						elif Engine.isKeyDown(EngineModule.Keys.K_5):
							shape.setFinalShape()
						elif Engine.isKeyDown(EngineModule.Keys.K_6):
							shape.setNonFinalShape()
				elif o and o.isGuiShape():
					if Engine.isKeyDown(EngineModule.Keys.K_1):
						o.setCustomMaterial()
					elif Engine.isKeyDown(EngineModule.Keys.K_2):
						o.setMaterialName("Body")
					elif Engine.isKeyDown(EngineModule.Keys.K_5):
						o.setFinalShape()
					elif Engine.isKeyDown(EngineModule.Keys.K_6):
						o.setNonFinalShape()

		if Engine.isKeyDown(EngineModule.Keys.K_3) or Engine.isKeyDown(EngineModule.Keys.K_4):
			if Engine.isKeyDown(EngineModule.Keys.K_3):
				objectsNumber = Engine.howManyObjects()
				for i in range(0,objectsNumber):
					o = Engine.getObject(i)
					if o.isGuiShape():
						if not o.isFinalShape():
							o.hide()
			elif Engine.isKeyDown(EngineModule.Keys.K_4):
				objectsNumber = Engine.howManyObjects()
				for i in range(0,objectsNumber):
					o = Engine.getObject(i)
					if o.isGuiShape():
						o.show()

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass

