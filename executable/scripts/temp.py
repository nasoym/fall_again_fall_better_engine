"""
temp:
	t: run temp
"""
import mesh
import createobjects as create
import saveload

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):

	if key == EngineModule.Keys.K_T:
		pass
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()
		#for o in selection.get():

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass
