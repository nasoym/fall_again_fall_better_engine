#ifndef _QUAT_H
#define _QUAT_H

#include <Ogre.h>
#include <math.h>
#include <string>

#include "PxPhysicsAPI.h"

#include "boost/format.hpp"

/*
#ifndef PI
	#define 	PI (3.14159265f)
#endif
#ifndef DEG2RAD
	#define 	DEG2RAD (PI / 180.0f)
#endif 
#ifndef RAD2DEG
	#define 	RAD2DEG (180.0f / PI)
#endif 
*/

class Quat : public Ogre::Quaternion {
    public: // Constructors
		Quat() : Ogre::Quaternion(1,0,0,0) {}
		Quat(float iw,float ix,float iy,float iz) : Ogre::Quaternion(iw,ix,iy,iz) {}
		Quat(const Ogre::Quaternion& ogreQuaternion) : Ogre::Quaternion(ogreQuaternion) {}
		Quat(const physx::PxQuat& physXQuat) : Ogre::Quaternion(physXQuat.w,physXQuat.x,physXQuat.y,physXQuat.z) {}
		Quat(const float angle,const Vec3 & axis) :
			Ogre::Quaternion(Ogre::Radian(angle),axis.toOgre()) {}

		Quat(const Quat & inputQuat) : Ogre::Quaternion(
			inputQuat.W(),
			inputQuat.X(),
			inputQuat.Y(),
			inputQuat.Z()
		) { }

	public:

		Quat fromTwoVectors(Vec3 & vec1, Vec3 & vec2) {
			Ogre::Quaternion q = vec1.toOgre().getRotationTo(vec2.toOgre());	
			w = q.w;
			x = q.x;
			y = q.y;
			z = q.z;
/*
			Vec3 vector1 = Vec3(vec1);
			Vec3 vector2 = Vec3(vec2);
			vector1.normalise();
			vector2.normalise();
			double	dot = vector1.dot(vector2);
			//double	angle = acos(dot);
			Vec3 cross = vector1.cross(vector2);
			double	qw = sqrt(
				(vector1.length() * vector1.length())
				*
				(vector2.length() * vector2.length())
				+
				dot
				);
			w = sqrt(dot);
			x = cross.X();
			y = cross.Y();
			z = cross.Z();
			normalise();
			//FromAngleAxis(
		//		Ogre::Radian(Ogre::Real(angle)),
		//		Vec3(cross).toOgre()
		//	);
		*/
			return *this;
		}

		Quat fromAngles(float t,float p,float r) {
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

		Vec3	toAngles(){
			Ogre::Matrix3	rotationMatrix = Ogre::Matrix3();
			ToRotationMatrix(rotationMatrix);
			Ogre::Radian x,y,z;
			rotationMatrix.ToEulerAnglesXYZ(x,y,z);
		  	return Vec3(
				x.valueDegrees(),
				y.valueDegrees(),
				z.valueDegrees());
		}

		Quat	fromAngleAxis(float angle,Vec3 axis) {
			FromAngleAxis(
				Ogre::Degree(angle),
				axis.toOgre()
			);
			//normalise();
			return *this;
		}

		Vec3	toAxis(){
			Ogre::Vector3	axis;
			Ogre::Radian	angle;
			ToAngleAxis(angle,axis);
			return Vec3(axis);
		}

		float	toAngle(){
			Ogre::Vector3	axis;
			Ogre::Radian	angle;
			ToAngleAxis(angle,axis);
			return angle.valueDegrees();
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

		std::string	toString(){
			return (boost::format("%3.3f %3.3f %3.3f %3.3f") % 
					w % x % y % z).str();
		}

    public: // Converters
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
