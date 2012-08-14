import libxml2

def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,objects,key):
	pass

def keyPressed(Engine,EngineModule,objects,key):
	if key == EngineModule.Keys.K_T:
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))

		objects["mesh"] = Engine.createMesh("Character.mesh")
		#objects["mesh"] = Engine.createMesh("tube.mesh")
		#objects["mesh"] = Engine.createMesh("Cube.mesh")
		#objects["mesh"] = Engine.createMesh("sphere.mesh")
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()

		#objects["mesh"].setSize(EngineModule.Vec3(1000,1000,1000))

	pass

def keyReleased(Engine,EngineModule,objects,key):
	pass

