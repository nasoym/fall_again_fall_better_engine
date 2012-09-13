#include "logger.h"

#include "engine.h"
#include "engine_gui_container.h"
#include "engine_gui_shape.h"

EngineGuiContainer::EngineGuiContainer(Engine* engine) :
	EngineObject(engine),
	mPosition(Vec3()),
	mOrientation(Quat()),
	mSize(Vec3(1,1,1))
	{
}

EngineGuiContainer::~EngineGuiContainer(){

}

EngineGuiShape*		EngineGuiContainer::getShapeByIndex(int index){
	//Logger::debug(format("get shape by index : %1%") % index);
	return mShapes[index];
}

void				EngineGuiContainer::selectShow(){
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->selectShow();
	}
}

void				EngineGuiContainer::selectHide(){
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->selectHide();
	}
}

bool				EngineGuiContainer::hasShape(EngineGuiShape* shape){
	bool hasShape = false;
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		if ( (*iter) == shape ) {
			hasShape = true;
			break;
		}
	}
	return hasShape;
}

EngineGuiShape*		EngineGuiContainer::getShapeByName(const char* name){
	EngineGuiShape*	foundShape = 0;
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		//TODO right comparison 
		//if ( (*iter)->getName() ) {
			foundShape = (*iter);
			break;
		//}
	}
	return foundShape;
}

void	EngineGuiContainer::addShape(EngineGuiShape* shape){
	mShapes.push_back(shape);
	shape->setContainer(this);
}

void	EngineGuiContainer::removeShape(EngineGuiShape* shape){
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		if ( (*iter) == shape ) {
			//TODO erase iter
			break;
		}
	}
}

int     EngineGuiContainer::howManyShapes() {
	return mShapes.size();
}

void        EngineGuiContainer::setPosition(Vec3& vec3){
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->setPosition(vec3);
	}
	mPosition = vec3;
}

void        EngineGuiContainer::setOrientation(Quat& quat){
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->setOrientation(quat);
	}
	mOrientation = quat;
}

void        EngineGuiContainer::setSize(Vec3& vec3){
	std::vector<EngineGuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->setSize(vec3);
	}
	mSize = vec3;
}

void	EngineGuiContainer::addDebugAxises(float debugSize, float debugWidth){
	EngineGuiShape* shape;
	shape = getEngine()->createGuiBox()->isGuiShape();
	shape->setColour(1,0,0,0.5f);
	shape->setLocalSize(Vec3(debugSize,debugWidth,debugWidth));
	shape->setLocalPosition(Vec3(debugSize,0,0));
	addShape(shape);

	shape = getEngine()->createGuiBox()->isGuiShape();
	shape->setColour(0,1,0,0.5f);
	shape->setLocalSize(Vec3(debugWidth,debugSize,debugWidth));
	shape->setLocalPosition(Vec3(0,debugSize,0));
	addShape(shape);

	shape = getEngine()->createGuiBox()->isGuiShape();
	shape->setColour(0,0,1,0.5f);
	shape->setLocalSize(Vec3(debugWidth,debugWidth,debugSize));
	shape->setLocalPosition(Vec3(0,0,debugSize));
	addShape(shape);
}

