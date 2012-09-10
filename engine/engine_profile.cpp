#include "logger.h"
#include "engine.h"
#include "physic_engine.h"
#include "engine_object.h"

#include "actor.h"
#include "dynamic_actor.h"
#include "physic_shape.h"

void		Engine::printUsedResources(){
	ResourceGroupManager::ResourceManagerIterator resMgrs =
		ResourceGroupManager::getSingleton().getResourceManagerIterator();
	int resources = 0;
	while (resMgrs.hasMoreElements()) {
		ResourceManager::ResourceMapIterator resourceIterator =
			resMgrs.getNext()->getResourceIterator();
		while (resourceIterator.hasMoreElements()) {
			Ogre::ResourcePtr resource = resourceIterator.getNext();
			resources ++;
		}
	}
	Logger::debug( format("found resources: %1%") % resources);
}
