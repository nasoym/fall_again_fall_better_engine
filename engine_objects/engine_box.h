#ifndef _ENGINE_BOX_H
#define _ENGINE_BOX_H

#include "engine_gui_shape.h"

class Engine;

class EngineBox : public EngineGuiShape {
    public:
        EngineBox(Engine*);
		virtual EngineBox*				isBox(){return this;}
		virtual ObjectType		getType(){ return BOX;}
	private:
};
#endif