#include "logger.h"
#include "physic_engine.h"
#include <boost/thread.hpp>

PhysicsEngine::PhysicsEngine() :
    mForceFactor(300) {
    Logger::debug(format("creating physics engine: %p") % this);
    setup();
}

PhysicsEngine::~PhysicsEngine(){
    Logger::debug(format("deleting physics engine: %p") % this);
    close();
}

float PhysicsEngine::getForceFactor() {
    return mForceFactor;
}

void PhysicsEngine::setForceFactor(float factor) {
    mForceFactor = factor;
}

void PhysicsEngine::setup(){

    mPhysics = PxCreatePhysics(
        PX_PHYSICS_VERSION,
        mDefaultAllocator, 
        mDefaultErrorCallback,
        PxTolerancesScale(),
        false
        );

    if(!PxInitExtensions(*mPhysics)) {

    }

    mMaterial = mPhysics->createMaterial(0.5f,0.5f,0.5f);

    PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f,-9.81f,0.0f);

	if(!sceneDesc.cpuDispatcher) {
		int cpusToUse = boost::thread::hardware_concurrency() - 1;
		mCpuDispatcher = PxDefaultCpuDispatcherCreate(cpusToUse);
		sceneDesc.cpuDispatcher	= mCpuDispatcher;
	}

    if(!sceneDesc.filterShader) {
        sceneDesc.filterShader  = PxDefaultSimulationFilterShader;
    }
    mScene = mPhysics->createScene(sceneDesc);

}

void PhysicsEngine::simulate(float timing) {
    //mScene->simulate( 1.0f / 60.0f );
    mScene->simulate(timing);
    mScene->fetchResults(true);
}

void PhysicsEngine::close(){
    mScene->release();
    mCpuDispatcher->release();
    mMaterial->release();
    mPhysics->release();
}

PxPhysics* PhysicsEngine::getPhysics() {
    return mPhysics;
}

PxMaterial* PhysicsEngine::getMaterial() {
    return mMaterial;
}

PxScene* PhysicsEngine::getScene() {
    return mScene;
}



