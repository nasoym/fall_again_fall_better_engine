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
		Quat() : mQuaternion(1,0,0,0) {}
		Quat(float w,float x,float y,float z) : mQuaternion(w,x,y,z) {}
		Quat(boost::python::object& tupleObject) : mQuaternion() {
			mQuaternion.w = boost::python::extract<float>(tupleObject[0]);
			mQuaternion.x = boost::python::extract<float>(tupleObject[1]);
			mQuaternion.y = boost::python::extract<float>(tupleObject[2]);
			mQuaternion.z = boost::python::extract<float>(tupleObject[3]);
		}
		Quat(const Ogre::Quaternion& ogreQuaternion) : mQuaternion(ogreQuaternion) {}
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
				Ogre::Degree(t),
				Ogre::Degree(p),
				Ogre::Degree(r)
			);
			mQuaternion.FromRotationMatrix(rotationMatrix);
			mQuaternion.normalise();
		}

		Vec3    operator * (const Vec3 vec3) {
			return Vec3(mQuaternion * vec3.toOgre());
		}

		Quat    operator * (const Quat quat) {
			return Quat(mQuaternion * quat.toOgre());
		}

		Quat    operator + (const Quat quat) {
			return Quat(mQuaternion + quat.toOgre());
		}

		Quat    operator - (const Quat quat) {
			return Quat(mQuaternion - quat.toOgre());
		}


		Quat	inverse() {
			return Quat(mQuaternion.Inverse());
		}

		void	normalise() {
			mQuaternion.normalise();
		}


    public: // Converters
		boost::python::tuple toTuple() const{
			return boost::python::make_tuple(mQuaternion.w,mQuaternion.x, mQuaternion.y,mQuaternion.z);
		}
		physx::PxQuat toPhysx() const {
			return physx::PxQuat(mQuaternion.x, mQuaternion.y,mQuaternion.z,mQuaternion.w);
		}
		Ogre::Quaternion toOgre() const {
			return Ogre::Quaternion(mQuaternion.w,mQuaternion.x, mQuaternion.y,mQuaternion.z);
		}

		float	W() const {return mQuaternion.w;}
		float	X() const {return mQuaternion.x;}
		float	Y() const {return mQuaternion.y;}
		float	Z() const {return mQuaternion.z;}

	public:
		Ogre::Quaternion	mQuaternion;
};

#endif
