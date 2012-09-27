import random
import os

lastEventTime = None
lastMemReportTime = 0
lastMemUsage = 0

memReportTime = 1000 * 60 * 10

watchDogFrequency = 1000 * 60 * 3
lastWatchDogTime = 0

framesBelowMinimumFPS = 0
maximalFramesBelowMinimum = 20 * 60 * 15
minimalFPS = 20

def init(Engine,EngineModule,objects):
	global lastEventTime,lastMemReportTime
	lastEventTime = Engine.getTime()
	lastMemReportTime = Engine.getTime()

def keyPressed(Engine,EngineModule,key,selection,objects):

	if key == EngineModule.Keys.K_EXTREME_VELOCITY:
		if Engine.isFullscreen():
			Engine.log("extreme velocity")
			Engine.quit()

	if key == EngineModule.Keys.K_FOCUS_CHANGE:
		if Engine.isFullscreen():
			Engine.log("focus change in fullscreen")
			Engine.quit()


def guiUpdate(Engine,EngineModule,selection,objects):

	global lastEventTime
	global guiFrameCounter
	global lastMemUsage
	global lastMemReportTime
	global lastWatchDogTime

	global framesBelowMinimumFPS
	global maximalFramesBelowMinimum
	global minimalFPS

	currentTime = Engine.getTime()

	if Engine.getTimeDifference() > 0:
		fps = float(1000.0 / Engine.getTimeDifference())
		if fps < minimalFPS:
			framesBelowMinimumFPS += 1
		elif not framesBelowMinimumFPS <= 0:
			framesBelowMinimumFPS -= 1
		if framesBelowMinimumFPS > maximalFramesBelowMinimum:
			Engine.log("fps: " + str(fps) + " is below minimum: " + str(minimalFPS))
	
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
			Engine.log("report mem: " + str(memUsage) + "  diff: " + 
				str(memUsageDifference) + 
				" time: " + str(currentTime))
		Engine.log("report fps: " + str(float(1000.0 / Engine.getTimeDifference())))




