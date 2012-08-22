"""
bonescale:
	h: scale body
	g: scale joint pos
	j: select next bone of body
"""

import bodyjoint




def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass


	if key == EngineModule.Keys.K_G:
		factor = EngineModule.Vec3(1,1,1)
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			factor = EngineModule.Vec3(1.1,1,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_2):
			factor = EngineModule.Vec3(1,1.1,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_3):
			factor = EngineModule.Vec3(1,1,1.1)
		elif Engine.isKeyDown(EngineModule.Keys.K_4):
			factor = EngineModule.Vec3(0.9,1,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_5):
			factor = EngineModule.Vec3(1,0.9,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_6):
			factor = EngineModule.Vec3(1,1,0.9)


		factor = EngineModule.Vec3(0,0,0)
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			factor = EngineModule.Vec3(0.1,0,0)
		elif Engine.isKeyDown(EngineModule.Keys.K_2):
			factor = EngineModule.Vec3(0,0.1,0)
		elif Engine.isKeyDown(EngineModule.Keys.K_3):
			factor = EngineModule.Vec3(0,0,0.1)
		elif Engine.isKeyDown(EngineModule.Keys.K_4):
			factor = EngineModule.Vec3(-0.1,0,0)
		elif Engine.isKeyDown(EngineModule.Keys.K_5):
			factor = EngineModule.Vec3(0,-0.1,0)
		elif Engine.isKeyDown(EngineModule.Keys.K_6):
			factor = EngineModule.Vec3(0,0,-0.1)



		if len(selection.get()) == 2:
			body,joint = bodyjoint.getBodyJoint(selection.get())
			if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
				currentJointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
				bodyjoint.bodyJointScaleJointPos(body,joint, 
					currentJointPos + factor
					)

	if key == EngineModule.Keys.K_H:
		factor = EngineModule.Vec3(1,1,1)

		if Engine.isKeyDown(EngineModule.Keys.K_1):
			factor = EngineModule.Vec3(1.1,1,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_2):
			factor = EngineModule.Vec3(1,1.1,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_3):
			factor = EngineModule.Vec3(1,1,1.1)
		elif Engine.isKeyDown(EngineModule.Keys.K_4):
			factor = EngineModule.Vec3(0.9,1,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_5):
			factor = EngineModule.Vec3(1,0.9,1)
		elif Engine.isKeyDown(EngineModule.Keys.K_6):
			factor = EngineModule.Vec3(1,1,0.9)

		if len(selection.get()) == 2:
			body,joint = bodyjoint.getBodyJoint(selection.get())
			if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
				bodyjoint.bodyJointScaleBody(body,joint,
					body.getSize() * factor
					)

	if key == EngineModule.Keys.K_J:
		if len(selection.get()) == 1:
			body = None
			if selection.get()[0].isBody():
				body = selection.get()[0]
			if body:
				if body.howManyJoints() > 0:
					j = body.getJoint(0)
					selection.add(j)
		elif len(selection.get()) == 2:
			body,joint = bodyjoint.getBodyJoint(selection.get())
			if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
				if body.howManyJoints() > 0:
					selection.remove(joint)

					bodyJoints = body.howManyJoints()
					currentIndex = 0
					for index in range(0,bodyJoints):
						j = body.getJoint(index)
						if j.readUuid() == joint.readUuid():
							currentIndex = index
							break

					newIndex = currentIndex + 1
					if newIndex == body.howManyJoints():
						newIndex = 0

					j = body.getJoint(newIndex)
					selection.add(j)


def keyReleased(Engine,EngineModule,key,selection,objects):
	pass


