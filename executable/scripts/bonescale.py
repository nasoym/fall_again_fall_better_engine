"""
bonescale:
	h: scale body
	g: scale joint pos
	j: select next bone of body
"""

def getBodyJointAnchorSizePos(body,joint):
	if joint.getBody1().readUuid() == body.readUuid():
		return joint.getAnchor1Size()
	elif joint.getBody2().readUuid() == body.readUuid():
		return joint.getAnchor2Size()
	else:
		print("body is not 1 or 2")

def getBodyJointAnchorPos(body,joint):
	if joint.getBody1().readUuid() == body.readUuid():
		return joint.getAnchor1()
	elif joint.getBody2().readUuid() == body.readUuid():
		return joint.getAnchor2()
	else:
		print("body is not 1 or 2")

def setBodyJointAnchorSizePos(body,joint,position):
	if joint.getBody1().readUuid() == body.readUuid():
		joint.setAnchor1Size(position)
	elif joint.getBody2().readUuid() == body.readUuid():
		joint.setAnchor2Size(position)
	else:
		print("body is not 1 or 2")

def setBodyJointAnchorPos(body,joint,position):
	if joint.getBody1().readUuid() == body.readUuid():
		joint.setAnchor1(position)
	elif joint.getBody2().readUuid() == body.readUuid():
		joint.setAnchor2(position)
	else:
		print("body is not 1 or 2")

def isBodyJointConnected(body,joint):
	if joint.getBody1().readUuid() == body.readUuid():
		return True
	elif joint.getBody2().readUuid() == body.readUuid():
		return True
	else:
		print("body is not 1 or 2")
	return False

def bodyJointScaleBody(body,joint,newBodySize):
	if isBodyJointConnected(body,joint):
		oldJointAnchorPos = getBodyJointAnchorPos(body,joint)
		oldJointAnchorSizePos = getBodyJointAnchorSizePos(body,joint)
		body.setSize(newBodySize)
		setBodyJointAnchorSizePos(body,joint,oldJointAnchorSizePos)
		newJointAnchorPos = getBodyJointAnchorPos(body,joint)

		bodyJoints = body.howManyJoints()
		for index in range(0,bodyJoints):
			j = body.getJoint(index)
			if not (j.readUuid() == joint.readUuid()):
				anchor = getBodyJointAnchorPos(body,j)
				oldRelativePos = anchor - oldJointAnchorPos
				newRelativePos = oldRelativePos + newJointAnchorPos
				setBodyJointAnchorPos(body,j,newRelativePos)
		
def bodyJointScaleJointPos(body,joint,newJointSizePos):
	if isBodyJointConnected(body,joint):
		oldJointAnchorPos = getBodyJointAnchorPos(body,joint)
		setBodyJointAnchorSizePos(body,joint,newJointSizePos)
		newJointAnchorPos = getBodyJointAnchorPos(body,joint)

		bodyJoints = body.howManyJoints()
		for index in range(0,bodyJoints):
			j = body.getJoint(index)
			if not (j.readUuid() == joint.readUuid()):
				anchor = getBodyJointAnchorPos(body,j)
				oldRelativePos = anchor - oldJointAnchorPos
				newRelativePos = oldRelativePos + newJointAnchorPos
				setBodyJointAnchorPos(body,j,newRelativePos)

def getBodyJoint(selection):
	body = None
	joint = None
	if selection[0].isBody():
		body = selection[0]
	if selection[1].isBody():
		body = selection[1]
	if selection[0].isJoint():
		joint = selection[0]
	if selection[1].isJoint():
		joint = selection[1]
	return (body,joint)

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
			body,joint = getBodyJoint(selection.get())
			if ((body and joint) and isBodyJointConnected(body,joint)):
				currentJointPos = getBodyJointAnchorSizePos(body,joint)
				bodyJointScaleJointPos(body,joint, 
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
			body,joint = getBodyJoint(selection.get())
			if ((body and joint) and isBodyJointConnected(body,joint)):
				bodyJointScaleBody(body,joint,
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
			body,joint = getBodyJoint(selection.get())
			if ((body and joint) and isBodyJointConnected(body,joint)):
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


