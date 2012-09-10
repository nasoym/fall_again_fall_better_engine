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

    (mEngine->getScene())->addActor(*mBody);

    mShape = mBody->createShape( PxBoxGeometry(size.toPhysx()), *(mEngine->getMaterial()) );
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);

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

void		PhysicBox::addForce(Vec3 force){
	mBody->addForce(
		force.toPhysx(),
		PxForceMode::eIMPULSE
		);
}

void PhysicBox::dsetSolverIterations(int i1,int i2){
	mBody->setSolverIterationCounts(i1,i2);
    wakeUp();
}

void PhysicBox::resetMass(){
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    wakeUp();
}

void PhysicBox::setMass(float mass){
	mBody->setMass(mass);
    //PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    wakeUp();
}

float PhysicBox::getMass(){
	return mBody->getMass();
}

