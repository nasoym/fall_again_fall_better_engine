"""
temp:
	t: run temp
"""

import mesh
import createobjects as create


def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):
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
			pos14 = body14.getPosition()
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
			bodyLocalAnchor = body13.getOrientation().inverse() * (globalAnchor - body13.getPosition())

			joint = create.createJoint(Engine,EngineModule,ground,body13)

			joint.setAnchor1(parentLocalAnchor)
			joint.setAnchor2(bodyLocalAnchor)
			#joint.setAnchor1Orientation(EngineModule.Quat().fromAngles(0,0,-90))
			joint.setAnchor2Orientation(EngineModule.Quat().fromAngles(90,-90,0))
			joint.setLimits(10,10)

			globalAnchor = body14.getPosition()
			parentLocalAnchor = ground.getOrientation().inverse() * (globalAnchor - ground.getPosition())
			bodyLocalAnchor = body14.getOrientation().inverse() * (globalAnchor - body14.getPosition())

			joint = create.createJoint(Engine,EngineModule,ground,body14)

			joint.setAnchor1(parentLocalAnchor)
			joint.setAnchor2(bodyLocalAnchor)
			#joint.setAnchor1Orientation(EngineModule.Quat().fromAngles(0,0,-90))
			joint.setAnchor2Orientation(EngineModule.Quat().fromAngles(90,-90,0))
			joint.setLimits(10,10)

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass
