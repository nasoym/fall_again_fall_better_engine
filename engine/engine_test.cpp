#include <string>
#include "logger.h"
#include "engine.h"
#include "physic_engine.h"
#include "engine_object.h"

#include "actor.h"
#include "dynamic_actor.h"
#include "physic_shape.h"

#include "memobserver.h"

int			Engine::getMemoryUsage(){
	return getMemoryUsageWorkingSize();
}

void		Engine::log(std::string message){
	Logger::debug(message);
	LogManager::getSingleton().logMessage(message);
}

void		Engine::test(){
    //Logger::debug(format("%1% %2%") % mTimer.getMilliseconds() % mTimer.getMicroseconds());

    //Logger::debug(format("%1%") % getMemoryUsage());


    Logger::debug("articulation test: start");
	PxArticulation*	mArticulation = getPhysicsEngine()->getPhysics()->createArticulation();


    Logger::debug("create link");
    Logger::debug(format("%1%") % mArticulation);
	PxArticulationLink*	mLink = mArticulation->createLink(NULL,
		PxTransform(PxVec3(5,5,5))
		);
    Logger::debug(format("%1%") % mLink);

    Logger::debug("add shape");
	PxShape* shape = mLink->createShape( 
		PxBoxGeometry(PxVec3(5,5,5)), 
		*(getPhysicsEngine()->getMaterial()) 
		);
    Logger::debug("adding 2nd link");
	mLink = mArticulation->createLink(mLink,
		PxTransform(PxVec3(5,5,5))
		);
    Logger::debug(format("%1%") % mLink);
    Logger::debug("add shape");
	shape = mLink->createShape( 
		PxBoxGeometry(PxVec3(5,5,5)), 
		*(getPhysicsEngine()->getMaterial()) 
		);


    Logger::debug("get joint");
	PxArticulationJoint* mJoint = mLink->getInboundJoint();
    Logger::debug(format("%1%") % mJoint);

    Logger::debug("add to scene");
	getPhysicsEngine()->getScene()->addArticulation(
		*mArticulation
	);
    Logger::debug("articulation test: end");


	/*
	DynamicActor*	actor = new DynamicActor(this,Vec3(0,100,0));
	PhysicShape*	shape;

	shape = actor->addCapsule(Vec3(60,30,30));
	*/
	//shape = actor->addBox();
	//shape = actor->addSphere();
	//shape->setLocalSize(Vec3(60,30,30));

	/*
	shape = actor->addCapsule();
	//shape = actor->addBox();
	//shape = actor->addSphere();
	shape->setLocalSize(Vec3(60,30,30));
	shape->setLocalOrientation(Quat().fromAngles(0,45,0));

	shape = actor->addBox();
	shape->setLocalPosition(Vec3(0,10,0));
	shape->setLocalSize(Vec3(10,10,10));

	shape = actor->addBox();
	shape->setLocalPosition(Vec3(30,0,0));
	shape->setLocalSize(Vec3(10,10,10));
	*/

}

