#ifndef _PHYSIC_ENGINE_H
#define _PHYSIC_ENGINE_H

#include "logger.h"

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

class ErrorCallback: public PxDefaultErrorCallback {
	void reportError(
		PxErrorCode code, const char * message,const char* file, int line){
			Logger::debug(
				format("PhysX Error: message:%1% file:%2% line:%3%") %
				message %
				file %
				line
				);
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

        //PxDefaultErrorCallback	    mDefaultErrorCallback;
        ErrorCallback	    mDefaultErrorCallback;
        Allocator                   mDefaultAllocator;
		PxFoundation * 				mFoundation;
		//PxSimulationFilterShader* gDefaultFilterShader;

        PxPhysics *                 mPhysics;
        PxMaterial *                mMaterial; 
        PxScene *                   mScene;
        PxDefaultCpuDispatcher *    mCpuDispatcher;

        float                       mForceFactor;
};
#endif
