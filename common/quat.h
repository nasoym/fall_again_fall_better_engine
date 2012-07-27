#ifndef _QUAT_H
#define _QUAT_H

#include <Ogre.h>

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>

#include "PxPhysicsAPI.h"

class Quat {
    public: // Constructors
		Quat() : mQuaternion() {}
		Quat(float w,float x,float y,float z) : mQuaternion(w,x,y,z) {}
		Quat(boost::python::object& tupleObject) : mQuaternion() {
			mQuaternion.w = boost::python::extract<float>(tupleObject[0]);
			mQuaternion.x = boost::python::extract<float>(tupleObject[1]);
			mQuaternion.y = boost::python::extract<float>(tupleObject[2]);
			mQuaternion.z = boost::python::extract<float>(tupleObject[3]);
		}
		Quat(Ogre::Quaternion& ogreQuaternion) : mQuaternion(ogreQuaternion) {}
		Quat(const Ogre::Quaternion& ogreQuaternion) : mQuaternion(ogreQuaternion) {}
		Quat(physx::PxQuat& physXQuat) : mQuaternion(physXQuat.w,physXQuat.x,physXQuat.y,physXQuat.z) {}
		Quat(const physx::PxQuat& physXQuat) : mQuaternion(physXQuat.w,physXQuat.x,physXQuat.y,physXQuat.z) {}

		Quat(const Quat & inputQuat) : mQuaternion(
			inputQuat.W(),
			inputQuat.X(),
			inputQuat.Y(),
			inputQuat.Z()
		) { }

	public:
		void tupleFromAngle(boost::python::object& tupleObject) {
			fromAngle(
				boost::python::extract<float>(tupleObject[0]),
				boost::python::extract<float>(tupleObject[1]),
				boost::python::extract<float>(tupleObject[2])
			);
		}

		void fromAngle(float t,float p,float r) {
			Ogre::Matrix3	rotationMatrix = Ogre::Matrix3();
			rotationMatrix.FromEulerAnglesXYZ(
				//Ogre::Degree(t),
				//Ogre::Degree(p),
				//Ogre::Degree(r)
				Ogre::Radian(t),
				Ogre::Radian(p),
				Ogre::Radian(r)
			);
			mQuaternion.FromRotationMatrix(rotationMatrix);
			mQuaternion.normalise();
		}

    public: // Converters
		boost::python::tuple toTuple(){
			return boost::python::make_tuple(mQuaternion.w,mQuaternion.x, mQuaternion.y,mQuaternion.z);
		}
		physx::PxQuat toPhysx(){
			return physx::PxQuat(mQuaternion.x, mQuaternion.y,mQuaternion.z,mQuaternion.w);
		}
		Ogre::Quaternion toOgre(){
			return Ogre::Quaternion(mQuaternion.w,mQuaternion.x, mQuaternion.y,mQuaternion.z);
		}

		float	W(){return mQuaternion.w;}
		float	X(){return mQuaternion.x;}
		float	Y(){return mQuaternion.y;}
		float	Z(){return mQuaternion.z;}

		float	W() const {return mQuaternion.w;}
		float	X() const {return mQuaternion.x;}
		float	Y() const {return mQuaternion.y;}
		float	Z() const {return mQuaternion.z;}

	public:
		Ogre::Quaternion	mQuaternion;
};

#endif
