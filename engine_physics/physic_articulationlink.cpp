#include "physic_articulationlink.h"
#include "physic_engine.h"


PhysicArticulationLink::PhysicArticulationLink(PhysicsEngine* engine) :
	mEngine(engine),
	mParentLink(0),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{
	mArticulation = (mEngine->getPhysics())->createArticulation();
	mLink = mArticulation->createLink(0,PxTransform());
	mJoint =mLink->getInboundJoint();
}

PhysicArticulationLink::PhysicArticulationLink(PhysicsEngine* engine,PhysicArticulationLink* parentLink) :
	mEngine(engine),
	mParentLink(parentLink),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{

	if(parentLink){
		mArticulation = parentLink->getArticulation();
	}
	mLink = mArticulation->createLink(parentLink->getLink(),PxTransform());
	mJoint =mLink->getInboundJoint();

}

PhysicArticulationLink::~PhysicArticulationLink( ) {
}

