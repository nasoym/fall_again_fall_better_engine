#include "logger.h"
#include "engine.h"

#include "physic_box.h"
#include "physic_static.h"

#include "engine_gui_shape.h"
#include "engine_spacecage.h"
#include "engine_body.h"
#include "engine_static_body.h"
#include "engine_joint.h"
#include "engine_object.h"
#include "engine_mesh.h"
#include "engine_box.h"

#include "articulation.h"
#include "dynamic_actor.h"

EngineObject*	Engine::createGuiBox(){
	return new EngineBox(this);
}

Articulation*	Engine::createArticulation(){
	return new Articulation(this);
}

DynamicActor*	Engine::createDynamicActor(){
	return new DynamicActor(this,Vec3(1,1,1));
}

EngineObject*	Engine::createSpaceCage(Vec3& size){
	return new EngineSpaceCage(this,size);
}

EngineObject*	Engine::createPhysicBox(){
	EngineBody* engineObject = new EngineBody(this);
	engineObject->setPhysicBody(
		new PhysicBox(getPhysicsEngine(),
			Vec3(0,0,0), Vec3(1,1,1) ) );
	return engineObject;
}

EngineObject*	Engine::createMesh(const char* meshName){
	return new EngineMesh(this,meshName);
}

EngineObject*	Engine::createPhysicStatic(){
	EngineStaticBody* engineObject = new EngineStaticBody(this);
	engineObject->setPhysicBody(
		new PhysicStatic( getPhysicsEngine(),
			Vec3(0,0,0), Vec3(1,1,1) ) );
	return engineObject;
}

EngineObject*	Engine::createJoint(EngineObject* obj1,EngineObject* obj2){
	if (obj1->isBody() && obj2->isBody() ) {
		EngineJoint* engineObject = new EngineJoint(this,obj1->isBody(),obj2->isBody());
		return engineObject;
	}
	return 0;
}
