#ifndef _QUAT_H
#define _QUAT_H

#include <Ogre.h>

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>

#include "PxPhysicsAPI.h"

class Quat : public Ogre::Quaternion {
    public: // Constructors
		Quat() : Ogre::Quaternion(1,0,0,0) {}
		Quat(float iw,float ix,float iy,float iz) : Ogre::Quaternion(iw,ix,iy,iz) {}
		Quat(boost::python::object& tupleObject) : Ogre::Quaternion() {
			w = boost::python::extract<float>(tupleObject[0]);
			x = boost::python::extract<float>(tupleObject[1]);
			y = boost::python::extract<float>(tupleObject[2]);
			z = boost::python::extract<float>(tupleObject[3]);
		}
		Quat(const Ogre::Quaternion& ogreQuaternion) : Ogre::Quaternion(ogreQuaternion) {}
		Quat(const physx::PxQuat& physXQuat) : Ogre::Quaternion(physXQuat.w,physXQuat.x,physXQuat.y,physXQuat.z) {}

		Quat(const Quat & inputQuat) : Ogre::Quaternion(
			inputQuat.W(),
			inputQuat.X(),
			inputQuat.Y(),
			inputQuat.Z()
		) { }

	public:
		Quat tupleFromAngle(boost::python::object& tupleObject) {
			fromAngle(
				boost::python::extract<float>(tupleObject[0]),
				boost::python::extract<float>(tupleObject[1]),
				boost::python::extract<float>(tupleObject[2])
			);
			return *this;
		}

		Quat fromAngle(float t,float p,float r) {
			Ogre::Matrix3	rotationMatrix = Ogre::Matrix3();
			rotationMatrix.FromEulerAnglesXYZ(
				Ogre::Degree(t),
				Ogre::Degree(p),
				Ogre::Degree(r)
			);
			FromRotationMatrix(rotationMatrix);
			normalise();
			return *this;
		}

		Vec3    operator * (const Vec3 vec3) {
			// rotate vec3 by quaternion
			return Vec3(toOgre() * vec3.toOgre());
		}

		Quat    operator * (const Quat quat) {
			return Quat(toOgre() * quat.toOgre());
		}

		Quat    operator + (const Quat quat) {
			return Quat(toOgre() + quat.toOgre());
		}

		Quat    operator - (const Quat quat) {
			return Quat(toOgre() - quat.toOgre());
		}


		Quat	inverse() {
			return Quat(Inverse());
		}

		void	normalise() {
			Ogre::Quaternion::normalise();
		}


    public: // Converters
		boost::python::tuple toTuple() const{
			return boost::python::make_tuple(w,x,y,z);
		}
		physx::PxQuat toPhysx() const {
			return physx::PxQuat(x,y,z,w);
		}
		Ogre::Quaternion toOgre() const {
			return *this;
		}

		float	W() const {return w;}
		float	X() const {return x;}
		float	Y() const {return y;}
		float	Z() const {return z;}

	public:
};

#endif
