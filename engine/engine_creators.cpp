#include "logger.h"
#include "engine.h"

#include "engine_gui_shape.h"
#include "engine_joint.h"
#include "engine_object.h"
#include "engine_mesh.h"
#include "engine_box.h"

#include "articulation.h"
#include "dynamic_actor.h"
#include "static_actor.h"

EngineObject*	Engine::createGuiBox(){
	return new EngineBox(this);
}

Articulation*	Engine::createArticulation(){
	return new Articulation(this);
}

DynamicActor*	Engine::createDynamicActor(){
	return new DynamicActor(this,Vec3(1,1,1));
}

StaticActor*	Engine::createStaticActor(){
	return new StaticActor(this,Vec3(1,1,1));
}

EngineObject*	Engine::createMesh(const char* meshName){
	return new EngineMesh(this,meshName);
}

EngineObject*	Engine::createJoint(EngineObject* obj1,EngineObject* obj2){
	if (obj1->isActor() && obj2->isActor() ) {
		EngineJoint* engineObject = new EngineJoint(this,obj1->isActor(),obj2->isActor());
		return engineObject;
	}
	return 0;
}
