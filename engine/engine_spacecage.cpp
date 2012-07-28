#include "engine_spacecage.h"
#include "logger.h"

#include "math3d.h"

EngineSpaceCage::EngineSpaceCage(Engine* engine) :
	EngineGuiShape(engine)
	{
	float ySize = 400;
	float xSize = 200;
	float zSize = 200;

	mBottomPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,0,0), Quat().fromAngle(0,0,90).toPhysx() );

	mTopPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,ySize,0), Quat().fromAngle(0,0,-90).toPhysx() );

	mFrontPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,0,zSize), Quat().fromAngle(0,90,0).toPhysx() );

	mBackPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(0,0,-zSize), Quat().fromAngle(0,-90,0).toPhysx() );

	mLeftPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(xSize,0,0), Quat().fromAngle(0,0,180).toPhysx() );

	mRightPlane = new PhysicPlane( getEngine()->getPhysicsEngine(),
		PxVec3(-xSize,0,0), Quat().fromAngle(0,0,0).toPhysx() );
}
