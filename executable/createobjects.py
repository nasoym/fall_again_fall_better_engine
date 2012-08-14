
def createPhysicBoxFinal(Engine,EngineModule):
	o = Engine.createPhysicBox()
	b = Engine.createGuiBox()
	b.setMaterialName("Body")
	b.setScaling1To1()
	o.addShape(b)
	o.setPosition(EngineModule.Vec3(0,150,0))
	o.setSize(EngineModule.Vec3(10,10,10))
	return o

def createPhysicBoxStructure(Engine,EngineModule):
	o = Engine.createPhysicBox()
	b = Engine.createGuiBox()
	b.setColour(0,1,0,0.5)
	b.setScaling1To1()
	o.addShape(b)
	o.setPosition(EngineModule.Vec3(0,150,0))
	o.setSize(EngineModule.Vec3(10,10,10))
	return o

def createPhysicStaticBoxFinal(Engine,EngineModule):
	o = Engine.createPhysicStatic()
	b = Engine.createGuiBox()
	b.setMaterialName("Body")
	b.setScaling1To1()
	o.addShape(b)
	return o

def createPhysicStaticBoxStructure(Engine,EngineModule):
	o = Engine.createPhysicStatic()
	b = Engine.createGuiBox()
	b.setColour(0,1,0,0.5)
	b.setScaling1To1()
	o.addShape(b)
	return o

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

def createSpaceCage(Engine,EngineModule,size):
	o = Engine.createSpaceCage(size)

	wall = 1.0;
	ground_opacity = 1.0;
	ceiling_opacity = 0.25;
	wall_opacity = 0.1;
	red = 1.0;
	green = 1.0;
	blue = 1.0;

	shape = Engine.createGuiBox()
	shape.setScalingNone()
	shape.setColour(red,green,blue,ground_opacity)
	#shape.setMaterialName("Body")
	shape.setSize(EngineModule.Vec3(size.X(),wall,size.Z()))
	shape.setPosition(EngineModule.Vec3(0,-wall,0))
	o.addShape(shape)

	shape = Engine.createGuiBox()
	shape.setScalingNone()
	shape.setColour(red,green,blue,ceiling_opacity)
	shape.setSize(EngineModule.Vec3(size.X(),wall,size.Z()))
	shape.setPosition(EngineModule.Vec3(0,size.Y() + wall,0))
	o.addShape(shape)

	shape = Engine.createGuiBox()
	shape.setScalingNone()
	shape.setColour(red,green,blue,wall_opacity)
	shape.setSize(EngineModule.Vec3(size.X(),size.Y()*0.5,wall))
	shape.setPosition(EngineModule.Vec3(0,size.Y()*0.5,size.Z()+wall))
	o.addShape(shape)

	shape = Engine.createGuiBox()
	shape.setScalingNone()
	shape.setColour(red,green,blue,wall_opacity)
	shape.setSize(EngineModule.Vec3(size.X(),size.Y()*0.5,wall))
	shape.setPosition(EngineModule.Vec3(0,size.Y()*0.5,-size.Z()-wall))
	o.addShape(shape)

	shape = Engine.createGuiBox()
	shape.setScalingNone()
	shape.setColour(red,green,blue,wall_opacity)
	shape.setSize(EngineModule.Vec3(wall,size.Y()*0.5,size.Z()))
	shape.setPosition(EngineModule.Vec3(size.X()+wall,size.Y()*0.5,0))
	o.addShape(shape)

	shape = Engine.createGuiBox()
	shape.setScalingNone()
	shape.setColour(red,green,blue,wall_opacity)
	shape.setSize(EngineModule.Vec3(wall,size.Y()*0.5,size.Z()))
	shape.setPosition(EngineModule.Vec3(-size.X()-wall,size.Y()*0.5,0))
	o.addShape(shape)

	return 0
