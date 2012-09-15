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


def bodyJointScaleJointPos(Engine,EngineModule,bodyName,jointName,vector):
	mesh = getMesh(Engine,EngineModule)
	body = mesh.getBodyOfBoneName(bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	bodyjoint.bodyJointScaleJointPos(body,joint,vector)

def bodyJointScaleBody(Engine,EngineModule,bodyName,jointName,vector):
	mesh = getMesh(Engine,EngineModule)
	body = mesh.getBodyOfBoneName(bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	bodyjoint.bodyJointScaleBody(body,joint,vector)

def setMotorTarget(Engine,EngineModule,jointName,quaternion):
	joint = getJoint(Engine,EngineModule,jointName)
	joint.setMotorTarget(quaternion)

def setLimits(Engine,EngineModule,jointName,y,z):
	joint = getJoint(Engine,EngineModule,jointName)
	joint.setLimits(y,z)


def bodyJointAbsoluteRotation(Engine,EngineModule,bodyName,jointName,quaternion):
	mesh = getMesh(Engine,EngineModule)
	body = mesh.getBodyOfBoneName(bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	bodyNum = bodyjoint.howIsBodyConnectedToJoint(body,joint)
	if bodyNum == 1:
		joint.setAnchor1Orientation(quaternion)
	if bodyNum == 2:
		joint.setAnchor2Orientation(quaternion)

def getShapeFromName(Engine,EngineModule,bodyName,shapeName):
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isPhysicShape():
			if o.getActor().getName() == bodyName:
				if o.getName() == shapeName:
					return o
	return None

def addBox(Engine,EngineModule,bodyName,shapeName,size,r,g,b,a):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	shape = body.addBox(size)
	shape.setColour(r,g,b,a)
	shape.setName(shapeName)

def addCapsule(Engine,EngineModule,bodyName,shapeName,size,r,g,b,a):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	shape = body.addCapsule(size)
	shape.setColour(r,g,b,a)
	shape.setName(shapeName)

def addSphere(Engine,EngineModule,bodyName,shapeName,size,r,g,b,a):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	shape = body.addSphere(size)
	shape.setColour(r,g,b,a)
	shape.setName(shapeName)

def movePhysicShape(Engine,EngineModule,bodyName,shapeName,position):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	shape = getShapeFromName(Engine,EngineModule,bodyName,shapeName)
	shape.setLocalPosition(position)

def scalePhysicShape(Engine,EngineModule,bodyName,shapeName,size):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	shape = getShapeFromName(Engine,EngineModule,bodyName,shapeName)
	shape.setLocalSize(size)

def rotatePhysicShape(Engine,EngineModule,bodyName,shapeName,quaternion):
	body = getBodyFromName(Engine,EngineModule,bodyName)
	shape = getShapeFromName(Engine,EngineModule,bodyName,shapeName)
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


			bodyJointScaleBody(Engine,EngineModule,bodyName='root',jointName='belly-joint',vector=EngineModule.Vec3(2.373790503,5.363181591,2.779959440))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(-3.033333778,0.000001589,-0.000000199))
			bodyJointScaleBody(Engine,EngineModule,bodyName='hand-l',jointName='hand-l-joint',vector=EngineModule.Vec3(1.436753869,1.364018083,0.359188467))
			bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(1.312762141,1.516341448,1.378492236))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uleg-l',jointName='uleg-l-joint',vector=EngineModule.Vec3(11.259112358,1.898749590,1.726135969))

			bodyJointScaleBody(Engine,EngineModule,bodyName='hand-r',jointName='hand-r-joint',vector=EngineModule.Vec3(1.436753869,1.364018083,0.359188467))
			bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(1.312762141,1.516341448,1.378492236))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uleg-r',jointName='uleg-r-joint',vector=EngineModule.Vec3(11.259112358,1.898749590,1.726135969))




			#-----

			bodyJointScaleJointPos(Engine,EngineModule,bodyName='belly',jointName='cheast-joint',vector=EngineModule.Vec3(1.333345652,0.000000646,-0.000000156))
			bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='cheast-joint',vector=EngineModule.Vec3(2.558202267,1.516341448,1.378492236))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='belly',jointName='cheast-joint',vector=EngineModule.Vec3(1.033345580,0.000000646,-0.000000156))
			bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='cheast-joint',vector=EngineModule.Vec3(3.095424891,3.250413418,2.686291933))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='belly',jointName='cheast-joint',vector=EngineModule.Vec3(1.033345580,0.000000641,0.699999869))

			bodyJointScaleBody(Engine,EngineModule,bodyName='cheast',jointName='cheast-joint',vector=EngineModule.Vec3(4.148015022,5.959090710,4.070138931))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='cheast',jointName='cheast-joint',vector=EngineModule.Vec3(-0.999999762,0.000001907,0.600000024))
			bodyJointScaleBody(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(4.306881905,3.363751173,3.363751173))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(-1.000001788,0.000001907,0.599997103))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='neck',jointName='head-joint',vector=EngineModule.Vec3(1.333341599,0.000000000,-0.000001192))
			bodyJointScaleBody(Engine,EngineModule,bodyName='neck',jointName='head-joint',vector=EngineModule.Vec3(2.449944496,2.220075846,2.018250704))
			bodyJointScaleBody(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(4.306881905,5.417355061,3.363751173))

			bodyJointScaleJointPos(Engine,EngineModule,bodyName='shoulder-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(1.233332872,0.000000527,-0.000006907))
			bodyJointScaleBody(Engine,EngineModule,bodyName='shoulder-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(2.196150780,2.018250704,1.834773302))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(9.539100647,1.898749590,1.726135969))
			bodyJointScaleBody(Engine,EngineModule,bodyName='larm-l',jointName='larm-l-joint',vector=EngineModule.Vec3(7.937189579,1.296871424,1.178974032))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uleg-l',jointName='uleg-l-joint',vector=EngineModule.Vec3(11.259112358,3.363751173,3.057955503))
			bodyJointScaleBody(Engine,EngineModule,bodyName='lleg-l',jointName='lleg-l-joint',vector=EngineModule.Vec3(13.635429382,2.088624477,1.898749590))
			bodyJointScaleBody(Engine,EngineModule,bodyName='foot-l',jointName='foot-l-joint',vector=EngineModule.Vec3(2.883241415,1.426558614,1.178974032))
			bodyJointScaleBody(Engine,EngineModule,bodyName='toes-l',jointName='toes-l-joint',vector=EngineModule.Vec3(2.018269062,1.726135969,0.732050061))
			bodyJointScaleBody(Engine,EngineModule,bodyName='hand-l',jointName='hand-l-joint',vector=EngineModule.Vec3(2.313906908,1.815508246,0.636324406))

			bodyJointScaleJointPos(Engine,EngineModule,bodyName='shoulder-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(1.233332872,0.000000527,-0.000006907))
			bodyJointScaleBody(Engine,EngineModule,bodyName='shoulder-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(2.196150780,2.018250704,1.834773302))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(9.539100647,1.898749590,1.726135969))
			bodyJointScaleBody(Engine,EngineModule,bodyName='larm-r',jointName='larm-r-joint',vector=EngineModule.Vec3(7.937189579,1.296871424,1.178974032))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uleg-r',jointName='uleg-r-joint',vector=EngineModule.Vec3(11.259112358,3.363751173,3.057955503))
			bodyJointScaleBody(Engine,EngineModule,bodyName='lleg-r',jointName='lleg-r-joint',vector=EngineModule.Vec3(13.635429382,2.088624477,1.898749590))
			bodyJointScaleBody(Engine,EngineModule,bodyName='foot-r',jointName='foot-r-joint',vector=EngineModule.Vec3(2.883241415,1.426558614,1.178974032))
			bodyJointScaleBody(Engine,EngineModule,bodyName='toes-r',jointName='toes-r-joint',vector=EngineModule.Vec3(2.018269062,1.726135969,0.732050061))
			bodyJointScaleBody(Engine,EngineModule,bodyName='hand-r',jointName='hand-r-joint',vector=EngineModule.Vec3(2.313906908,1.815508246,0.636324406))




			bodyJointScaleBody(Engine,EngineModule,bodyName='head',jointName='head-joint',vector=EngineModule.Vec3(3.226835489,3.700126410,3.363751173))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='head',jointName='head-joint',vector=EngineModule.Vec3(-0.800000429,-0.000000477,0.000000011))
			bodyJointScaleBody(Engine,EngineModule,bodyName='head',jointName='head-joint',vector=EngineModule.Vec3(2.305550814,4.477152824,4.477152824))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='head',jointName='head-joint',vector=EngineModule.Vec3(-2.100000381,-0.000000477,0.000000011))
			bodyJointScaleBody(Engine,EngineModule,bodyName='head',jointName='head-joint',vector=EngineModule.Vec3(2.305550814,4.924868107,4.477152824))
			bodyJointScaleBody(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(5.211327553,7.138394833,4.477152824))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(-1.000001788,0.000001907,0.199997157))
			bodyJointScaleBody(Engine,EngineModule,bodyName='breast',jointName='breast-joint',vector=EngineModule.Vec3(5.211327553,7.138394833,4.924868107))
			bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(3.095424652,6.334136963,3.933000565))
			bodyJointScaleBody(Engine,EngineModule,bodyName='root',jointName='belly-joint',vector=EngineModule.Vec3(2.533615112,6.489449978,3.057955503))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='root',jointName='belly-joint',vector=EngineModule.Vec3(0.400000900,-0.000001192,-0.000017166))

			bodyJointScaleBody(Engine,EngineModule,bodyName='lleg-l',jointName='lleg-l-joint',vector=EngineModule.Vec3(13.635429382,2.297487020,2.088624477))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(9.539100647,2.297487020,2.088624477))
			bodyJointScaleBody(Engine,EngineModule,bodyName='larm-l',jointName='larm-l-joint',vector=EngineModule.Vec3(7.937189579,1.569214463,1.426558614))

			bodyJointScaleBody(Engine,EngineModule,bodyName='lleg-r',jointName='lleg-r-joint',vector=EngineModule.Vec3(13.635429382,2.297487020,2.088624477))
			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(9.539100647,2.297487020,2.088624477))
			bodyJointScaleBody(Engine,EngineModule,bodyName='larm-r',jointName='larm-r-joint',vector=EngineModule.Vec3(7.937189579,1.569214463,1.426558614))



			bodyJointScaleBody(Engine,EngineModule,bodyName='neck',jointName='neck-joint',vector=EngineModule.Vec3(2.182900190,2.954921246,2.954921246))
			bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(3.033825636,6.334136963,3.933000565))

			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(-1.300001740,0.000002936,0.000005826))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))

			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(-1.300001740,0.000002936,0.000005826))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))


			bodyJointScaleBody(Engine,EngineModule,bodyName='neck',jointName='neck-joint',vector=EngineModule.Vec3(2.182900190,2.954921246,2.954921246))
			bodyJointScaleBody(Engine,EngineModule,bodyName='belly',jointName='belly-joint',vector=EngineModule.Vec3(3.033825636,6.334136963,3.933000565))
			bodyJointScaleBody(Engine,EngineModule,bodyName='cheast',jointName='cheast-joint',vector=EngineModule.Vec3(4.148015022,5.959090710,4.432381153))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='cheast',jointName='cheast-joint',vector=EngineModule.Vec3(-0.999999762,0.000001907,0.700000048))

			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(-1.300001740,0.000002936,0.000005826))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-l',jointName='finger-index-high-l-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-middle-high-l',jointName='finger-middle-high-l-joint',vector=EngineModule.Vec3(2.069151402,0.321195006,0.321195006))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-little-high-l',jointName='finger-little-high-l-joint',vector=EngineModule.Vec3(1.836014986,0.313505679,0.313505679))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-ring-high-l',jointName='finger-ring-high-l-joint',vector=EngineModule.Vec3(2.195024252,0.309758455,0.309758455))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-middle-high-l',jointName='finger-middle-high-l-joint',vector=EngineModule.Vec3(2.276066542,0.321195006,0.321195006))
			bodyJointScaleBody(Engine,EngineModule,bodyName='thumb-high-l',jointName='thumb-high-l-joint',vector=EngineModule.Vec3(1.722578645,0.323549688,0.294136077))
			bodyJointScaleBody(Engine,EngineModule,bodyName='foot-l',jointName='foot-l-joint',vector=EngineModule.Vec3(2.883241415,1.726135969,1.178974032))

			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(-1.300001740,0.000002936,0.000005826))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(2.125452757,0.329934716,0.329934716))
			bodyJointScaleJointPos(Engine,EngineModule,bodyName='finger-index-high-r',jointName='finger-index-high-r-joint',vector=EngineModule.Vec3(-1.200001836,0.000002936,0.000005826))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-middle-high-r',jointName='finger-middle-high-r-joint',vector=EngineModule.Vec3(2.069151402,0.321195006,0.321195006))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-little-high-r',jointName='finger-little-high-r-joint',vector=EngineModule.Vec3(1.836014986,0.313505679,0.313505679))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-ring-high-r',jointName='finger-ring-high-r-joint',vector=EngineModule.Vec3(2.195024252,0.309758455,0.309758455))
			bodyJointScaleBody(Engine,EngineModule,bodyName='finger-middle-high-r',jointName='finger-middle-high-r-joint',vector=EngineModule.Vec3(2.276066542,0.321195006,0.321195006))
			bodyJointScaleBody(Engine,EngineModule,bodyName='thumb-high-r',jointName='thumb-high-r-joint',vector=EngineModule.Vec3(1.722578645,0.323549688,0.294136077))
			bodyJointScaleBody(Engine,EngineModule,bodyName='foot-r',jointName='foot-r-joint',vector=EngineModule.Vec3(2.883241415,1.726135969,1.178974032))


			setLimits(Engine,EngineModule,jointName='belly-joint',y=15.9999918938,z=14.9999976158)
			bodyJointScaleBody(Engine,EngineModule,bodyName='cheast',jointName='cheast-joint',vector=EngineModule.Vec3(4.065469742,5.959090710,4.432381153))
			setLimits(Engine,EngineModule,jointName='cheast-joint',y=10.9999979019,z=10.9999990463)
			setLimits(Engine,EngineModule,jointName='breast-joint',y=10.9999979019,z=10.9999990463)
			setLimits(Engine,EngineModule,jointName='neck-joint',y=15.999994278,z=15.9999980927)
			setLimits(Engine,EngineModule,jointName='head-joint',y=20.9999895096,z=20.9999966621)

			setLimits(Engine,EngineModule,jointName='uleg-l-joint',y=30.9999895096,z=30.9999918938)
			setLimits(Engine,EngineModule,jointName='toes-l-joint',y=15.9999990463,z=0.999999713898)

			setLimits(Engine,EngineModule,jointName='uleg-r-joint',y=30.9999895096,z=30.9999918938)
			setLimits(Engine,EngineModule,jointName='toes-r-joint',y=15.9999990463,z=0.999999713898)





			setLimits(Engine,EngineModule,jointName='larm-l-joint',y=0.999984836578,z=30.9999918938)
			setLimits(Engine,EngineModule,jointName='finger-index-high-l-joint',y=55.9999799728,z=0.99999961853)
			setMotorTarget(Engine,EngineModule,jointName='finger-index-high-l-joint',quaternion=EngineModule.Quat(0.996194839,0.000000000,0.087155752,0.000000000))
			setLimits(Engine,EngineModule,jointName='finger-index-high-l-joint',y=60.9999704361,z=0.999998950958)
			setLimits(Engine,EngineModule,jointName='finger-middle-high-l-joint',y=50.9999847412,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='finger-ring-high-l-joint',y=50.9999847412,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='finger-little-high-l-joint',y=50.9999847412,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='hand-l-joint',y=30.9999895096,z=15.9999980927)
			setLimits(Engine,EngineModule,jointName='thumb-high-l-joint',y=20.9999895096,z=20.9999966621)
			setLimits(Engine,EngineModule,jointName='uarm-l-joint',y=35.9999728203,z=35.9999918938)
			setLimits(Engine,EngineModule,jointName='lleg-l-joint',y=30.9999918938,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='shoulder-l-joint',y=25.9999895096,z=25.999994278)

			setLimits(Engine,EngineModule,jointName='larm-r-joint',y=0.999984836578,z=30.9999918938)
			setLimits(Engine,EngineModule,jointName='finger-index-high-r-joint',y=55.9999799728,z=0.99999961853)
			setMotorTarget(Engine,EngineModule,jointName='finger-index-high-r-joint',quaternion=EngineModule.Quat(0.996194839,0.000000000,0.087155752,0.000000000))
			setLimits(Engine,EngineModule,jointName='finger-index-high-r-joint',y=60.9999704361,z=0.999998950958)
			setLimits(Engine,EngineModule,jointName='finger-middle-high-r-joint',y=50.9999847412,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='finger-ring-high-r-joint',y=50.9999847412,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='finger-little-high-r-joint',y=50.9999847412,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='hand-r-joint',y=30.9999895096,z=15.9999980927)
			setLimits(Engine,EngineModule,jointName='thumb-high-r-joint',y=20.9999895096,z=20.9999966621)
			setLimits(Engine,EngineModule,jointName='uarm-r-joint',y=35.9999728203,z=35.9999918938)
			setLimits(Engine,EngineModule,jointName='lleg-r-joint',y=30.9999918938,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='shoulder-r-joint',y=25.9999895096,z=25.999994278)



			bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='larm-l',jointName='larm-l-joint',quaternion=EngineModule.Quat(0.499999940,0.000000000,0.000000000,0.866025567))
			setLimits(Engine,EngineModule,jointName='larm-l-joint',y=0,z=0)


			setMotorTarget(Engine,EngineModule,jointName='lleg-l-joint',quaternion=EngineModule.Quat(1.000000000,0.000000000,0.000000000,0.000000000))

			setLimits(Engine,EngineModule,jointName='lleg-l-joint',y=84.9999713898,z=9.99998855591e-08)
			setLimits(Engine,EngineModule,jointName='foot-l-joint',y=30.9999775887,z=30.9999895096)
			setLimits(Engine,EngineModule,jointName='uleg-l-joint',y=45.9999656677,z=45.9999895096)
			setLimits(Engine,EngineModule,jointName='lleg-l-joint',y=84.9999523163,z=10.0)
			setMotorTarget(Engine,EngineModule,jointName='lleg-l-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))
			bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='lleg-l',jointName='lleg-l-joint',quaternion=EngineModule.Quat(0.939692855,0.000000000,-0.342020273,0.000000000))

			setLimits(Engine,EngineModule,jointName='lleg-r-joint',y=85.9999370575,z=0.99999961853)
			setLimits(Engine,EngineModule,jointName='foot-r-joint',y=30.9999895096,z=30.9999918938)
			setLimits(Engine,EngineModule,jointName='uleg-r-joint',y=45.9999656677,z=45.9999895096)
			setLimits(Engine,EngineModule,jointName='lleg-r-joint',y=85.9999275208,z=10.9999990463)
			setMotorTarget(Engine,EngineModule,jointName='lleg-r-joint',quaternion=EngineModule.Quat(0.939692795,0.000000000,-0.342020273,0.000000000))
			bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='lleg-r',jointName='lleg-r-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))

			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(9.443709373,2.297487020,2.297487020))
			setLimits(Engine,EngineModule,jointName='uarm-r-joint',y=50.9999656677,z=35.9999799728)
			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',vector=EngineModule.Vec3(9.443709373,2.274512053,2.527235746))
			bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='uarm-r',jointName='uarm-r-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))

			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(9.443709373,2.297487020,2.297487020))
			setLimits(Engine,EngineModule,jointName='uarm-l-joint',y=50.9999656677,z=35.9999799728)
			bodyJointScaleBody(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',vector=EngineModule.Vec3(9.443709373,2.274512053,2.527235746))
			bodyJointAbsoluteRotation(Engine,EngineModule,bodyName='uarm-l',jointName='uarm-l-joint',quaternion=EngineModule.Quat(0.939692676,0.000000000,-0.342020214,0.000000000))



			addSphere(Engine,EngineModule,bodyName='foot-l',shapeName='foot-l-2',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
			scalePhysicShape(Engine,EngineModule,bodyName='foot-l',shapeName='foot-l-2',size=EngineModule.Vec3(2.143589020,1.948717356,1.948717356))
			movePhysicShape(Engine,EngineModule,bodyName='foot-l',shapeName='foot-l-2',position=EngineModule.Vec3(-2.000000477,2.000000000,-1.999999523))

			addSphere(Engine,EngineModule,bodyName='foot-r',shapeName='foot-r-2',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
			scalePhysicShape(Engine,EngineModule,bodyName='foot-r',shapeName='foot-r-2',size=EngineModule.Vec3(2.143589020,1.948717356,1.948717356))
			movePhysicShape(Engine,EngineModule,bodyName='foot-r',shapeName='foot-r-2',position=EngineModule.Vec3(-2.000000477,2.000000000,-1.999999523))

