import helpers

def runMethods(Engine,EngineModule,objects,animList,index,methodName):
	for groupName in animList[index]['groups']:
		if groupName in objects.get():
			partsList = objects.get()[groupName]
			#print("group: " + str(groupName))
			for part in partsList:
				methods = animList[index][methodName]
				for method in methods:
					method(Engine,EngineModule,objects,part)

def playAnimation(Engine,EngineModule,objects,animData,animList):
	animName = animData["name"]
	startTime = animData["starttime"]
	animIndex = animData["index"]
	animListSize = len(animList)
	currentTime = Engine.getTime()
	if animIndex < animListSize:
		endTime = startTime + animList[animIndex]['time']
		if ((currentTime > startTime) and
			(currentTime < endTime)):
			if animIndex != 0:
				print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
				runMethods(Engine,EngineModule,
					objects,animList,animIndex-1,"end")
			print("run anim start: " + str(animName) + " index : " + str(animIndex))
			runMethods(Engine,EngineModule,
				objects,animList,animIndex,"start")
			animData["index"] = animIndex + 1
			print("go to next anim index")
			animData["starttime"] = endTime
	elif animIndex == animListSize:
		if currentTime > startTime:
			print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
			runMethods(Engine,EngineModule,
				objects,animList,animIndex-1,"end")
			animData["index"] = animIndex + 1
			print("done")



def showBodyList(bodyList):
	number = 0
	text = ""
	for body in bodyList:
		if body:
			#print("body: " + body.getName() + " : " + str(body.getMass())[:5])
			text += " " + body.getName() + ":" + str(body.getMass())[:5]
			number += 1
	print(text)
	print("total bodies: " + str(number))

def getBodyListFromGroupName(objects,groupName):
	if groupName in objects.get():
		bodyList = objects.get()[groupName]
		return bodyList
	else:
		return []

def getBodyListFromGroupNameList(objects,groupNameList):
	bodyList = []
	for groupName in groupNameList:
		if groupName in objects.get():
			for body in objects.get()[groupName]:
				bodyList.append(body)
	return bodyList

def getBodyListFromNameList(Engine,EngineModule,nameList):
	bodyList = []
	for bodyName in nameList:
		body = helpers.getBodyFromName(Engine,EngineModule,bodyName)
		bodyList.append(body)
	return bodyList
		

def resetMasses(bodyList):
	for body in bodyList:
		if body.isActor():
			body.resetMass()

def multiplyMasses(bodyList,factor):
	for body in bodyList:
		if body.isActor():
			newMass = body.getMass() * factor
			body.setMass(newMass)

def setMasses(bodyList,mass):
	for body in bodyList:
		if body.isActor():
			body.setMass(mass)

def showMassRelationToPrev(bodyList):
	text = ""
	for i in range(0,len(bodyList)):
		body = bodyList[i]
		if i > 0:
			prevBody = bodyList[i-1]
			massRelation = body.getMass() / prevBody.getMass()
			#print("body: " + body.getName() + " mass: " + str(body.getMass()) + 
			#	" relation to prev: " + str(massRelation))
			text += " " + body.getName() + ":" + str(body.getMass())[:5]
			text += ":" + str(massRelation)[:5]
		else:
			#print("body: " + body.getName() + " mass: " + str(body.getMass())) 
			text += " " + body.getName() + ":" + str(body.getMass())[:5]
	print(text)

def showMassRelationToAll(bodyList):
	totalMass = 0
	text = ""
	for body in bodyList:
		totalMass += body.getMass()
	for body in bodyList:
		massRelation = body.getMass() / totalMass
		#print("body: " + body.getName() + " mass: " + str(body.getMass()) + 
		#	" relation to all: " + str(massRelation))
		text += " " + body.getName() + ":" + str(body.getMass())[:5]
		text += ":" + str(massRelation)[:5]
	print(text)


def approachRelationToPrev(bodyList,finalRelation,approachPercentage):
	for i in range(0,len(bodyList)):
		body = bodyList[i]
		if i > 0:
			prevBody = bodyList[i-1]
			massInFinalRelation = prevBody.getMass() * finalRelation
			diffToActualMass = massInFinalRelation - body.getMass()
			newMass = body.getMass() + (diffToActualMass * approachPercentage)
			body.setMass(newMass)

def approachEqualMassDistribution(bodyList,approachPercentage):
	totalMass = 0
	totalBodies = 0
	for body in bodyList:
		totalMass += body.getMass()
		totalBodies += 1
	for body in bodyList:
		massInFinalRelation = totalMass / totalBodies
		diffToActualMass = massInFinalRelation - body.getMass()
		newMass = body.getMass() + (diffToActualMass * approachPercentage)
		body.setMass(newMass)

