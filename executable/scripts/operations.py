"""operations:
	o: run operations
"""

import bodyjoint
import helpers

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

def bodyJointScaleJointPos(Engine,EngineModule,bodyName,jointName,vector):
	mesh = getMesh(Engine,EngineModule)
	body = mesh.getBodyOfBoneName(bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	bodyjoint.bodyJointScaleJointPos(body,joint,vector)

def bodyJointScaleBody(Engine,EngineModule,bodyName,jointName,vector):
	mesh = getMesh(Engine,EngineModule)
	body = mesh.getBodyOfBoneName(bodyName)
	joint = getJoint(Engine,EngineModule,jointName)
	bodyjoint.bodyJointScaleBody(body,joint,newValue)

def setMotorTarget(Engine,EngineModule,jointName,quaternion):
	joint = getJoint(Engine,EngineModule,jointName)
	joint.setMotorTarget(quaternion)

def setLimits(Engine,EngineModule,jointName,y,z):
	joint = getJoint(Engine,EngineModule,jointName)
	joint.setLimits(y,z)

def keyPressed(Engine,EngineModule,key,selection,objects):
	if key == EngineModule.Keys.K_O:
		pass

		bodyJointScaleJointPos(Engine,EngineModule,bodyName='uleg-r',jointName='uleg-r-joint',vector=EngineModule.Vec3(-0.900000453,-0.000017166,0.100005008))
		bodyJointScaleJointPos(Engine,EngineModule,bodyName='uleg-r',jointName='uleg-r-joint',vector=EngineModule.Vec3(-0.800000429,-0.000017166,0.100005008))


