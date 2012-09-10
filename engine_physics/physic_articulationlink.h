#ifndef _ARTICULATION_LINK_H
	#define _ARTICULATION_LINK_H

#include "PxPhysicsAPI.h"
using namespace physx;

class PhysicsEngine;

class PhysicArticulationLink {
	
	public:
		PhysicArticulationLink(PhysicsEngine*);
		PhysicArticulationLink(PhysicsEngine*,PhysicArticulationLink*);
		virtual ~PhysicArticulationLink();



	public:
		PxArticulation*			getArticulation(){return mArticulation;}
		PxArticulationLink*		getLink(){return mLink;}

	private:
		PhysicsEngine*      	mEngine;
		PxArticulation* 		mArticulation;
		PxArticulationLink*		mLink;
		PxArticulationJoint* 	mJoint;

		PhysicArticulationLink*	mParentLink;

};
#endif

