"""edit:
	#x: work on body,joint: sizepos with all joints
	#b: work on body,joint: singual anchor pos 
	m: joint motor
		1:on 2:off 3:set power
	r: rotate
	t: translate
	y: scale
	u: select next
"""

import bodyjoint
import helpers

def storeOperation(text):
	f = open("operations.txt","a")
	f.write(text + "\n")
	f.close()

def storeBodyJointOperation(EngineModule,method,body,joint,value):
	text = method + "(Engine,EngineModule,"
	text += "bodyName='" + body.getName() + "'"
	text += ",jointName='" + joint.getName() + "'"
	if type(value) == EngineModule.Vec3:
		text += ",vector=EngineModule.Vec3(" + str(value) + "))"
	if type(value) == EngineModule.Quat:
		text += ",quaternion=EngineModule.Quat(" + str(value) + "))"
	storeOperation(text)

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
				body,tooMany = helpers.findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = helpers.findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				print("rotate shape")
				angle = helpers.getModifiedQuaternion(Engine,EngineModule,5)
				newValue = o.getLocalOrientation() * angle
				if Engine.isKeyDown(EngineModule.Keys.K_0):
					newValue = EngineModule.Quat()
				o.setLocalOrientation(newValue)

				text = "rotatePhysicShape(Engine,EngineModule"
				text += ",bodyName='" + o.getActor().getName() + "'"
				text += ",shapeName='" + o.getName() + "'"
				text += ",quaternion=EngineModule.Quat(" + str(newValue) + ")"
				text += ")"
				helpers.storeOperation(text)

			elif o.isGuiShape():
				print("found guishape")

			if not tooMany:
				if body and joint:
					print("found body and joint")	
					print("rotate joint orientation")
					angle = helpers.getModifiedQuaternion(Engine,EngineModule,10)
					bodyNum = bodyjoint.howIsBodyConnectedToJoint(body,joint)
					if bodyNum == 1:
						newOri = joint.getAnchor1Orientation() * angle
						joint.setAnchor1Orientation(newOri)
						if Engine.isKeyDown(EngineModule.Keys.K_0):
							joint.setAnchor1Orientation(EngineModule.Quat())
						#TODO take care of all other joints
					if bodyNum == 2:
						newOri = joint.getAnchor2Orientation() * angle
						joint.setAnchor2Orientation(newOri)
						if Engine.isKeyDown(EngineModule.Keys.K_0):
							joint.setAnchor2Orientation(EngineModule.Quat())
						#TODO take care of all other joints

				elif body and not joint:
					print("found single body")	
					print("rotate body")
					angle = helpers.getModifiedQuaternion(Engine,EngineModule,5)
					body.setOrientation(body.getOrientation() * angle)

					if Engine.isKeyDown(EngineModule.Keys.K_0):
						body.setOrientation(EngineModule.Quat())

				elif joint and not body:
					print("found single joint")	
					print("rotate joint motor target")
					angle = helpers.getModifiedQuaternion(Engine,EngineModule,10)
					motorTarget = joint.getMotorTarget() * angle
					if Engine.isKeyDown(EngineModule.Keys.K_0):
						print("reset motor target")
						motorTarget = EngineModule.Quat()
					joint.setMotorTarget(motorTarget)
					if joint.isMotorOn():
						joint.setMotorOn()
					text = "setMotorTarget(Engine,EngineModule,"
					text += "jointName='" + joint.getName() + "'"
					text += ",quaternion=EngineModule.Quat(" + str(motorTarget) + "))"
					storeOperation(text)

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
				body,tooMany = helpers.findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = helpers.findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				print("move localy")
				vector = helpers.getModifiedVector(Engine,EngineModule,1)
				vector = o.getLocalOrientation() * vector
				newValue = o.getLocalPosition() + vector 
				if Engine.isKeyDown(EngineModule.Keys.K_0):
					newValue = EngineModule.Vec3()
				o.setLocalPosition(newValue)

				text = "movePhysicShape(Engine,EngineModule"
				text += ",bodyName='" + o.getActor().getName() + "'"
				text += ",shapeName='" + o.getName() + "'"
				text += ",position=EngineModule.Vec3(" + str(newValue) + ")"
				text += ")"
				helpers.storeOperation(text)

			elif o.isGuiShape():
				print("found guishape")

			if not tooMany:
				if body and joint:
					print("found body and joint")	
					print("move joint pos in rel to body")
					vector = helpers.getModifiedVector(Engine,EngineModule,0.1)
					currentJointPos = bodyjoint.getBodyJointAnchorSizePos(body,joint)
					newValue = currentJointPos + vector
					bodyjoint.bodyJointScaleJointPos(body,joint,newValue)
					storeBodyJointOperation(EngineModule,"bodyJointScaleJointPos",body,joint,newValue)

				elif body and not joint:
					print("found single body")	
					print("move globaly")
					vector = helpers.getModifiedVector(Engine,EngineModule,20)
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
				body,tooMany = helpers.findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = helpers.findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				print("scale localy")
				vector = helpers.getModifiedVector(Engine,EngineModule,0.1)
				newValue = o.getLocalSize() * (EngineModule.Vec3(1,1,1) + vector)
				o.setLocalSize(newValue)

				text = "scalePhysicShape(Engine,EngineModule"
				text += ",bodyName='" + o.getActor().getName() + "'"
				text += ",shapeName='" + o.getName() + "'"
				text += ",size=EngineModule.Vec3(" + str(newValue) + ")"
				text += ")"
				helpers.storeOperation(text)

			elif o.isGuiShape():
				print("found guishape")

			if not tooMany:
				if body and joint:
					print("found body and joint")	
					print("scale body with regards of joints")
					vector = helpers.getModifiedVector(Engine,EngineModule,0.1)
					newValue = body.getSize() * (EngineModule.Vec3(1,1,1) + vector)
					bodyjoint.bodyJointScaleBody(body,joint,newValue)
					storeBodyJointOperation(EngineModule,"bodyJointScaleBody",body,joint,newValue)

				elif body and not joint:
					print("found single body")	
					print("scale")
					vector = helpers.getModifiedVector(Engine,EngineModule,0.1)
					body.setSize(body.getSize() * (EngineModule.Vec3(1,1,1) + vector))

				elif joint and not body:
					print("found single joint")	
					print("scale joint limits")
					yLimit = joint.getYLimit()
					zLimit = joint.getZLimit()

					step = 5
					vector = helpers.getModifiedVector(Engine,EngineModule,step)

					oldY = yLimit
					oldZ = zLimit

					yLimit += vector.x
					zLimit += vector.y

					if Engine.isKeyDown(EngineModule.Keys.K_0):
						yLimit = 0
						zLimit = 0

					if yLimit <= 0:
						yLimit = 0
					if zLimit <= 0:
						zLimit = 0

					print("set limits: y: " + str(yLimit) + " z: " + str(zLimit))

					text = "setLimits(Engine,EngineModule,"
					text += "jointName='" + joint.getName() + "'"
					text += ",y=" + str(yLimit) + ",z=" + str(zLimit) + ")"
					storeOperation(text)

					joint.setLimits(yLimit,zLimit)



			else:
				print("found too many connected joints and bodies")



	if key == EngineModule.Keys.K_U:
		print("select next object")
		sel = selection.get()[:]
		while len(sel)>0:
			o = sel.pop()
			body = None
			joint = None
			tooMany = False
			if o.isJoint():
				body,tooMany = helpers.findBodyForJoint(Engine,EngineModule,sel,o)
				joint = o
			elif o.isActor():
				joint,tooMany = helpers.findJointForBody(Engine,EngineModule,sel,o)
				body = o
			elif o.isPhysicShape():
				print("found physicshape")
				# select next physic shape
				body = o.getActor()
				numShapes = body.howManyPhysicShapes()
				if numShapes > 1:
					print("has shapes: " + str(numShapes))
					selection.clear()
					currentIndex = 0
					for i in range(0,numShapes):
						shape = body.getPhysicShapeByIndex(i)
						if shape.getName() == o.getName():
							currentIndex = i
							break
					newIndex = currentIndex + 1
					if newIndex == numShapes:
						newIndex = 0
					print("current index: " + str(currentIndex))
					print("next index: " + str(newIndex))
					selection.add(body.getPhysicShapeByIndex(newIndex))

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
					if Engine.isKeyDown(EngineModule.Keys.K_1):
						if body.howManyJoints() > 0:
							j = body.getJoint(0)
							selection.add(j)
					if Engine.isKeyDown(EngineModule.Keys.K_2):
						if body.howManyPhysicShapes() > 0:
							shape = body.getPhysicShapeByIndex(0)
							selection.clear()
							selection.add(shape)
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


	"""
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
			"""

	if key == EngineModule.Keys.K_M:
		exp = 15
		spring = (10 ** exp) * 1.2
		damping = (10 ** exp) * 1.0

		print("set motor on/off power")
		if len(selection.get()) > 0:
			for o in selection.get():
				if o.isJoint():
					j = o.isJoint()
					if Engine.isKeyDown(EngineModule.Keys.K_1):
						j.setMotorOn()

					if Engine.isKeyDown(EngineModule.Keys.K_2):
						j.setMotorOff()
		else:
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

						j.dsetMotorSpring(spring)
						j.dsetMotorDamping(damping)
						j.dsetMotorAccel(True)

