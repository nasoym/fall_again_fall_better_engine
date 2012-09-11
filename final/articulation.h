#ifndef _ARTICULATION_H
	#define _ARTICULATION_H

#include "PxPhysicsAPI.h"
using namespace physx;

class Engine;

//#include "engine_gui_container.h"
#include "actor.h"

class Articulation : public Actor {
	
	public:
		Articulation(Engine*);
		Articulation(Engine*,Articulation*);
		virtual ~Articulation();

		virtual Articulation*				isArticulation(){return this;}
		virtual ObjectType					getType(){ return ARTICULATION;}

        virtual PxRigidActor*     	getActor(){return mLink;}


		Vec3		getParentAnchor();
		Quat		getParentAnchorOrientation();
		Vec3		getChildAnchor();
		Quat		getChildAnchorOrientation();
		void		setParentAnchor(Vec3 & vec3);
		void		setChildAnchor(Vec3& vec3);
		void		setParentAnchorOrientation(Quat & quat);
		void		setChildAnchorOrientation(Quat & quat);
		Quat		getMotorTarget();
		void		setMotorTarget(Quat & quat);
		void		setSpring(float spring);
		float		getSpring();
		void		setDamping(float damping);
		float		getDamping();
		void		resetMass();
		void		setMass(float mass);
		float		getMass();
		void		wakeUp();
		void		setSolverIterationCounts(float posIters, float velIters);




	public:
		PxArticulation*			getArticulation(){return mArticulation;}
		PxArticulationLink*		getLink(){return mLink;}






	private:
		PxArticulation* 		mArticulation;
		PxArticulationLink*		mLink;
		PxArticulationJoint* 	mJoint;

		Articulation*			mParent;

};
#endif

