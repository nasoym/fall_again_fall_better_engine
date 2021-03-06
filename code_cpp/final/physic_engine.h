#ifndef _PHYSIC_ENGINE_H
#define _PHYSIC_ENGINE_H

#include "logger.h"

#include "PxPhysicsAPI.h"
#include "PxDefaultErrorCallback.h"
#include "PxErrorCallback.h"

#include "PxDefaultCpuDispatcher.h"
#include "PxExtensionsAPI.h"
#include "math3d.h"
using namespace physx;

class Allocator : public PxAllocatorCallback {
#ifdef MACOSX
    void* allocate(size_t size, const char*, const char*, int) {
        void *ptr = ::malloc(size);	
        PX_ASSERT((reinterpret_cast<size_t>(ptr) & 15)==0);
        return ptr;
    }
    void deallocate(void* ptr) {
        ::free(ptr);			
    }
#else
    void * allocate(size_t size,const char*,const char*,int) {
        return _aligned_malloc(size,16);
    }
    void deallocate(void * ptr) {
        _aligned_free(ptr);
    }
#endif
};

//class ErrorCallback: public PxDefaultErrorCallback {
class ErrorCallback: public PxErrorCallback {
    virtual void reportError(PxErrorCode::Enum code, const char* message, const char* file, int line){
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


		Vec3		getGravity(){return Vec3(mScene->getGravity());}
		void		setGravity(Vec3 & vec3){mScene->setGravity(vec3.toPhysx());}

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
