#ifndef _VEC3_H
#define _VEC3_H

#include <Ogre.h>

#include "PxPhysicsAPI.h"

#include "boost/format.hpp"

class Vec3 : public Ogre::Vector3 {
    public:
		Vec3() : Ogre::Vector3(0,0,0) {}
		Vec3(float x,float y,float z) : Ogre::Vector3(x,y,z) {}
		Vec3(const Ogre::Vector3& ogreVector) : Ogre::Vector3(ogreVector) {}
		Vec3(const physx::PxVec3& physXVector) : Ogre::Vector3(physXVector.x,physXVector.y,physXVector.z) {}
		Vec3(const Vec3 & inputVec) : Ogre::Vector3(
			inputVec.X(),
			inputVec.Y(),
			inputVec.Z()
		) {}

		Vec3    operator *= (const float input_float) {
			x *= input_float;
			y *= input_float;
			z *= input_float;
			return *this;
		}

		Vec3    operator * (const float input_float) {
			return Vec3(toOgre() * input_float);
		}

		Vec3    operator /= (const float input_float) {
			x /= input_float;
			y /= input_float;
			z /= input_float;
			return *this;
		}

		Vec3    operator / (const float input_float) {
			return Vec3(toOgre() / input_float);
		}

		Vec3    operator /= (const Vec3 vec3) {
			x /= vec3.X();
			y /= vec3.Y();
			z /= vec3.Z();
			return *this;
		}
		Vec3    operator / (const Vec3 vec3) {
			return Vec3(
				x / vec3.X(),
				y / vec3.Y(),
				z / vec3.Z()
				);
		}

		Vec3    operator *= (const Vec3 vec3) {
			x *= vec3.X();
			y *= vec3.Y();
			z *= vec3.Z();
			return *this;
		}
		Vec3    operator * (const Vec3 vec3) {
			return Vec3(
				x * vec3.X(),
				y * vec3.Y(),
				z * vec3.Z()
				);
		}

		Vec3    operator += (const Vec3 vec3) {
			x += vec3.X();
			y += vec3.Y();
			z += vec3.Z();
			return *this;
		}
		Vec3    operator + (const Vec3 vec3) {
			return Vec3(toOgre() + vec3.toOgre());
		}

		Vec3    operator -= (const Vec3 vec3) {
			x -= vec3.X();
			y -= vec3.Y();
			z -= vec3.Z();
			return *this;
		}
		Vec3    operator - (const Vec3 vec3) {
			return Vec3(toOgre() - vec3.toOgre());
		}

		float	length() {
			return Ogre::Vector3::length();
		}

		float	distance(const Vec3 vec3) {
			return Ogre::Vector3::distance(vec3.toOgre());
		}

		void	normalise() {
			Ogre::Vector3::normalise();
		}

		double	dot(const Vec3 & vec3) {
			//return Ogre::Vector3::dotProduct(vec3.toOgre());
			//return dotProduct(vec3.toOgre());
			return (
				X()*vec3.X()
				+
				Y()*vec3.Y()
				+
				Z()*vec3.Z()
				);
		}

		Vec3	cross(const Vec3 & vec3) {
			//return Vec3(Ogre::Vector3::crossProduct(vec3.toOgre()));
			//return Vec3(crossProduct(vec3.toOgre()));
			return Vec3(
				Y()*vec3.Z() - Z()*vec3.Y(),
				Z()*vec3.X() - X()*vec3.Z(),
				X()*vec3.Y() - Y()*vec3.X()
				);
		}

		std::string	toString(){
			return (boost::format("%9.9f,%9.9f,%9.9f") % 
					x % y % z).str();
		}

	public:
		physx::PxVec3 toPhysx() const {
			return physx::PxVec3(x,y,z);
		}

		Ogre::Vector3 toOgre() const {
			return *this;
		}

		float	X() const {return x;}
		float	Y() const {return y;}
		float	Z() const {return z;}

};

#endif
