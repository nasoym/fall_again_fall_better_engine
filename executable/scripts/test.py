import random
import os

lastEventTime = None
lastMemReportTime = 0
lastMemUsage = 0

#memReportTime = 1000 * 60 * 10
memReportTime = 1000 * 60 * 1
#memReportTime = 1000 * 5 


watchDogFrequency = 1000 * 5
lastWatchDogTime = 0

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
	global lastWatchDogTime

	currentTime = Engine.getTime()

	
	"""
	timeSinceEvent = currentTime - lastEventTime
	if timeSinceEvent > 100:
		lastEventTime = currentTime
		if random.uniform(0,1) < 0.1:
			#print("event")
			Engine.callPythonKeyPressed(EngineModule.Keys.K_SPACE)
			"""

	timeSinceLastWatchDog = currentTime - lastWatchDogTime
	if timeSinceLastWatchDog > watchDogFrequency:
		lastWatchDogTime = currentTime
		os.utime("watchdog.txt",None)

	timeSinceLastReport = currentTime - lastMemReportTime
	if timeSinceLastReport > memReportTime:
		memUsage = Engine.getMemoryUsage()
		memUsageDifference = memUsage - lastMemUsage
		lastMemReportTime = currentTime
		lastMemUsage = memUsage
		if memUsageDifference > 0:
			Engine.log("mem: " + str(memUsage) + "  diff: " + 
				str(memUsageDifference) + 
				" time: " + str(currentTime))
			Engine.log("fps: " + str(float(1000.0 / Engine.getTimeDifference())))




