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
		bool				hasShape(EngineGuiShape*);
		int     			howManyShapes();

		void				addDebugAxises(float debugSize=5.0, float debugWidth=0.5);
		//void				addDebugAxises(float,float);

		virtual EngineGuiContainer*		isGuiContainer(){return this;}
		virtual ObjectType		getType(){ return GUICONTAINER;}

		void				selectShow();
		void				selectHide();

	private:
		std::vector<EngineGuiShape*>	mShapes;

		Vec3		mPosition;
		Quat		mOrientation;
		Vec3		mSize;

};
#endif
