"""
temp:
	t: run temp
		1:load
		2:save
	o: move object by step size 20 (x+:1, y+:2, z+:3, x-:4, y-:5, z-:6) 
		7: y*0.9
		8: step size:1
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
	if key == EngineModule.Keys.K_N:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			Engine.setTimingFactor(Engine.getTimingFactor() * 0.9)
			print("timingfactor: " +str(Engine.getTimingFactor()))
		if Engine.isKeyDown(EngineModule.Keys.K_2):
			Engine.setTimingFactor(Engine.getTimingFactor() * 1.1)
			print("timingfactor: " +str(Engine.getTimingFactor()))

	if key == EngineModule.Keys.K_X:
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			jointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
			bodySize = body.getSize()
			print("body joint size pos: " + str(jointPos))
			print("body size: " + str(bodySize))

			#jointPos = EngineModule.Vec3(-2,-0.5,0.3) 
			#bodySize = EngineModule.Vec3(3.3,2,2) 

			bodyjoint.bodyJointScaleJointPos(body,joint, jointPos)
			bodyjoint.bodyJointScaleBody(body,joint, bodySize )

			jointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
			bodySize = body.getSize()
			print("body joint pos: " + str(jointPos))
			print("body size: " + str(bodySize))

	if key == EngineModule.Keys.K_B:
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			jointPos = bodyjoint.getBodyJointAnchorPos(body,joint)
			bodySize = body.getSize()
			print("body joint pos: " + str(jointPos))
			print("body size: " + str(bodySize))

			jointPos.x *= 1.1

			bodyjoint.setBodyJointAnchorPos(body,joint,jointPos)
			body.setSize(bodySize)

			jointPos = bodyjoint.getBodyJointAnchorPos(body,joint)
			bodySize = body.getSize()
			print("body joint pos: " + str(jointPos))
			print("body size: " + str(bodySize))

	if key == EngineModule.Keys.K_O:
		if len(selection.get()) == 1:
			o = selection.get()[0]
			step = 20
			if Engine.isKeyDown(EngineModule.Keys.K_8):
				step = 1
			if Engine.isKeyDown(EngineModule.Keys.K_1):
				o.setPosition(o.getPosition() + EngineModule.Vec3(step,0,0))
			if Engine.isKeyDown(EngineModule.Keys.K_2):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,step,0))
			if Engine.isKeyDown(EngineModule.Keys.K_3):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,0,step))
			if Engine.isKeyDown(EngineModule.Keys.K_4):
				o.setPosition(o.getPosition() + EngineModule.Vec3(-step,0,0))
			if Engine.isKeyDown(EngineModule.Keys.K_5):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,-step,0))
			if Engine.isKeyDown(EngineModule.Keys.K_6):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,0,-step))
			if Engine.isKeyDown(EngineModule.Keys.K_7):
				o.setPosition(o.getPosition() * EngineModule.Vec3(1,0.9,1))

	if key == EngineModule.Keys.K_T:
		pass
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()
		#for o in selection.get():
		#if Engine.isKeyDown(EngineModule.Keys.K_7):


		if Engine.isKeyDown(EngineModule.Keys.K_1):
			print("loading")
			saveload.load(Engine,EngineModule,"xmlscene/ragdoll_02.xml")
		elif Engine.isKeyDown(EngineModule.Keys.K_2):
			print("saving")
			saveload.save(Engine,EngineModule,"xmlscene/ragdoll_02.xml")
		else:
			pass

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass
