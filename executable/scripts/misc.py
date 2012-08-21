"""
misc:
	k: save
	l: load
	f: add force (1,2,3, 4,5,6, 7,8)
	y: rotate joint (1,2,3,4,5,6, 7) in steps of 10 degree
	u: set joint limits y:1,2 z:3,4 5 ,7 in steps of 5 units
"""
import saveload

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


	if key == EngineModule.Keys.K_O:
		if len(selection.get()) == 1:
			o = selection.get()[0]
			o.setPosition(o.getPosition() * EngineModule.Vec3(1,0.9,1))

	if key == EngineModule.Keys.K_Y:
		if len(selection.get()) == 1:
			o = selection.get()[0]
			if o and o.isJoint():
				j = o.isJoint()
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
		if len(selection.get()) == 1:
			o = selection.get()[0]
			if o and o.isJoint():
				j = o.isJoint()
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


def keyReleased(Engine,EngineModule,key,selection,objects):
	pass

