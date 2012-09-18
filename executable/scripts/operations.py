"""operations:
	o: run operations
"""

import bodyjoint
import helpers

import datetime

def storeOperation(text):
	f = open("operations.txt","a")
	f.write(text + "\n")
	f.close()

def getMesh(Engine,EngineModule):
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isMesh():
			return o
	return None

def getJoint(Engine,EngineModule,jointName):
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isJoint():
			if o.getName() == jointName:
				return o
	return None

def getBodyFromName(Engine,EngineModule,bodyName):
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isActor():
			if o.getName() == bodyName:
				return o
	return None

def getShapeFromName(Engine,EngineModule,bodyName,shapeName):
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isPhysicShape():
			if o.getActor().getName() == bodyName:
				if o.getName() == shapeName:
					return o
	return None

def setBodyJointAnchorPos(Engine,EngineModule,bodyName,jointName,vector):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#	body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	if body and joint:
		bodyjoint.setBodyJointAnchorPos(body,joint,vector)

def bodyJointScaleJointPos(Engine,EngineModule,bodyName,jointName,vector):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#	body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	if body and joint:
		bodyjoint.bodyJointScaleJointPos(body,joint,vector)

def bodyJointScaleBody(Engine,EngineModule,bodyName,jointName,vector):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#	body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	if body and joint:
		bodyjoint.bodyJointScaleBody(body,joint,vector)

def setMotorTarget(Engine,EngineModule,jointName,quaternion):
	joint = getJoint(Engine,EngineModule,jointName)
	if joint:
		joint.setMotorTarget(quaternion)

def setLimits(Engine,EngineModule,jointName,y,z):
	joint = getJoint(Engine,EngineModule,jointName)
	if joint:
		joint.setLimits(y,z)

def bodyJointRotateJoint(Engine,EngineModule,bodyName,jointName,quaternion):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	if body and joint:
		bodyjoint.bodyJointRotateJoint(body,joint,quaternion)

def bodyJointAbsoluteRotation(Engine,EngineModule,bodyName,jointName,quaternion):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#	body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	if body and joint:
		bodyNum = bodyjoint.howIsBodyConnectedToJoint(body,joint)
		if bodyNum == 1:
			joint.setAnchor1Orientation(quaternion)
		if bodyNum == 2:
			joint.setAnchor2Orientation(quaternion)

def bodyOrientation(Engine,EngineModule,bodyName,quaternion):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#	body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		body.setOrientation(quaternion)

def bodyPosition(Engine,EngineModule,bodyName,vector):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#	body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		body.setPosition(vector)

def bodySize(Engine,EngineModule,bodyName,vector):
	#mesh = getMesh(Engine,EngineModule)
	#if mesh:
	#	body = mesh.getBodyOfBoneName(bodyName)
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		body.setSize(vector)

def addBox(Engine,EngineModule,bodyName,shapeName,size,r,g,b,a):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		shape = body.addBox(size)
		shape.setColour(r,g,b,a)
		shape.setName(shapeName)

def addCapsule(Engine,EngineModule,bodyName,shapeName,size,r,g,b,a):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		shape = body.addCapsule(size)
		shape.setColour(r,g,b,a)
		shape.setName(shapeName)

def addSphere(Engine,EngineModule,bodyName,shapeName,size,r,g,b,a):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		shape = body.addSphere(size)
		shape.setColour(r,g,b,a)
		shape.setName(shapeName)

def movePhysicShape(Engine,EngineModule,bodyName,shapeName,position):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		shape = getShapeFromName(Engine,EngineModule,bodyName,shapeName)
		if shape:
			shape.setLocalPosition(position)

def scalePhysicShape(Engine,EngineModule,bodyName,shapeName,size):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		shape = getShapeFromName(Engine,EngineModule,bodyName,shapeName)
		if shape:
			shape.setLocalSize(size)

def rotatePhysicShape(Engine,EngineModule,bodyName,shapeName,quaternion):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	if body:
		shape = getShapeFromName(Engine,EngineModule,bodyName,shapeName)
		if shape:
			shape.setLocalOrientation(quaternion)



def keyPressed(Engine,EngineModule,key,selection,objects):
	if key == EngineModule.Keys.K_O:
		if Engine.isKeyDown(EngineModule.Keys.K_1):
			print("write time to operations.txt")
			storeOperation(str(datetime.datetime.now()))
		elif Engine.isKeyDown(EngineModule.Keys.K_0):
			print("clear operations.txt")
			f = open("operations.txt","w")
			f.write("\n")
			f.close()
		else:
			runOperations(Engine,EngineModule)


def runOperations(Engine,EngineModule):





	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))


	bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-middle-high-l',jointName='finger-middle-high-l-joint',vector=EngineModule.Vec3(2.276066542,0.321195006,0.321195006))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-ring-high-l',jointName='finger-ring-high-l-joint',vector=EngineModule.Vec3(2.195024252,0.309758455,0.309758455))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-little-high-l',jointName='finger-little-high-l-joint',vector=EngineModule.Vec3(1.836014986,0.313505679,0.313505679))
	bodyJointScaleBody(Engine,EngineModule,bodyName='thumb-high-l',jointName='thumb-high-l-joint',vector=EngineModule.Vec3(1.722578645,0.323549688,0.294136077))

	setLimits(Engine,EngineModule,jointName='finger-index-high-l-joint',y=60.9999704361,z=0.999998950958)
	setLimits(Engine,EngineModule,jointName='finger-middle-high-l-joint',y=50.9999847412,z=0.99999961853)
	setLimits(Engine,EngineModule,jointName='finger-ring-high-l-joint',y=50.9999847412,z=0.99999961853)
	setLimits(Engine,EngineModule,jointName='finger-little-high-l-joint',y=50.9999847412,z=0.99999961853)
	setLimits(Engine,EngineModule,jointName='thumb-high-l-joint',y=20.9999895096,z=20.9999966621)

	setMotorTarget(Engine,EngineModule,jointName='finger-index-high-l-joint',quaternion=EngineModule.Quat(0.996194839,0.000000000,0.087155752,0.000000000))



	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))

	bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-middle-high-r',jointName='finger-middle-high-r-joint',vector=EngineModule.Vec3(2.276066542,0.321195006,0.321195006))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-ring-high-r',jointName='finger-ring-high-r-joint',vector=EngineModule.Vec3(2.195024252,0.309758455,0.309758455))
	bodyJointScaleBody(Engine,EngineModule,bodyName='finger-little-high-r',jointName='finger-little-high-r-joint',vector=EngineModule.Vec3(1.836014986,0.313505679,0.313505679))
	bodyJointScaleBody(Engine,EngineModule,bodyName='thumb-high-r',jointName='thumb-high-r-joint',vector=EngineModule.Vec3(1.722578645,0.323549688,0.294136077))

	setLimits(Engine,EngineModule,jointName='finger-index-high-r-joint',y=60.9999704361,z=0.999998950958)
	setLimits(Engine,EngineModule,jointName='finger-middle-high-r-joint',y=50.9999847412,z=0.99999961853)
	setLimits(Engine,EngineModule,jointName='finger-ring-high-r-joint',y=50.9999847412,z=0.99999961853)
	setLimits(Engine,EngineModule,jointName='finger-little-high-r-joint',y=50.9999847412,z=0.99999961853)
	setLimits(Engine,EngineModule,jointName='thumb-high-r-joint',y=20.9999895096,z=20.9999966621)

	setMotorTarget(Engine,EngineModule,jointName='finger-index-high-r-joint',quaternion=EngineModule.Quat(0.996194839,0.000000000,0.087155752,0.000000000))









	setLimits(Engine,EngineModule,jointName='hand-r-joint',y=30.9999895096,z=15.9999980927)

	bodyJointScaleBody(Engine,EngineModule,bodyName='hand-l',jointName='hand-l-joint',vector=EngineModule.Vec3(2.313906908,1.815508246,0.636324406))
	bodyJointScaleBody(Engine,EngineModule,bodyName='hand-r',jointName='hand-r-joint',vector=EngineModule.Vec3(2.313906908,1.815508246,0.636324406))



	bodyJointScaleJointPos(Engine,EngineModule,bodyName='shoulder-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(1.233332872,0.000000527,-0.000006907))
	bodyJointScaleBody(Engine,EngineModule,bodyName='shoulder-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(2.196150780,2.018250704,1.834773302))
	setLimits(Engine,EngineModule,jointName='shoulder-l-joint',y=15,z=15)

	bodyJointScaleJointPos(Engine,EngineModule,bodyName='shoulder-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(1.233332872,0.000000527,-0.000006907))
	bodyJointScaleBody(Engine,EngineModule,bodyName='shoulder-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(2.196150780,2.018250704,1.834773302))
	setLimits(Engine,EngineModule,jointName='shoulder-r-joint',y=15,z=15)


	bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(9.539100647,2.297487020,2.088624477))
	bodyJointScaleBody(Engine,EngineModule,bodyName='larm-l',jointName='larm-l-joint',vector=EngineModule.Vec3(7.937189579,1.569214463,1.426558614))

	setLimits(Engine,EngineModule,jointName='uarm-l-joint',y=70,z=55)

	bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(9.443709373,2.274512053,2.527235746))
	bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))


	bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(9.539100647,2.297487020,2.088624477))
	bodyJointScaleBody(Engine,EngineModule,bodyName='larm-r',jointName='larm-r-joint',vector=EngineModule.Vec3(7.937189579,1.569214463,1.426558614))

	setLimits(Engine,EngineModule,jointName='uarm-r-joint',y=70,z=55)

	bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(9.443709373,2.274512053,2.527235746))
	bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))








	movePhysicShape(Engine,EngineModule,bodyName='head',shapeName='1',position=EngineModule.Vec3(0.129410282,0.000000000,-0.482966751))
	addCapsule(Engine,EngineModule,bodyName='head',shapeName='2',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)

	rotatePhysicShape(Engine,EngineModule,bodyName='head',shapeName='2',quaternion=EngineModule.Quat(0.996195555,0.000000000,-0.087155819,0.000000000))
	scalePhysicShape(Engine,EngineModule,bodyName='head',shapeName='2',size=EngineModule.Vec3(2.357948065,4.594974041,4.177248955))
	movePhysicShape(Engine,EngineModule,bodyName='head',shapeName='2',position=EngineModule.Vec3(0.781421125,0.000000000,2.568423510))

	bodyJointScaleBody(Engine,EngineModule,bodyName='head',jointName='head-joint',vector=EngineModule.Vec3(2.282495260,5.959090710,5.959090710))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='head',jointName='head-joint',vector=EngineModule.Vec3(-2.100000381,-0.000000477,0.100000001))
	rotatePhysicShape(Engine,EngineModule,bodyName='head',shapeName='1',quaternion=EngineModule.Quat(0.991445959,0.000000000,-0.130526364,0.000000000))
	setLimits(Engine,EngineModule,jointName='head-joint',y=20,z=20)

	bodyJointScaleBody(Engine,EngineModule,bodyName='neck',jointName='head-joint',vector=EngineModule.Vec3(2.449944496,2.220075846,2.018250704))
	bodyJointScaleBody(Engine,EngineModule,bodyName='neck',jointName='neck-joint',vector=EngineModule.Vec3(2.182900190,2.954921246,2.954921246))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='neck',jointName='head-joint',vector=EngineModule.Vec3(1.333341599,0.000000000,-0.000001192))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='neck',jointName='neck-joint',vector=EngineModule.Vec3(-2.429821730,0.000000216,-0.200001240))
	setLimits(Engine,EngineModule,jointName='neck-joint',y=15,z=10)

	bodyJointScaleBody(Engine,EngineModule,bodyName='cheast',jointName='cheast-joint',vector=EngineModule.Vec3(4.065469742,7.931550026,4.432381153))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='cheast',jointName='cheast-joint',vector=EngineModule.Vec3(-0.999999762,0.000001907,0.700000048))
	rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='1',quaternion=EngineModule.Quat(0.996194720,0.000000000,0.087155759,0.000000000))
	setLimits(Engine,EngineModule,jointName='cheast-joint',y=15,z=10)

	bodyJointScaleBody(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(5.732460499,6.996340275,4.924868107))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(-1.000001788,0.000001907,0.199997157))
	rotatePhysicShape(Engine,EngineModule,bodyName='breast',shapeName='1',quaternion=EngineModule.Quat(0.984808385,0.000000000,-0.173648298,0.000000000))
	setLimits(Engine,EngineModule,jointName='breast-joint',y=15,z=10)

	bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='cheast-joint',vector=EngineModule.Vec3(3.095424891,3.250413418,2.686291933))
	bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(3.670929193,6.334136963,3.933000565))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='belly',jointName='cheast-joint',vector=EngineModule.Vec3(1.033345580,0.000000641,0.699999869))
	bodyJointScaleJointPos(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(-1.293976188,0.000000934,0.499999791))
	rotatePhysicShape(Engine,EngineModule,bodyName='belly',shapeName='1',quaternion=EngineModule.Quat(0.991444886,0.000000000,0.130526215,0.000000000))
	setLimits(Engine,EngineModule,jointName='belly-joint',y=15,z=10)

	movePhysicShape(Engine,EngineModule,bodyName='root',shapeName='1',position=EngineModule.Vec3(2.000000000,0.000000000,2.000000000))
	bodySize(Engine,EngineModule,bodyName='root',vector=EngineModule.Vec3(4.399131775,8.297108650,5.840505600))

	addCapsule(Engine,EngineModule,bodyName='root',shapeName='2',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
	scalePhysicShape(Engine,EngineModule,bodyName='root',shapeName='2',size=EngineModule.Vec3(1.977985501,4.594974041,4.177248955))
	movePhysicShape(Engine,EngineModule,bodyName='root',shapeName='2',position=EngineModule.Vec3(4.181388378,3.500116587,3.928447247))
	rotatePhysicShape(Engine,EngineModule,bodyName='root',shapeName='2',quaternion=EngineModule.Quat(0.779888928,0.000000063,0.625927150,-0.000000022))

	addCapsule(Engine,EngineModule,bodyName='root',shapeName='3',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
	scalePhysicShape(Engine,EngineModule,bodyName='root',shapeName='3',size=EngineModule.Vec3(1.977985501,4.594974041,4.177248955))
	movePhysicShape(Engine,EngineModule,bodyName='root',shapeName='3',position=EngineModule.Vec3(4.181388378,-3.500116587,3.928447247))
	rotatePhysicShape(Engine,EngineModule,bodyName='root',shapeName='3',quaternion=EngineModule.Quat(0.779888928,0.000000063,0.625927150,-0.000000022))



	bodyJointScaleBody(Engine,EngineModule,bodyName='uleg-l',jointName='uleg-l-joint',vector=EngineModule.Vec3(11.259112358,3.363751173,3.057955503))
	bodyJointScaleBody(Engine,EngineModule,bodyName='uleg-r',jointName='uleg-r-joint',vector=EngineModule.Vec3(11.259112358,3.363751173,3.057955503))

	bodyJointScaleBody(Engine,EngineModule,bodyName='lleg-l',jointName='lleg-l-joint',vector=EngineModule.Vec3(13.635429382,2.297487020,2.088624477))
	bodyJointScaleBody(Engine,EngineModule,bodyName='lleg-r',jointName='lleg-r-joint',vector=EngineModule.Vec3(13.635429382,2.297487020,2.088624477))

	setLimits(Engine,EngineModule,jointName='uleg-l-joint',y=60,z=60)
	setLimits(Engine,EngineModule,jointName='lleg-l-joint',y=84,z=10)
	setMotorTarget(Engine,EngineModule,jointName='lleg-l-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))
	bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='lleg-l',jointName='lleg-l-joint',quaternion=EngineModule.Quat(0.939692855,0.000000000,-0.342020273,0.000000000))

	setLimits(Engine,EngineModule,jointName='uleg-r-joint',y=60,z=60)
	setLimits(Engine,EngineModule,jointName='lleg-r-joint',y=85,z=10)
	setMotorTarget(Engine,EngineModule,jointName='lleg-r-joint',quaternion=EngineModule.Quat(0.939692795,0.000000000,-0.342020273,0.000000000))
	bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='lleg-r',jointName='lleg-r-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))






	setLimits(Engine,EngineModule,jointName='foot-l-joint',y=50,z=50)
	setLimits(Engine,EngineModule,jointName='foot-r-joint',y=50,z=50)

	bodyJointScaleBody(Engine,EngineModule,bodyName='foot-l',jointName='foot-l-joint',vector=EngineModule.Vec3(4.643489361,1.132517815,2.088624477))
	bodyJointScaleBody(Engine,EngineModule,bodyName='foot-r',jointName='foot-r-joint',vector=EngineModule.Vec3(4.643489361,1.132517815,2.088624477))

	rotatePhysicShape(Engine,EngineModule,bodyName='foot-l',shapeName='1',quaternion=EngineModule.Quat(0.980786443,0.000000000,0.000000000,-0.195090607))
	rotatePhysicShape(Engine,EngineModule,bodyName='foot-r',shapeName='1',quaternion=EngineModule.Quat(0.980786443,0.000000000,0.000000000,0.195090607))

	scalePhysicShape(Engine,EngineModule,bodyName='foot-r',shapeName='1',size=EngineModule.Vec3(5.107838631,1.132517815,2.088624477))
	movePhysicShape(Engine,EngineModule,bodyName='foot-r',shapeName='1',position=EngineModule.Vec3(-0.732535958,-0.844623208,0.000000000))

	scalePhysicShape(Engine,EngineModule,bodyName='foot-l',shapeName='1',size=EngineModule.Vec3(5.107838631,1.132517815,2.088624477))
	movePhysicShape(Engine,EngineModule,bodyName='foot-l',shapeName='1',position=EngineModule.Vec3(-0.732535958,0.844623208,0.000000000))

	rotatePhysicShape(Engine,EngineModule,bodyName='foot-r',shapeName='1',quaternion=EngineModule.Quat(0.979853213,-0.008509734,0.042781331,0.194904968))
	rotatePhysicShape(Engine,EngineModule,bodyName='foot-l',shapeName='1',quaternion=EngineModule.Quat(0.979853153,0.008509736,0.042781319,-0.194904953))



def runOperations2(Engine,EngineModule):

	setBodyJointAnchorPos(Engine,EngineModule,bodyName='foot-r',jointName='foot-ground-r',vector=EngineModule.Vec3(4.643490314,1.399999857,0.000001907))
	setBodyJointAnchorPos(Engine,EngineModule,bodyName='foot-l',jointName='foot-ground-l',vector=EngineModule.Vec3(4.643490314,-1.399999857,0.000001907))

	setBodyJointAnchorPos(Engine,EngineModule,bodyName='ground',jointName='foot-ground-l',vector=EngineModule.Vec3(3.708251953,1.290204048,-4.486923218))
	setBodyJointAnchorPos(Engine,EngineModule,bodyName='ground',jointName='foot-ground-r',vector=EngineModule.Vec3(-3.713666916,1.294058800,-4.488095760))

	#setBodyJointAnchorPos(Engine,EngineModule,bodyName='ground',jointName='foot-ground-r',vector=EngineModule.Vec3(-5.813664913,1.294058800,-4.488095760))
	#setBodyJointAnchorPos(Engine,EngineModule,bodyName='ground',jointName='foot-ground-l',vector=EngineModule.Vec3(5.408250332,1.290204048,-4.486923218))

	setLimits(Engine,EngineModule,jointName='foot-ground-l',y=40,z=123.0)
	setLimits(Engine,EngineModule,jointName='foot-ground-r',y=40,z=123.0)

	setLimits(Engine,EngineModule,jointName='foot-ground-l',y=4,z=123.0)
	setLimits(Engine,EngineModule,jointName='foot-ground-r',y=4,z=123.0)

	setLimits(Engine,EngineModule,jointName='foot-ground-l',y=10,z=123.0)
	setLimits(Engine,EngineModule,jointName='foot-ground-r',y=10,z=123.0)

