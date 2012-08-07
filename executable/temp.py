
def launch(Engine,objects,EngineModule):

	#Engine.setTimingFactor(0.0001)
	#print("timingfactor: " +str(Engine.getTimingFactor()))

	objects["mesh"] = Engine.createMesh("Character.mesh")
	#objects["mesh"] = Engine.createMesh("tube.mesh")
	#objects["mesh"] = Engine.createMesh("Cube.mesh")
	#objects["mesh"] = Engine.createMesh("sphere.mesh")
	#Engine.simulatePhysics(1.0/60.0)
	#Engine.physicPauseToggle()

	#objects["mesh"].setSize(EngineModule.Vec3(1000,1000,1000))

