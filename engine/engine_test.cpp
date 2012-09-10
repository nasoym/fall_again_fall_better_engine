#include "logger.h"
#include "engine.h"
#include "physic_engine.h"
#include "engine_object.h"

#include "actor.h"
#include "dynamic_actor.h"
#include "physic_shape.h"

void		Engine::test(){
    //Logger::debug(format("%1% %2%") % mTimer.getMilliseconds() % mTimer.getMicroseconds());


	DynamicActor*	actor = new DynamicActor(this,Vec3(0,100,0));
	PhysicShape*	shape;

	shape = actor->addCapsule(Vec3(60,30,30));
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

