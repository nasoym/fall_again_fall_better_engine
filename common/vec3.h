#ifndef _VEC3_H
#define _VEC3_H

#include <Ogre.h>

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>

#include "PxPhysicsAPI.h"

class Vec3 {
    public:
		Vec3() : mVector() {}
		Vec3(float x,float y,float z) : mVector(x,y,z) {}
		Vec3(boost::python::object& tupleObject) : mVector() {
			mVector.x = boost::python::extract<float>(tupleObject[0]);
			mVector.y = boost::python::extract<float>(tupleObject[1]);
			mVector.z = boost::python::extract<float>(tupleObject[2]);
		}
		Vec3(Ogre::Vector3& ogreVector) : mVector(ogreVector) {}
		Vec3(const Ogre::Vector3& ogreVector) : mVector(ogreVector) {}
		Vec3(physx::PxVec3& physXVector) : mVector(physXVector.x,physXVector.y,physXVector.z) {}
		Vec3(const physx::PxVec3& physXVector) : mVector(physXVector.x,physXVector.y,physXVector.z) {}
		Vec3(const Vec3 & inputVec) : mVector(
			inputVec.X(),
			inputVec.Y(),
			inputVec.Z()
		) {}


		Vec3    operator *= (const float input_float) {
			mVector *= input_float;
			return *this;
		}

		Vec3    operator * ( const float input_float) {
			return Vec3(mVector * input_float);
		}


	public:
		boost::python::tuple toTuple(){
			return boost::python::make_tuple(mVector.x, mVector.y,mVector.z);
		}
		physx::PxVec3 toPhysx(){
			return physx::PxVec3(mVector.x, mVector.y,mVector.z);
		}
		Ogre::Vector3 toOgre(){
			return Ogre::Vector3(mVector.x, mVector.y,mVector.z);
		}

		float	X(){return mVector.x;}
		float	Y(){return mVector.y;}
		float	Z(){return mVector.z;}

		float	X() const {return mVector.x;}
		float	Y() const {return mVector.y;}
		float	Z() const {return mVector.z;}

	public:
		Ogre::Vector3	mVector;
};

#endif
