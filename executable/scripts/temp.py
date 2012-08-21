"""
temp:
	t: run temp
	f: add force
	y: rotate joint (1,2,3,4,5,6) in steps of 10 degree
	u: set joint limits y:1,2 z:3,4 in steps of 5 units
"""

import mesh
import createobjects as create


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

	if key == EngineModule.Keys.K_O:
		if len(selection.get()) == 1:
			o = selection.get()[0]
			o.setPosition(o.getPosition() * EngineModule.Vec3(1,0,1))

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

	if key == EngineModule.Keys.K_T:
		pass
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()
		#for o in selection.get():

		o = Engine.createMesh("Character.mesh")
		o.setColour(1,0,0,0.2)
		#o.setColour(1,0,0,0.9)
		#o.setMaterialName("Body")
		o.setSize(EngineModule.Vec3(1,1,1)*1000)
		o.setPosition(EngineModule.Vec3(0,150,0))
		mesh.createBones(Engine,EngineModule,o)
		o.setUnselectable()
		o.calcLocalPosOfRootBone()

		body13 = None
		body14 = None
		bonesNumber = o.getNumberOfBones()
		bonesList = []
		for i in range(0,bonesNumber):
			body = o.getBodyByIndex(i)
			if body.getName() == "Bone.014":
				body14 = body
			if body.getName() == "Bone.013":
				body13 = body
		if body13 and body14:
			pos13 = body13.getPosition()
			#pos13 += body13.getOrientation() * body13.getSize() 
			pos14 = body14.getPosition()
			#pos14 += body14.getOrientation() * body14.getSize() 

			halfpos = pos14 - pos13
			halfpos = halfpos * EngineModule.Vec3(0.5,0.5,0.5)
			finalPos = pos13 + halfpos
			finalPos.y -= 5

			xySize = (halfpos.x + halfpos.y ) * 5

			ground = create.createPhysicStaticBoxStructure(Engine,EngineModule)
			ground.setPosition(finalPos)
			ground.setSize(EngineModule.Vec3(
				xySize,1,xySize
				) )
			ground.setOrientation(o.getOrientation())


			globalAnchor = body13.getPosition()
			parentLocalAnchor = ground.getOrientation().inverse() * (globalAnchor - ground.getPosition())
			bodyPosition = body13.getPosition()
			bodyPosition += body13.getOrientation() * (body13.getSize() * EngineModule.Vec3(-1,0,0))
			bodyLocalAnchor = body13.getOrientation().inverse() * (globalAnchor - bodyPosition)

			#joint = create.createJoint(Engine,EngineModule,ground,body13)
			joint = Engine.createJoint(ground,body13)

			joint.setAnchor1(parentLocalAnchor)
			joint.setAnchor2(bodyLocalAnchor)
			#joint.setAnchor1Orientation(EngineModule.Quat().fromAngles(0,0,-90))
			#joint.setAnchor2Orientation(EngineModule.Quat().fromAngles(90,-90,0))
			joint.setAnchor1Orientation(body13.getOrientation() * ground.getOrientation().inverse() )
			#joint.setLimits(40,40)
			#joint.setLimits(10,10)
			#joint.setLimits(1,1)
			joint.setLimits(0,0)

			b = Engine.createGuiBox()
			b.setColour(0,1,1,0.5)
			b.setSize(EngineModule.Vec3(1,4,4))
			b.setScalingFixed()
			joint.addShape(b)

			globalAnchor = body14.getPosition()
			parentLocalAnchor = ground.getOrientation().inverse() * (globalAnchor - ground.getPosition())
			bodyPosition = body14.getPosition()
			bodyPosition += body14.getOrientation() * (body14.getSize() * EngineModule.Vec3(-1,0,0))
			bodyLocalAnchor = body14.getOrientation().inverse() * (globalAnchor - bodyPosition)

			#joint = create.createJoint(Engine,EngineModule,ground,body14)
			joint = Engine.createJoint(ground,body14)

			joint.setAnchor1(parentLocalAnchor)
			joint.setAnchor2(bodyLocalAnchor)
			#joint.setAnchor1Orientation(EngineModule.Quat().fromAngles(0,0,-90))
			#joint.setAnchor2Orientation(EngineModule.Quat().fromAngles(90,-90,0))
			joint.setAnchor1Orientation(body14.getOrientation() * ground.getOrientation().inverse() )
			#joint.setLimits(40,40)
			#joint.setLimits(10,10)
			#joint.setLimits(1,1)
			joint.setLimits(0,0)

			b = Engine.createGuiBox()
			b.setColour(0,1,1,0.5)
			b.setSize(EngineModule.Vec3(1,4,4))
			b.setScalingFixed()
			joint.addShape(b)

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass
