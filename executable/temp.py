import libxml2
import mesh

def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,objects,key):
	pass

def keyPressed(Engine,EngineModule,objects,key):
	if key == EngineModule.Keys.K_T:
		#Engine.setTimingFactor(0.0001)
		#print("timingfactor: " +str(Engine.getTimingFactor()))

		o = Engine.createMesh("Character.mesh")
		#o.setColour(1,0,0,0.2)
		o.setColour(1,0,0,0.9)
		#o.setSize(EngineModule.Vec3(1000,1000,1000))
		mesh.createBones(Engine,EngineModule,o)
		#Engine.simulatePhysics(1.0/60.0)
		#Engine.physicPauseToggle()


def keyReleased(Engine,EngineModule,objects,key):
	pass

