import random

lastEventTime = None
lastMemReportTime = 0
lastMemUsage = 0

#memReportTime = 1000 * 60 * 10
memReportTime = 1000 * 60 * 1
#memReportTime = 1000 * 5 

def init(Engine,EngineModule,objects):
	pass
	global lastEventTime,lastMemReportTime
	lastEventTime = Engine.getTime()
	lastMemReportTime = Engine.getTime()

def guiUpdate(Engine,EngineModule,selection,objects):

	global lastEventTime
	global guiFrameCounter
	global lastMemUsage
	global lastMemReportTime

	currentTime = Engine.getTime()

	
	"""
	timeSinceEvent = currentTime - lastEventTime
	if timeSinceEvent > 100:
		lastEventTime = currentTime
		if random.uniform(0,1) < 0.1:
			#print("event")
			Engine.callPythonKeyPressed(EngineModule.Keys.K_SPACE)
			"""

	timeSinceLastReport = currentTime - lastMemReportTime
	if timeSinceLastReport > memReportTime:
		memUsage = Engine.getMemoryUsage()
		memUsageDifference = memUsage - lastMemUsage
		if memUsageDifference > 0:
			lastMemReportTime = currentTime
			lastMemUsage = memUsage
			Engine.log("mem: " + str(memUsage) + "  diff: " + 
				str(memUsageDifference) + 
				" time: " + str(currentTime))





