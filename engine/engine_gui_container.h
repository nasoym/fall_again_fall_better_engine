#ifndef _ENGINE_GUI_CONTAINER_H
#define _ENGINE_GUI_CONTAINER_H

class Engine;

#include "engine_object.h"

#include "math3d.h"

#include <vector>

class EngineGuiContainer : public EngineObject {
    public:
        EngineGuiContainer(Engine*);
        ~EngineGuiContainer();

		virtual void        setPosition(Vec3& vec3);
		virtual Vec3    	getPosition(){return mPosition;}

		virtual void        setOrientation(Quat& quat);
		virtual Quat 		getOrientation(){return mOrientation;}

		virtual void        setSize(Vec3& vec3);
		virtual Vec3    	getSize(){return mSize;}

		EngineGuiShape*		getShapeByIndex(int);
		EngineGuiShape*		getShapeByName(const char*);
		void				addShape(EngineGuiShape*);
		void				removeShape(EngineGuiShape*);

		virtual EngineGuiContainer*		isGuiContainer(){return this;}

	private:
		std::vector<EngineGuiShape*>	mShapes;

		Vec3		mPosition;
		Quat		mOrientation;
		Vec3		mSize;

};
#endif
