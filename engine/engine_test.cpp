#include "logger.h"
#include "engine.h"
#include "physic_engine.h"
#include "engine_object.h"

#include "actor.h"
#include "dynamic_actor.h"
#include "physic_shape.h"

void		Engine::test(){
    Logger::debug(format("%1% %2%") % mTimer.getMilliseconds() % mTimer.getMicroseconds());


	DynamicActor*	box = new DynamicActor(this,Vec3(0,100,0));
	Logger::debug("created: dynamic box");

	PhysicShape*	boxShape;

	boxShape = box->addCapsule();
	//boxShape = box->addBox();
	//boxShape = box->addSphere();
	boxShape->setLocalSize(Vec3(60,30,30));

	/*
	boxShape = box->addBox();
	boxShape->setLocalPosition(Vec3(0,10,0));
	boxShape->setLocalSize(Vec3(10,10,10));

	boxShape = box->addBox();
	boxShape->setLocalPosition(Vec3(30,0,0));
	boxShape->setLocalSize(Vec3(10,10,10));
	*/

}

