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

EngineObject*	Engine::createLLBox(){
	return new EngineBox(this);
}

EngineObject*	Engine::createLLSpaceCage(Vec3& size){
	return new EngineSpaceCage(this,size);
}

EngineObject*	Engine::createLLMesh(const char* meshName){
	return new EngineMesh(this,meshName);
}

EngineObject*	Engine::createLLPhysicBody(){
	EngineBody* engineObject = new EngineBody(this);
	engineObject->setPhysicBody(
		new PhysicBox(getPhysicsEngine(),
			Vec3(0,0,0), Vec3(1,1,1) ) );
	return engineObject;
}

EngineObject*	Engine::createLLPhysicStatic(){
	EngineStaticBody* engineObject = new EngineStaticBody(this);
	engineObject->setPhysicBody(
		new PhysicStatic( getPhysicsEngine(),
			Vec3(0,0,0), Vec3(1,1,1) ) );
	return engineObject;
}

EngineObject*	Engine::createLLJoint(EngineObject* obj1,EngineObject* obj2){
	if (obj1->isBody() && obj2->isBody() ) {
		EngineJoint* engineObject = new EngineJoint(this,obj1->isBody(),obj2->isBody());
		return engineObject;
	}
	return 0;
}






EngineObject*	Engine::createGuiBox(){
	EngineBox* engineObject = new EngineBox(this);
	return engineObject;
}

EngineObject*	Engine::createSpaceCage(Vec3& size){
	EngineSpaceCage* engineObject = new EngineSpaceCage(this,size);

	float wall = 1.0;
	float ground_opacity = 1.0;
	float ceiling_opacity = 0.25;
	float wall_opacity = 0.1;
	float red = 1.0;
	float green = 1.0;
	float blue = 1.0;

	EngineBox* shape;
	shape = new EngineBox(this);
	shape->setScalingNone();
	shape->setColour(red,green,blue,ground_opacity);
	shape->setSize(Vec3(size.X(),wall,size.Z()));
	shape->setPosition(Vec3(0,-wall,0));
	engineObject->addShape(shape);

	shape = new EngineBox(this);
	shape->setScalingNone();
	shape->setColour(red,green,blue,ceiling_opacity);
	shape->setSize(Vec3(size.X(),wall,size.Z()));
	shape->setPosition(Vec3(0,size.Y() + wall,0));
	engineObject->addShape(shape);

	shape = new EngineBox(this);
	shape->setScalingNone();
	shape->setColour(red,green,blue,wall_opacity);
	shape->setSize(Vec3(size.X(),size.Y()*0.5,wall));
	shape->setPosition(Vec3(0,size.Y()*0.5,size.Z()+wall));
	engineObject->addShape(shape);

	shape = new EngineBox(this);
	shape->setScalingNone();
	shape->setColour(red,green,blue,wall_opacity);
	shape->setSize(Vec3(size.X(),size.Y()*0.5,wall));
	shape->setPosition(Vec3(0,size.Y()*0.5,-size.Z()-wall));
	engineObject->addShape(shape);

	shape = new EngineBox(this);
	shape->setScalingNone();
	shape->setColour(red,green,blue,wall_opacity);
	shape->setSize(Vec3(wall,size.Y()*0.5,size.Z()));
	shape->setPosition(Vec3(size.X()+wall,size.Y()*0.5,0));
	engineObject->addShape(shape);

	shape = new EngineBox(this);
	shape->setScalingNone();
	shape->setColour(red,green,blue,wall_opacity);
	shape->setSize(Vec3(wall,size.Y()*0.5,size.Z()));
	shape->setPosition(Vec3(-size.X()-wall,size.Y()*0.5,0));
	engineObject->addShape(shape);

	return engineObject;
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




