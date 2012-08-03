
def launch(Engine,objects,EngineModule):

	#Engine.setTimingFactor(0.25)
	#print("timingfactor: " +str(Engine.getTimingFactor()))

	objects["mesh"] = Engine.createMesh("Character.mesh")
	#objects["mesh"] = Engine.createMesh("tube.mesh")
	#objects["mesh"] = Engine.createMesh("Cube.mesh")

	#objects["mesh"].setSize(EngineModule.Vec3(1000,1000,1000))

