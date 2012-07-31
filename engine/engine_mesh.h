#ifndef _ENGINE_MESH_H
#define _ENGINE_MESH_H

#include "engine_gui_shape.h"

class Engine;

class EngineMesh : public EngineGuiShape {

    public:
        EngineMesh(Engine*);
		virtual void		physicUpdate();
		virtual void		guiUpdate();

		virtual void        setPosition(Vec3& vec3);
		virtual void        setOrientation(Quat& quat);
		virtual void        setSize(Vec3& vec3);

		virtual Vec3    	getPosition();
		virtual Quat 		getOrientation();
		virtual Vec3    	getSize();

	private:
};
#endif



