
def launch(engine,objects,module):
	"""
	print("hello  .")
	print(objects["gui1"])
	o = objects["gui1"]
	print(o.isGuiShape())
	o.setPosition((0,4,0))
	print(o.getPosition())

	q = module.Quat(1,0,0,0)
	q.fromAngle(0,0,30)
	engine.setCameraOrientation(q)

	engine.setCameraPosition(module.Vec3(0,0,300))
	print(engine.getCameraPosition().toTuple())
	#print(Engine)
	#print(module.Vec3)
	"""

	transformFactor = 4
	direction = module.Vec3(0,0,-1)
	direction *= transformFactor
	globalDir = engine.getCameraOrientation() * direction

	engine.setCameraPosition( engine.getCameraPosition() + globalDir)





