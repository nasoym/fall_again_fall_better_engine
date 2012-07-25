
#ifndef _ENGINE_GUI_SHAPE_H
#define _ENGINE_GUI_SHAPE_H

#include "engine.h"

#include "engine_object.h"

#include "shape_graphic.h"

class EngineGuiShape : public EngineObject {
    public:
        EngineGuiShape(Engine* engine);
        virtual ~EngineGuiShape();

		void		setShape(GraphicsShape* shape){mShape=shape;}

	private:
		GraphicsShape*	mShape;

};

#endif
