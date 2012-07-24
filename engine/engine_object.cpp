//-------------------------------------
#include "logger.h"
#include "engine_object.h"
//-------------------------------------

EngineObject::EngineObject(Engine* engine) :
	mEngine(engine)
	{
	mEngine->addObject(this);
}

EngineObject::~EngineObject(){
	mEngine->deleteObject(this);
}

