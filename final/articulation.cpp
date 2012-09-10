#include "logger.h"
#include "articulation.h"
#include "engine.h"
#include "physic_engine.h"

Articulation::Articulation(Engine* engine) :
	EngineGuiContainer(engine),
	mParent(0),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{
	mArticulation = getEngine()->getPhysicsEngine()->getPhysics()->createArticulation();
	mLink = mArticulation->createLink(0,PxTransform());
	mJoint =mLink->getInboundJoint();
}

Articulation::Articulation(Engine* engine,Articulation* parentLink) :
	EngineGuiContainer(engine),
	mParent(parentLink),
	mArticulation(0),
	mLink(0),
	mJoint(0)
	{
	if(mParent) mArticulation = mParent->getArticulation();
	mLink = mArticulation->createLink(mParent->getLink(),PxTransform());
	mJoint =mLink->getInboundJoint();
}

Articulation::~Articulation( ) {

}

