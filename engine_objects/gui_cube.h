#ifndef _GUI_CUBE_H
#define _GUI_CUBE_H

#include "gui_shape.h"

class Engine;

class GuiCube : public GuiShape {
    public:
        GuiCube(Engine*);
		virtual GuiCube*				isBox(){return this;}
		virtual ObjectType		getType(){ return BOX;}
	private:
};
#endif
