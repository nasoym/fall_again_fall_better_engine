#include "logger.h"
#include "engine.h"

#include "physic_box.h"
#include "physic_static.h"

#include "engine_gui_shape.h"
#include "engine_spacecage.h"
#include "engine_body.h"
#include "engine_joint.h"
#include "engine_object.h"
#include "engine_mesh.h"

EngineObject*	Engine::createMesh(const char* meshName){
	EngineMesh* engineObject = new EngineMesh(this,meshName);
	//engineObject->setSize(Vec3(10,1,10));
	//engineObject->setPosition(Vec3(0,-0.5,0));
	return engineObject;
}

EngineObject*	Engine::createGuiBox(){
	EngineGuiShape* engineObject = new EngineGuiShape(this);
	engineObject->createBoxEntity();
	engineObject->setSize(Vec3(10,1,10));
	engineObject->setPosition(Vec3(0,-0.5,0));
	return engineObject;
}

EngineObject*	Engine::createPhysicStatic(){
	EngineBody* engineObject = new EngineBody(this);
	engineObject->setPhysicBody(
		new PhysicStatic(
			getPhysicsEngine(),
			Vec3(0,0,0),
			Vec3(1,1,1)
			)
	);
	engineObject->setGuiUpdatesOff();
	engineObject->createBoxEntity();
	engineObject->setSize(Vec3(1,1,1));
	engineObject->setPosition(Vec3(0,150,0));
	return engineObject;
}

EngineObject*	Engine::createPhysicBox(){
	EngineBody* engineObject = new EngineBody(this);
	engineObject->setPhysicBody(
		new PhysicBox(
			getPhysicsEngine(),
			Vec3(0,0,0),
			Vec3(1,1,1)
			)
	);
	engineObject->createBoxEntity();
	engineObject->setSize(Vec3(1,1,1));
	engineObject->setPosition(Vec3(0,150,0));
	return engineObject;
}

EngineObject*	Engine::createJoint(EngineObject* obj1,EngineObject* obj2){
	if (obj1->isBody() && obj2->isBody() ) {
		EngineJoint* engineObject = new EngineJoint(this,obj1->isBody(),obj2->isBody());
		return engineObject;
	}
	return 0;
}

EngineObject*	Engine::createSpaceCage(Vec3& size){
	EngineSpaceCage* spaceCage = new EngineSpaceCage(this,size);
	spaceCage->createBoxEntity();
	spaceCage->setColour(1.0f,1.0f,1.0f,0.3f);
	spaceCage->setSize(Vec3(size.X(),1,size.Z()));
	spaceCage->setPosition(Vec3(0,-0.5,0));
	return spaceCage;
}



