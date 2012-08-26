#ifndef _PHYSIC_BODY_H
#define _PHYSIC_BODY_H

class BaseJoint;

#include "PxPhysicsAPI.h"
using namespace physx;

#include <vector>
#include "math3d.h"

class PhysicBody {
	protected:
		std::vector<BaseJoint*>    mJoints;

	public:
		PhysicBody();
		virtual ~PhysicBody();
		virtual PxRigidActor*   getBody(){return 0;}
		virtual void            wakeUp(){}

		virtual Vec3	  	getPosition();
		virtual Quat	  	getOrientation();
		virtual Vec3	  	getSize();

		virtual void	  	setPosition(Vec3);
		virtual void	  	setOrientation(Quat);
		virtual void	  	setSize(Vec3);

		virtual void    	deleteAllJoints();
		virtual void    	deleteJoint(BaseJoint* joint);
		virtual int     	howManyJoints();
		virtual void    	addJoint(BaseJoint* joint);
		virtual BaseJoint*  getJoint(int index);

		virtual void		addForce(Vec3);

		virtual void 		dsetSolverIterations(int i1,int i2){}
		virtual void 		setMass(float mass){}
		virtual float		getMass(){return 0;}

};
#endif
