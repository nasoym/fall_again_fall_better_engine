#include "dynamic_actor.h"
#include "engine.h"
#include "physic_engine.h"


DynamicActor::DynamicActor(Engine* engine, Vec3 & position) :
	Actor(engine),
	mBody(0)
	{
    mBody = (getEngine()->getPhysicsEngine()->getPhysics())->createRigidDynamic( PxTransform(position.toPhysx()) );
    (getEngine()->getPhysicsEngine()->getScene())->addActor(*mBody);

	//setSolverIterations(16,4);
	//setSolverIterations(16,2);
	//setSolverIterations(32,16);
	//setSolverIterations(64,32);
	setSolverIterations(16,4);
}

DynamicActor::~DynamicActor( ){
    mBody->release();
    mBody = 0;
}

void    DynamicActor::wakeUp() {
    mBody->wakeUp();
}

void		DynamicActor::addForce(Vec3 force){
	mBody->addForce(
		force.toPhysx(),
		PxForceMode::eIMPULSE
		);
}

void DynamicActor::resetMass(){
    PxRigidBodyExt::updateMassAndInertia(*mBody, 1.0f);
    wakeUp();
}

void DynamicActor::setMass(float mass){
	mBody->setMass(mass);
    wakeUp();
}

float DynamicActor::getMass(){
	return mBody->getMass();
}

void DynamicActor::setSolverIterations(int i1,int i2){
	mBody->setSolverIterationCounts(i1,i2);
    wakeUp();
}

