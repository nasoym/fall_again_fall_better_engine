
def createJoint(Engine,EngineModule,body1,body2):
	o = Engine.createJoint(body1,body2)
	b = Engine.createGuiBox()
	b.setColour(0,0,1,0.5)
	b.setSize(EngineModule.Vec3(2,7,7))
	b.setScalingFixed()
	o.addShape(b)
	return o

def createPhysicBoxFinal(Engine,EngineModule):
	o = Engine.createDynamicActor()
	b = o.addBox(EngineModule.Vec3(1,1,1))
	#b = o.addCapsule(EngineModule.Vec3(1,1,1))
	b.setMaterialName(Engine.getDefaultShadedMaterialName())
	b.setScaling1To1()
	o.setPosition(EngineModule.Vec3(0,150,0))
	o.setSize(EngineModule.Vec3(10,10,10))
	return o

def createPhysicBoxStructure(Engine,EngineModule):
	o = Engine.createDynamicActor()
	b = o.addBox(EngineModule.Vec3(1,1,1))
	b.setColour(0,1,0,0.5)
	b.setScaling1To1()
	o.setPosition(EngineModule.Vec3(0,150,0))
	o.setSize(EngineModule.Vec3(10,10,10))
	return o

def createPhysicStaticBoxFinal(Engine,EngineModule):
	o = Engine.createStaticActor()
	b = o.addBox(EngineModule.Vec3(1,1,1))
	b.setMaterialName(Engine.getDefaultShadedMaterialName())
	b.setScaling1To1()
	o.setPosition(EngineModule.Vec3(0,150,0))
	o.setSize(EngineModule.Vec3(10,10,10))
	return o

def createPhysicStaticBoxStructure(Engine,EngineModule):
	o = Engine.createStaticActor()
	b = o.addBox(EngineModule.Vec3(1,1,1))
	b.setColour(0,1,0,0.5)
	b.setScaling1To1()
	o.setPosition(EngineModule.Vec3(0,150,0))
	o.setSize(EngineModule.Vec3(10,10,10))
	return o

def createSpaceCage(Engine,EngineModule,size):
	o = Engine.createSpaceCage(size)
	o.setUnselectable()

	#TODO create all planes
	#TODO save load xml
	"""
	float xSize = size.X();
	float ySize = size.Y();
	float zSize = size.Z();

	mBottomPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,0,0), Quat().fromAngles(0,0,90).toPhysx() );

	mTopPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,ySize,0), Quat().fromAngles(0,0,-90).toPhysx() );

	mFrontPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,0,zSize), Quat().fromAngles(0,90,0).toPhysx() );

	mBackPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,0,-zSize), Quat().fromAngles(0,-90,0).toPhysx() );

	mLeftPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(xSize,0,0), Quat().fromAngles(0,0,180).toPhysx() );

	mRightPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(-xSize,0,0), Quat().fromAngles(0,0,0).toPhysx() );
		"""

	wall = 1.0;
	ground_opacity = 1.0;
	ceiling_opacity = 0.25;
	wall_opacity = 0.1;
	red = 1.0;
	green = 1.0;
	blue = 1.0;

	shape = Engine.createGuiBox()
	shape.setScalingNone()
	#shape.setColour(red,green,blue,ground_opacity)
	shape.setMaterialName(Engine.getDefaultShadedMaterialName())
	shape.turnOffShadows()
	shape.setFinalShape()
	shape.setSize(EngineModule.Vec3(size.X(),wall,size.Z()))
	#shape.setSize(EngineModule.Vec3(size.X() * 10000,wall,size.Z() * 10000))
	shape.setPosition(EngineModule.Vec3(0,-wall,0))
	o.addShape(shape)

	"""
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
	"""

	return 0
