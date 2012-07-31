
#ifndef _ENGINE_GUI_SHAPE_H
#define _ENGINE_GUI_SHAPE_H

class Engine;

#include "engine_object.h"

#include "shape_graphic.h"

class EngineGuiShape : public EngineObject {
    public:
        EngineGuiShape(Engine* engine);

		void		setShape(GraphicsShape* shape){mShape=shape;}

		virtual void        setPosition(Vec3& vec3);
		virtual Vec3    	getPosition();

		virtual void        setOrientation(Quat& quat);
		virtual Quat 		getOrientation();

		virtual void        setSize(Vec3& vec3);
		virtual Vec3    	getSize();

		virtual EngineGuiShape*			isGuiShape(){return this;}

	private:
		GraphicsShape*	mShape;

};

#endif
