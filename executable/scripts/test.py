import random

lastEventTime = None
guiFrameCounter = 0
lastMemUsage = 0

def init(Engine,EngineModule,objects):
	pass
	global lastEventTime
	lastEventTime = Engine.getTime()

def guiUpdate(Engine,EngineModule,selection,objects):

	#Engine.callPythonKeyPressed(EngineModule.Keys.K_SPACE)

	global lastEventTime
	global guiFrameCounter
	global lastMemUsage

	currentTime = Engine.getTime()
	timeSinceEvent = currentTime - lastEventTime
	
	if timeSinceEvent > 100:
		lastEventTime = currentTime
		if random.uniform(0,1) < 0.1:
			#print("event")
			Engine.callPythonKeyPressed(EngineModule.Keys.K_SPACE)

	if guiFrameCounter > 10:
		guiFrameCounter = 0
		memUsage = Engine.getMemoryUsage()
		memUsageDifference = memUsage - lastMemUsage
		if memUsageDifference > 0:
			Engine.log("mem: " + str(memUsage) + "  diff: " + 
				str(memUsageDifference) + 
				" time: " + str(currentTime))
			lastMemUsage = memUsage
	else:
		guiFrameCounter += 1





