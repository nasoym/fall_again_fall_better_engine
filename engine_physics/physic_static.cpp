#include "physic_static.h"
#include "physic_engine.h"
#include "logger.h"

PhysicStatic::PhysicStatic(PhysicsEngine* engine, Vec3& position,Vec3& size) :
	PhysicBody(),
	mEngine(engine),
	mBody(0),
	mShape(0)
	{
    mBody = (mEngine->getPhysics())->createRigidStatic( PxTransform(position.toPhysx()) );
    mShape = mBody->createShape( PxBoxGeometry(size.toPhysx()), *(mEngine->getMaterial()) );
    (mEngine->getScene())->addActor(*mBody);
}

PhysicStatic::~PhysicStatic( ){
    mBody->release();
    mBody = 0;
}

Vec3	PhysicStatic::getSize() {
	PxBoxGeometry	boxGeometry;
	if (mShape->getBoxGeometry(boxGeometry)) {
		return Vec3(boxGeometry.halfExtents);
	}
	return Vec3();
}

void    PhysicStatic::setSize(Vec3 vec3) {
    mShape->setGeometry(PxBoxGeometry(
		vec3.toPhysx()
		));
}


