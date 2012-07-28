#ifndef _ENGINE_BODY_H
#define _ENGINE_BODY_H

#include "engine.h"
class Engine;

#include "engine_gui_shape.h"

#include "box_physic.h"

class EngineBody : public EngineGuiShape {
    public:
        EngineBody(Engine*);
	private:
		PhysicBox*		mPhysicBox;
};
#endif


