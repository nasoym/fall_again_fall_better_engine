
def createBox(Engine,EngineModule):
	o = Engine.createPhysicBox()
	o.setSize(EngineModule.Vec3(10,10,10))
	o.setPosition(EngineModule.Vec3(0,150,0))

	b = Engine.createGuiBox()
	b.setLocalPosition(EngineModule.Vec3(10,0,0))
	b.setLocalSize(EngineModule.Vec3(10,0.5,0.5))
	b.setColour(1,0,0,0.8)
	b.setScalingFixed()
	o.addShape(b)

	b = Engine.createGuiBox()
	b.setLocalPosition(EngineModule.Vec3(0,10,0))
	b.setLocalSize(EngineModule.Vec3(0.5,10,0.5))
	b.setColour(0,1,0,0.8)
	b.setScalingFixed()
	o.addShape(b)

	b = Engine.createGuiBox()
	b.setLocalPosition(EngineModule.Vec3(0,0,10))
	b.setLocalSize(EngineModule.Vec3(0.5,0.5,10))
	b.setColour(0,0,1,0.8)
	b.setScalingFixed()
	o.addShape(b)
	return o

