#ifndef _PHYSIC_ENGINE_H
#define _PHYSIC_ENGINE_H

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

class PhysicsEngine {
    public:
        PhysicsEngine();
        ~PhysicsEngine();
        void            simulate(float);
        float           getForceFactor();
        void            setForceFactor(float);

    public:
        PxPhysics*  getPhysics();
        PxMaterial* getMaterial();
        PxScene*    getScene();

    private:
        void    setup();
        void    close();

    private:

        PxDefaultErrorCallback	    mDefaultErrorCallback;
        Allocator                   mDefaultAllocator;

        PxPhysics *                 mPhysics;
        PxMaterial *                mMaterial; 
        PxScene *                   mScene;
        PxDefaultCpuDispatcher *    mCpuDispatcher;

        float                       mForceFactor;
};
#endif
