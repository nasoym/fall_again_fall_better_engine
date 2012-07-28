#ifndef _ENGINE_STATIC_H
#define _ENGINE_STATIC_H

#include "engine.h"
class Engine;

#include "engine_gui_shape.h"

#include "static_physic.h"

class EngineStatic : public EngineGuiShape {
    public:
        EngineStatic(Engine*);
		virtual void	physicUpdate();
		virtual void	guiUpdate();

		virtual void        setPosition(Vec3& vec3);
		virtual void        setOrientation(Quat& quat);
		virtual void        setSize(Vec3& vec3);

		virtual Vec3    	getPosition();
		virtual Quat 		getOrientation();
		virtual Vec3    	getSize();
	private:

		PhysicStatic*		mPhysicBox;
};
#endif



