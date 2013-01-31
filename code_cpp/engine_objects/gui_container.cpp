#include "logger.h"

#include "engine.h"
#include "gui_container.h"
#include "gui_shape.h"

GuiContainer::GuiContainer(Engine* engine) :
	EngineObject(engine),
	mPosition(Vec3()),
	mOrientation(Quat()),
	mSize(Vec3(1,1,1))
	{
}

GuiContainer::~GuiContainer(){

}

GuiShape*		GuiContainer::getShapeByIndex(int index){
	//Logger::debug(format("get shape by index : %1%") % index);
	return mShapes[index];
}

void				GuiContainer::selectShow(){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->selectShow();
	}
}

void				GuiContainer::selectHide(){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->selectHide();
	}
}

bool				GuiContainer::hasShape(GuiShape* shape){
	bool hasShape = false;
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		if ( (*iter) == shape ) {
			hasShape = true;
			break;
		}
	}
	return hasShape;
}

GuiShape*		GuiContainer::getShapeByName(const char* name){
	GuiShape*	foundShape = 0;
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		//TODO right comparison 
		//if ( (*iter)->getName() ) {
			foundShape = (*iter);
			break;
		//}
	}
	return foundShape;
}

void	GuiContainer::addShape(GuiShape* shape){
	mShapes.push_back(shape);
	shape->setContainer(this);
}

void	GuiContainer::removeShape(GuiShape* shape){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		if ( (*iter) == shape ) {
			//TODO erase iter
			break;
		}
	}
}

int     GuiContainer::howManyShapes() {
	return mShapes.size();
}

void        GuiContainer::setPosition(const Vec3& vec3){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->setPosition(vec3);
	}
	mPosition = vec3;
}

void        GuiContainer::setOrientation(const Quat& quat){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->setOrientation(quat);
	}
	mOrientation = quat;
}

void        GuiContainer::setSize(const Vec3& vec3){
	std::vector<GuiShape*>::iterator	iter;
	for(iter=mShapes.begin();iter!=mShapes.end();++iter){
		(*iter)->setSize(vec3);
	}
	mSize = vec3;
}

void	GuiContainer::addDebugAxises(float debugSize, float debugWidth){
	GuiShape* shape;
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

