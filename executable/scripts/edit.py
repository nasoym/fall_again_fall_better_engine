"""edit:
	o: move object by step size 20 
		(x+:1, y+:2, z+:3, x-:4, y-:5, z-:6) 
		7: y*0.9
		8: step size=1
	x: work on body,joint: sizepos with all joints
	b: work on body,joint: singual anchor pos 
	m: joint motor
		1:on 2:off 3,4,5: set different values

	j: select next bone of body


	r: rotate
	t: translate
	y: scale
"""
import bodyjoint

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def delFromSelectionList(selectionList,engineObject):
	for s in selectionList:
		if s.readUuid() == engineObject.readUuid():
			selectionList.remove(s)
			break

def findBodyForJoint(Engine,EngineModule,selection,joint):
	bodies = []
	for o in selection:
		if o.isActor():
			if bodyjoint.isBodyJointConnected(o,joint):
				bodies.append(o)
	if len(bodies) > 0:
		foundBody = bodies[0]
		otherConnectedJoints = []
		tooMany = False
		for j in selection:
			if j.isJoint():
				if bodyjoint.isBodyJointConnected(foundBody,j):
					otherConnectedJoints.append(j)
		if len(otherConnectedJoints) > 0:
			for j in otherConnectedJoints:
				delFromSelectionList(selection,j)
			tooMany = True

		if len(bodies) > 1:
			tooMany = True

		for body in bodies:
			delFromSelectionList(selection,body)

		return foundBody,tooMany
	else:
		return None,False

def findJointForBody(Engine,EngineModule,selection,body):
	joints = []
	for o in selection:
		if o.isJoint():
			if bodyjoint.isBodyJointConnected(body,o):
				joints.append(o)

	if len(joints) > 0:
		foundJoint = joints[0]
		tooMany = False
		otherConnectedActors = []
		for j in selection:
			if j.isActor():
				if bodyjoint.isBodyJointConnected(j,foundJoint):
					otherConnectedActors.append(j)
		if len(otherConnectedActors) > 0:
			for j in otherConnectedActors:
				delFromSelectionList(selection,j)
			tooMany = True

		if len(joints) > 1:
			tooMany = True

		for joint in joints:
			delFromSelectionList(selection,joint)

		return foundJoint,tooMany
	else:
		return None,False

def getModifiedQuaternion(Engine,EngineModule,stepSize):
	quaternion = EngineModule.Quat().fromAngles(0,0,0)

	finalStepSize = stepSize
	if Engine.isKeyDown(EngineModule.Keys.K_MINUS):
		finalStepSize *= 0.5
	elif Engine.isKeyDown(EngineModule.Keys.K_EQUALS):
		finalStepSize *= 2.0

	if Engine.isKeyDown(EngineModule.Keys.K_1):
		quaternion = EngineModule.Quat().fromAngles(finalStepSize,0,0)
	if Engine.isKeyDown(EngineModule.Keys.K_2):
		quaternion = EngineModule.Quat().fromAngles(0,finalStepSize,0)
	if Engine.isKeyDown(EngineModule.Keys.K_3):
		quaternion = EngineModule.Quat().fromAngles(0,0,finalStepSize)
	if Engine.isKeyDown(EngineModule.Keys.K_4):
		quaternion = EngineModule.Quat().fromAngles(-finalStepSize,0,0)
	if Engine.isKeyDown(EngineModule.Keys.K_5):
		quaternion = EngineModule.Quat().fromAngles(0,-finalStepSize,0)
	if Engine.isKeyDown(EngineModule.Keys.K_6):
		quaternion = EngineModule.Quat().fromAngles(0,0,-finalStepSize)

	return quaternion

def getModifiedVector(Engine,EngineModule,stepSize):
	vector = EngineModule.Vec3()

	finalStepSize = stepSize
	if Engine.isKeyDown(EngineModule.Keys.K_MINUS):
		finalStepSize *= 0.5
	elif Engine.isKeyDown(EngineModule.Keys.K_EQUALS):
		finalStepSize *= 2.0

	if Engine.isKeyDown(EngineModule.Keys.K_1):
		vector = EngineModule.Vec3(finalStepSize,0,0)
	if Engine.isKeyDown(EngineModule.Keys.K_2):
		vector = EngineModule.Vec3(0,finalStepSize,0)
	if Engine.isKeyDown(EngineModule.Keys.K_3):
		vector = EngineModule.Vec3(0,0,finalStepSize)
	if Engine.isKeyDown(EngineModule.Keys.K_4):
		vector = EngineModule.Vec3(-finalStepSize,0,0)
	if Engine.isKeyDown(EngineModule.Keys.K_5):
		vector = EngineModule.Vec3(0,-finalStepSize,0)
	if Engine.isKeyDown(EngineModule.Keys.K_6):
		vector = EngineModule.Vec3(0,0,-finalStepSize)
	return vector



def keyPressed(Engine,EngineModule,key,selection,objects):

	if key == EngineModule.Keys.K_R:
		print("rotate")
		sel = selection.get()[:]
		while len(sel)>0:
			o = sel.pop()
			body = None
			joint = None
			tooMany = False
			if o.isJoint():
				body,tooMany = findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				print("rotate shape")
				angle = getModifiedQuaternion(Engine,EngineModule,5)
				o.setLocalOrientation(o.getLocalOrientation() * angle)

				if Engine.isKeyDown(EngineModule.Keys.K_0):
					o.setLocalOrientation(EngineModule.Quat())

			elif o.isGuiShape():
				print("found guishape")

			if not tooMany:
				if body and joint:
					print("found body and joint")	
					print("rotate joint orientation")
					angle = getModifiedQuaternion(Engine,EngineModule,10)
					bodyNum = bodyjoint.howIsBodyConnectedToJoint(body,joint)
					if bodyNum == 1:
						newOri = joint.getAnchor1Orientation() * angle
						joint.setAnchor1Orientation(newOri)
						if Engine.isKeyDown(EngineModule.Keys.K_0):
							joint.setAnchor1Orientation(EngineModule.Quat())
					if bodyNum == 2:
						newOri = joint.getAnchor2Orientation() * angle
						joint.setAnchor2Orientation(newOri)
						if Engine.isKeyDown(EngineModule.Keys.K_0):
							joint.setAnchor2Orientation(EngineModule.Quat())

				elif body and not joint:
					print("found single body")	
					print("rotate body")
					angle = getModifiedQuaternion(Engine,EngineModule,5)
					body.setOrientation(body.getOrientation() * angle)

					if Engine.isKeyDown(EngineModule.Keys.K_0):
						body.setOrientation(EngineModule.Quat())

				elif joint and not body:
					print("found single joint")	
					print("rotate joint motor target")
					angle = getModifiedQuaternion(Engine,EngineModule,10)
					motorTarget = joint.getMotorTarget() * angle
					joint.setMotorTarget(motorTarget)
					if joint.isMotorOn():
						joint.setMotorOn()

					if Engine.isKeyDown(EngineModule.Keys.K_0):
						print("reset motor target")
						joint.setMotorTarget(EngineModule.Quat())

			else:
				print("found too many connected joints and bodies")

	if key == EngineModule.Keys.K_T:
		print("translate")

		sel = selection.get()[:]
		while len(sel)>0:
			o = sel.pop()
			body = None
			joint = None
			tooMany = False
			if o.isJoint():
				body,tooMany = findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				print("move localy")
				vector = getModifiedVector(Engine,EngineModule,20)
				vector = o.getLocalOrientation() * vector
				o.setLocalPosition(o.getLocalPosition() + vector)
				if Engine.isKeyDown(EngineModule.Keys.K_0):
					o.setLocalPosition(EngineModule.Vec3())

			elif o.isGuiShape():
				print("found guishape")

			if not tooMany:
				if body and joint:
					print("found body and joint")	
					print("move joint pos in rel to body")
					vector = getModifiedVector(Engine,EngineModule,0.1)
					currentJointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
					bodyjoint.bodyJointScaleJointPos(body,joint, 
						currentJointPos + vector
						)
					if Engine.isKeyDown(EngineModule.Keys.K_0):
						pass

				elif body and not joint:
					print("found single body")	
					print("move globaly")
					vector = getModifiedVector(Engine,EngineModule,20)
					vector = body.getOrientation() * vector
					body.setPosition(body.getPosition() + vector)

					if Engine.isKeyDown(EngineModule.Keys.K_0):
						body.setPosition(EngineModule.Vec3())

				elif joint and not body:
					print("found single joint")	

			else:
				print("found too many connected joints and bodies")




	if key == EngineModule.Keys.K_Y:
		print("scale")
		sel = selection.get()[:]
		while len(sel)>0:
			o = sel.pop()
			body = None
			joint = None
			tooMany = False
			if o.isJoint():
				body,tooMany = findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				print("scale localy")
				vector = getModifiedVector(Engine,EngineModule,0.1)
				o.setLocalSize(o.getLocalSize() * (EngineModule.Vec3(1,1,1) + vector))

			elif o.isGuiShape():
				print("found guishape")

			if not tooMany:
				if body and joint:
					print("found body and joint")	
					print("scale body with regards of joints")
					vector = getModifiedVector(Engine,EngineModule,0.1)
					bodyjoint.bodyJointScaleBody(body,joint,
						body.getSize() * (EngineModule.Vec3(1,1,1) + vector)
						)

				elif body and not joint:
					print("found single body")	
					print("scale")
					vector = getModifiedVector(Engine,EngineModule,0.1)
					body.setSize(body.getSize() * (EngineModule.Vec3(1,1,1) + vector))

				elif joint and not body:
					print("found single joint")	
					print("scale joint limits")
					yLimit = joint.getYLimit()
					zLimit = joint.getZLimit()

					step = 5
					vector = getModifiedVector(Engine,EngineModule,step)

					oldY = yLimit
					oldZ = zLimit

					yLimit += vector.x
					zLimit += vector.y

					if Engine.isKeyDown(EngineModule.Keys.K_0):
						yLimit = 0
						zLimit = 0

					if yLimit <= step:
						yLimit = 0
					if zLimit <= step:
						zLimit = 0

					print("changed limits: y: " + str(oldY) + "-" + 
						str(yLimit) + " z: " + str(oldZ) + "-" + 
						str(zLimit))

					joint.setLimits(yLimit,zLimit)



			else:
				print("found too many connected joints and bodies")



	if key == EngineModule.Keys.K_U:
		print("select next joint")
		sel = selection.get()[:]
		while len(sel)>0:
			o = sel.pop()
			body = None
			joint = None
			tooMany = False
			if o.isJoint():
				body,tooMany = findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				# select next physic shape

			elif o.isGuiShape():
				print("found guishape")

			if not tooMany:
				if body and joint:
					#print("found body and joint")	
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
				elif body and not joint:
					#print("found single body")	
					if body.howManyJoints() > 0:
						j = body.getJoint(0)
						selection.add(j)
				elif joint and not body:
					pass
					#print("found single joint")	
			else:
				print("found too many connected joints and bodies")







	if key == EngineModule.Keys.K_DELETE:
		print("deleting selection")
		selectedObjects = selection.get()[:]
		selection.clear()
		#for o in selection.get()[:]:
		while len(selectedObjects) > 0:
			o = selectedObjects.pop()
			#for o in selectedObjects:
			print("object: " + str(o))
			if o.isBox():
				print("is box")
				Engine.deleteObject(o)		
				print("done")
		print("done--")

	if key == EngineModule.Keys.K_X:
		print("edit body joint pos,size")
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			jointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
			bodySize = body.getSize()
			print("body joint size pos: " + str(jointPos))
			print("body size: " + str(bodySize))

			#jointPos = EngineModule.Vec3(-153,3,90) 
			#bodySize = EngineModule.Vec3(5,2.9,1.6) 

			bodyjoint.bodyJointScaleJointPos(body,joint, jointPos)
			bodyjoint.bodyJointScaleBody(body,joint, bodySize )

			jointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
			bodySize = body.getSize()
			print("body joint size pos: " + str(jointPos))
			print("body size: " + str(bodySize))

	if key == EngineModule.Keys.K_B:
		print("edit body joint pos")
		body,joint = bodyjoint.getBodyJoint(selection.get())
		if ((body and joint) and bodyjoint.isBodyJointConnected(body,joint)):
			jointPos = bodyjoint.getBodyJointAnchorPos(body,joint)
			bodySize = body.getSize()
			print("body joint pos: " + str(jointPos))
			print("body size: " + str(bodySize))

			#jointPos = EngineModule.Vec3(-153,3,90) 
			#jointPos.x *= 1.1
			#bodySize = EngineModule.Vec3(15,1,15)
			#jointPos.y *= 0.9

			bodyjoint.setBodyJointAnchorPos(body,joint,jointPos)
			body.setSize(bodySize)

			jointPos = bodyjoint.getBodyJointAnchorPos(body,joint)
			bodySize = body.getSize()
			print("body joint pos: " + str(jointPos))
			print("body size: " + str(bodySize))

	if key == EngineModule.Keys.K_M:
        #void        dsetContactDistance(float);
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)

			if o.isJoint():
				j = o.isJoint()

				if Engine.isKeyDown(EngineModule.Keys.K_1):
					j.setMotorOn()

				if Engine.isKeyDown(EngineModule.Keys.K_2):
					j.setMotorOff()

				if Engine.isKeyDown(EngineModule.Keys.K_3):
					exp = 38
					spring = (10 ** exp) * 1.4
					damping = (10 ** exp) * 1
					#spring = (10 ** 10) * 1
					#damping = (10 ** 8) * 1

					j.dsetMotorSpring(spring)
					j.dsetMotorDamping(damping)
					j.dsetMotorAccel(True)
				if Engine.isKeyDown(EngineModule.Keys.K_4):
					spring = (10 ** 1) * 1
					damping = (10 ** 1) * 4
					spring = 2
					damping = 5
					j.dsetMotorSpring(spring)
					j.dsetMotorDamping(damping)
					j.dsetMotorAccel(True)

				if Engine.isKeyDown(EngineModule.Keys.K_5):
					spring = (10 ** 15) * 1
					damping = (10 ** 14) * 1
					damping = (10 ** 13) * 1
					j.dsetMotorSpring(spring)
					j.dsetMotorDamping(damping)
					j.dsetMotorAccel(False)

