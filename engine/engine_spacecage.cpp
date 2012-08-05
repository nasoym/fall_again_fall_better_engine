#include "logger.h"
#include "math3d.h"

#include "engine_spacecage.h"
#include "engine.h"

#include "physic_plane.h"

EngineSpaceCage::EngineSpaceCage(Engine* engine,Vec3& size) :
	EngineGuiContainer(engine)
	{

	float xSize = size.X();
	float ySize = size.Y();
	float zSize = size.Z();

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
