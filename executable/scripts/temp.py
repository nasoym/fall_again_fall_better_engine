import libxml2
import mesh

def init(Engine,EngineModule):
	pass

def keyDown(Engine,EngineModule,key,selection):
	pass

def keyPressed(Engine,EngineModule,key,selection):
	if key == EngineModule.Keys.K_T:
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))

		o = Engine.createMesh("Character.mesh")
		#o = Engine.createMesh("Cube.mesh")
		#o = Engine.createMesh("tube.mesh")
		o.setColour(1,0,0,0.2)
		#o.setColour(1,0,0,0.9)
		#o.setMaterialName("Body")
		o.setSize(EngineModule.Vec3(1,1,1)*1000)
		#o.setSize(EngineModule.Vec3(1,1,1)*200)
		o.setPosition(EngineModule.Vec3(0,150,0))
		mesh.createBones(Engine,EngineModule,o)
		o.setUnselectable()
		o.calcLocalPosOfRootBone()
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()


def keyReleased(Engine,EngineModule,key,selection):
	pass

