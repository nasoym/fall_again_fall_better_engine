#include "logger.h"
#include "engine_keys.h"
#include "engine.h"

#include "gui_shape.h"
#include "gui_container.h"

#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>

EngineObject*	Engine::getObjectOfShape(GuiShape* shape) {
	EngineObject*	engineObject;
	GuiContainer*	engineGuiContainer;
	std::vector<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		engineObject = (*mIterator);
		if (engineObject->isGuiContainer()){
			engineGuiContainer = engineObject->isGuiContainer();
			if (engineGuiContainer->hasShape(shape) ) {
				return engineGuiContainer;
			}
		}
	}
	return shape;
}

GuiShape*	Engine::getGuiShapeOfMovable(MovableObject* movable) {
	EngineObject*	engineObject;
	GuiShape*	engineGuiShape;
	std::vector<EngineObject*>::iterator  mIterator;
	for (mIterator = mObjects.begin(); 
		mIterator != mObjects.end(); ++mIterator) {
		engineObject = (*mIterator);
		if (engineObject->isGuiShape()){
			engineGuiShape = engineObject->isGuiShape();
			if (engineGuiShape->getEntity() == movable) {
				return engineGuiShape;
				break;
			}
		}
	}
	return 0;
}

boost::python::list	Engine::getMouseQuery(){
	const OIS::MouseState &ms = mMouse->getMouseState();
	Ray mouseRay = mCamera->getCameraToViewportRay(
		float(ms.X.abs) / float(ms.width), 
		float(ms.Y.abs) / float(ms.height)
		);
	mRaySceneQuery->setRay(mouseRay);
	mRaySceneQuery->setSortByDistance(true);
	RaySceneQueryResult &result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator rayIterator;

	boost::python::list		queryList;
	GuiShape*	shape;
 
	for(rayIterator = result.begin(); rayIterator != result.end(); rayIterator++ ) {
		RaySceneQueryResultEntry& curEntry = *rayIterator;
		if ( curEntry.movable !=NULL ) {
			shape = getGuiShapeOfMovable(curEntry.movable);
			if (shape){
				queryList.append( 
					boost::python::make_tuple( 
						curEntry.distance, 
						shape->readUuid()
						)
					);
			}
		}
	}
	mRaySceneQuery->clearResults();
	return queryList;
}

