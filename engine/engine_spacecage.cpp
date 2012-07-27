#include "engine_spacecage.h"
#include "logger.h"

#include "math3d.h"

EngineSpaceCage::EngineSpaceCage(Engine* engine) :
	EngineGuiShape(engine)
	{
	Quat	rotation = Quat();
	rotation.fromAngle(0,0,90);
	mBottomPlane = new PhysicPlane(
		getEngine()->getPhysicsEngine(),
		PxVec3(0,0,0),
		rotation.toPhysx()
	);

}
