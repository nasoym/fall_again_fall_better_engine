
#include <stdio.h>

#include <Ogre.h>
using namespace Ogre;

#include "PxPhysicsAPI.h"
#include "PxDefaultErrorCallback.h"
#include "PxDefaultCpuDispatcher.h"
#include "PxExtensionsAPI.h"
using namespace physx;

class Allocator : public PxAllocatorCallback {
    void * allocate(size_t size,const char*,const char*,int) {
        return _aligned_malloc(size,16);
    }
    void deallocate(void * ptr) {
        _aligned_free(ptr);
    }
};
        PxDefaultErrorCallback	    mDefaultErrorCallback;
        Allocator                   mDefaultAllocator;

        PxPhysics *                 mPhysics;
        PxMaterial *                mMaterial; 
        PxScene *                   mScene;
        PxDefaultCpuDispatcher *    mCpuDispatcher;

int main(int argc, char *argv[]) {
	printf("starting");
	//Root *root = new Root("","");
	Root *root = new Root();
	root->showConfigDialog();
	root->initialise(true);


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
		mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
		sceneDesc.cpuDispatcher	= mCpuDispatcher;
	}

    if(!sceneDesc.filterShader) {
        sceneDesc.filterShader  = PxDefaultSimulationFilterShader;
    }
    mScene = mPhysics->createScene(sceneDesc);


	root->startRendering();
	printf("hello");
	return 0;
}
