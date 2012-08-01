
def launch(Engine,objects,EngineModule):

	#Engine.setTimingFactor(0.25)
	#print("timingfactor: " +str(Engine.getTimingFactor()))

	objects["mesh"] = Engine.createMesh("Character.mesh")
	#objects["mesh"].setSize(EngineModule.Vec3(1000,1000,1000))

