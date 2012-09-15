import helpers

def runMethods(Engine,EngineModule,objects,animList,index,methodName):
	for groupName in animList[index]['groups']:
		partsList = objects.get()[groupName]
		#print("group: " + str(groupName))
		for part in partsList:
			methods = animList[index][methodName]
			for method in methods:
				method(Engine,EngineModule,objects,part)

def playAnimation(Engine,EngineModule,objects,animData,animList):
	#animName = animData["name"]
	#if animName in animLists:
	startTime = animData["starttime"]
	animIndex = animData["index"]
	#animList = animLists[animName]
	animListSize = len(animList)
	currentTime = Engine.getTime()
	if animIndex < animListSize:
		endTime = startTime + animList[animIndex]['time']
		if ((currentTime > startTime) and
			(currentTime < endTime)):
			if animIndex != 0:
				#print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
				runMethods(Engine,EngineModule,
					objects,animList,animIndex-1,"end")
			#print("run anim start: " + str(animName) + " index : " + str(animIndex))
			runMethods(Engine,EngineModule,
				objects,animList,animIndex,"start")
			animData["index"] = animIndex + 1
			animData["starttime"] = endTime
	elif animIndex == animListSize:
		if currentTime > startTime:
			#print("run anim end: " + str(animName) + " index : " + str(animIndex-1))
			runMethods(Engine,EngineModule,
				objects,animList,animIndex-1,"end")
			animData["index"] = animIndex + 1
			#print("done")




