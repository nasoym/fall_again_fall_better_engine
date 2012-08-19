"""
misc:
	k: save
	l: load
"""
import saveload

def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass
	if key == EngineModule.Keys.K_K:
		saveload.save(Engine,EngineModule,"xmlscene/file1.xml")

	if key == EngineModule.Keys.K_L:
		saveload.load(Engine,EngineModule,"xmlscene/file1.xml")

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass

