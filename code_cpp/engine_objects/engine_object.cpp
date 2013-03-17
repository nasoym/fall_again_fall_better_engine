#include "logger.h"
#include "engine_object.h"
#include "engine.h"

EngineObject::EngineObject(Engine* engine) :
	mEngine(engine),
	mSelectable(true)
	{
	mEngine->addObject(this);
}

EngineObject::~EngineObject(){
	Logger::debug("engine object delete");
	//mEngine->deleteObject(this);
}

void	EngineObject::setUuid(std::string name){
	mUuid.fromString(name);
	mEngine->deleteMappedObject(this);
	mEngine->addMappedObject(this);
}


