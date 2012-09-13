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


			"""
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






			addSphere(Engine,EngineModule,bodyName='cheast',shapeName='2',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(20.000000000,0.000000000,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(0.000000000,0.000000000,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.000000000,0.000000000,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(2.000000000,0.000000000,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(2.000000000,1.000000000,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(2.000000477,2.000000238,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(2.000001192,3.000000954,0.000000000))
			scalePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.100000024,1.000000000,1.000000000))
			scalePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.210000038,1.100000024,1.100000024))
			scalePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.331000090,1.210000038,1.210000038))
			scalePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.464100122,1.331000090,1.331000090))
			scalePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.610510111,1.464100122,1.464100122))
			scalePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.771561146,1.610510111,1.610510111))
			scalePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='2',pos=EngineModule.Vec3(1.948717356,1.771561146,1.771561146))
			addCapsule(Engine,EngineModule,bodyName='cheast',shapeName='3',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Vec3(-0.000000358,0.999999285,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Vec3(-0.000000656,-0.000000834,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Vec3(-0.000000536,-1.000001073,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Vec3(-0.000001073,-2.000001907,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Vec3(-0.000001580,-3.000003338,0.000000000))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.999048710,0.043619417,0.000000001,0.000000030))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.996195376,0.087155819,0.000000004,0.000000045))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.995247543,0.087072894,0.043453455,0.003801745))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.992405117,0.086824216,0.086824208,0.007596180))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.987673342,0.086410232,0.130029678,0.011376151))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.981061578,0.085831776,0.172987640,0.015134526))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.972582340,0.085089944,0.215616345,0.018864036))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.962251782,0.084186137,0.257834613,0.022557653))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.950089693,0.083122082,0.299562126,0.026208339))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.948042333,0.096109703,0.295651317,0.067625768))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.944190383,0.108914398,0.291177720,0.108914405))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.938540995,0.121511742,0.286149830,0.149995759))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.931104958,0.133877799,0.280577272,0.190791592))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.921896935,0.145989031,0.274470598,0.231224313))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.910933912,0.157822371,0.267841488,0.271216929))
			rotatePhysicShape(Engine,EngineModule,bodyName='cheast',shapeName='3',pos=EngineModule.Quat(0.898236930,0.169355318,0.260702550,0.310693234))
			"""



			addSphere(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
			movePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',position=EngineModule.Vec3(0.000000000,1.000000000,0.000000000))
			movePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',position=EngineModule.Vec3(0.000000000,2.000000000,0.000000000))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.000000000,1.100000024,1.000000000))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.000000000,1.100000024,1.000000000))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.100000024,1.000000000,1.000000000))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.210000038,1.100000024,1.100000024))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.331000090,1.210000038,1.210000038))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.464100122,1.331000090,1.331000090))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.610510111,1.464100122,1.464100122))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.771561146,1.610510111,1.610510111))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(1.948717356,1.771561146,1.771561146))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(2.143589020,1.948717356,1.948717356))
			scalePhysicShape(Engine,EngineModule,bodyName='uarm-l',shapeName='2',size=EngineModule.Vec3(2.357948065,2.143589020,2.143589020))
			addCapsule(Engine,EngineModule,bodyName='larm-l',shapeName='2',size=EngineModule.Vec3(1.000000000,1.000000000,1.000000000),r=0.5,g=0.5,b=0.0,a=0.5)
			rotatePhysicShape(Engine,EngineModule,bodyName='larm-l',shapeName='2',quaternion=EngineModule.Quat(0.999048233,0.000000000,0.000000000,0.043619394))
			rotatePhysicShape(Engine,EngineModule,bodyName='larm-l',shapeName='2',quaternion=EngineModule.Quat(0.996194720,0.000000000,0.000000000,0.087155759))
			rotatePhysicShape(Engine,EngineModule,bodyName='larm-l',shapeName='2',quaternion=EngineModule.Quat(0.991444886,0.000000000,0.000000000,0.130526215))
			rotatePhysicShape(Engine,EngineModule,bodyName='larm-l',shapeName='2',quaternion=EngineModule.Quat(0.984807968,0.000000000,0.000000000,0.173648238))
			rotatePhysicShape(Engine,EngineModule,bodyName='larm-l',shapeName='2',quaternion=EngineModule.Quat(0.976296365,0.000000000,0.000000000,0.216439724))

