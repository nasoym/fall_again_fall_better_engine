#ifndef _ARTICULATION_H
	#define _ARTICULATION_H

#include "PxPhysicsAPI.h"
using namespace physx;

class Engine;

#include "engine_gui_container.h"

class Articulation : public EngineGuiContainer {
	
	public:
		Articulation(Engine*);
		Articulation(Engine*,Articulation*);
		virtual ~Articulation();

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


