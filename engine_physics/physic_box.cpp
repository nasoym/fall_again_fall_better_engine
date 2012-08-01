#include "physic_box.h"
#include "physic_engine.h"
#include "logger.h"

PhysicBox::PhysicBox(PhysicsEngine* engine, Vec3& position,Vec3& size) :
	PhysicBody(),
	mEngine(engine),
	mBody(0),
	mShape(0)
	{
    mBody = (mEngine->getPhysics())->createRigidDynamic( PxTransform(position.toPhysx()) );
    mShape = mBody->createShape( PxBoxGeometry(size.toPhysx()), *(mEngine->getMaterial()) );
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    (mEngine->getScene())->addActor(*mBody);
}

PhysicBox::~PhysicBox( ){
    mBody->release();
    mBody = 0;
}

void    PhysicBox::wakeUp() {
    mBody->wakeUp();
}

Vec3	PhysicBox::getSize() {
	PxBoxGeometry	boxGeometry;
	if (mShape->getBoxGeometry(boxGeometry)) {
		return Vec3(boxGeometry.halfExtents);
	}
	return Vec3();
}

void    PhysicBox::setSize(Vec3 vec3) {
    mShape->setGeometry(PxBoxGeometry(
		vec3.toPhysx()
		));
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    wakeUp();
}

