import saveload

def init(Engine,EngineModule,objects):
	if not "anims" in objects.get():
		objects.get()["anims"] = {}
		objects.setUnsavable("anims")

	#saveload.load(Engine,EngineModule,"xmlscene/scene.xml",objects)
	saveload.load(Engine,EngineModule,"xmlscene/test.xml",objects)
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		if o.isGuiShape():
			if not o.isFinalShape():
				o.hide()
	
	objects.get()["anims"]["stand"] = {"name":"rising","index":0,"starttime":Engine.getTime(),"done":True}
	Engine.setGravity(EngineModule.Vec3(0,-10,0))
	Engine.setTimingFactor(2.0)

