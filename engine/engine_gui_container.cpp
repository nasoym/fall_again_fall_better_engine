#include "logger.h"

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
	return mShapes[index];
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

