#ifndef _ENGINE_BODY_H
#define _ENGINE_BODY_H

#include "engine.h"
class Engine;

#include "engine_gui_shape.h"

#include "box_physic.h"

class EngineBody : public EngineGuiShape {
    public:
        EngineBody(Engine*);
		virtual void	physicUpdate();
		virtual void	guiUpdate();

		virtual void        setPosition(Vec3& vec3);
		virtual void        setOrientation(Quat& quat);
		virtual void        setSize(Vec3& vec3);

		PhysicBox*			getPhysicBody(){return mPhysicBox;}
		virtual EngineBody*				isBody(){return this;}
	private:

		PhysicBox*		mPhysicBox;
};
#endif


