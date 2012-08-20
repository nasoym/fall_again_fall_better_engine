"""
creators:
	c: create
		1: space cage
		2: box
		3: two jointed boxes
		4: ragdoll
"""

import scripts.createobjects as create
import scripts.ragdoll as ragdoll

def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_C:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			create.createSpaceCage(Engine,EngineModule,EngineModule.Vec3(600,600,600))
		elif Engine.isKeyDown(EngineModule.Keys.K_2):
			#o = create.createPhysicBoxFinal(Engine,EngineModule)
			o = create.createBox(Engine,EngineModule)
			o.setPosition(EngineModule.Vec3(0,150,0))
			o.setSize(EngineModule.Vec3(10,10,10))
		elif Engine.isKeyDown(EngineModule.Keys.K_3):
			a = create.createPhysicBoxFinal(Engine,EngineModule)
			b = create.createPhysicBoxFinal(Engine,EngineModule)

			j = Engine.createJoint(a,b)
			j.setAnchor1Size( EngineModule.Vec3(1,0,0) )
			j.setAnchor2Size( EngineModule.Vec3(-1,0,0) )
			j.setLimits(20,20)
			j.setAnchor1Orientation(
				EngineModule.Quat().fromAngles(0,0,45) )

		elif Engine.isKeyDown(EngineModule.Keys.K_4):
			char = ragdoll.createHumanBodyParts(Engine,
				EngineModule,size=5,
				pos=EngineModule.Vec3(0,150,0),
				base=False)
			ragdoll.createHumanJoints(Engine,EngineModule,char)
			ragdoll.createLimits(Engine,EngineModule,char,45)
			ragdoll.createLimitsHuman(Engine,EngineModule,char)

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass


