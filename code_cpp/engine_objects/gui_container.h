#ifndef _GUI_CONTAINER_H
#define _GUI_CONTAINER_H

class Engine;

#include "engine_object.h"

#include "math3d.h"

#include <vector>

class GuiContainer : public EngineObject {
    public:
        GuiContainer(Engine*);
        ~GuiContainer();

		virtual void        setPosition(Vec3& vec3);
		virtual Vec3    	getPosition(){return mPosition;}

		virtual void        setOrientation(Quat& quat);
		virtual Quat 		getOrientation(){return mOrientation;}

		virtual void        setSize(Vec3& vec3);
		virtual Vec3    	getSize(){return mSize;}

		GuiShape*		getShapeByIndex(int);
		GuiShape*		getShapeByName(const char*);
		void				addShape(GuiShape*);
		void				removeShape(GuiShape*);
		bool				hasShape(GuiShape*);
		int     			howManyShapes();

		void				addDebugAxises(float debugSize=5.0, float debugWidth=0.5);
		//void				addDebugAxises(float,float);

		virtual GuiContainer*		isGuiContainer(){return this;}
		virtual ObjectType		getType(){ return GUICONTAINER;}

		void				selectShow();
		void				selectHide();

	protected:
		std::vector<GuiShape*>	mShapes;
	private:

		Vec3		mPosition;
		Quat		mOrientation;
		Vec3		mSize;

};
#endif
