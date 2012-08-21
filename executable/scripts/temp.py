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

	if key == EngineModule.Keys.K_O:
		if len(selection.get()) == 1:
			o = selection.get()[0]
			if Engine.isKeyDown(EngineModule.Keys.K_1):
				o.setPosition(o.getPosition() + EngineModule.Vec3(20,0,0))
			if Engine.isKeyDown(EngineModule.Keys.K_2):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,20,0))
			if Engine.isKeyDown(EngineModule.Keys.K_3):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,0,20))
			if Engine.isKeyDown(EngineModule.Keys.K_4):
				o.setPosition(o.getPosition() + EngineModule.Vec3(-20,0,0))
			if Engine.isKeyDown(EngineModule.Keys.K_5):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,-20,0))
			if Engine.isKeyDown(EngineModule.Keys.K_6):
				o.setPosition(o.getPosition() + EngineModule.Vec3(0,0,-20))

			else:
				o.setPosition(o.getPosition() * EngineModule.Vec3(1,0.9,1))

	if key == EngineModule.Keys.K_T:
		pass
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()
		#for o in selection.get():
		#if Engine.isKeyDown(EngineModule.Keys.K_7):


		#saveload.save(Engine,EngineModule,"xmlscene/ragdoll_01.xml")
		saveload.load(Engine,EngineModule,"xmlscene/ragdoll_01.xml")
						

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass
