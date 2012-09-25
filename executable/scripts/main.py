import saveload

def init(Engine,EngineModule,objects):
	#saveload.load(Engine,EngineModule,"xmlscene/test.xml",objects)
	saveload.load(Engine,EngineModule,"xmlscene/scene.xml",objects)
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isGuiShape():
			if not o.isFinalShape():
				o.hide()
	
