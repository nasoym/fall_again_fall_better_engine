
#ifndef _ENGINE_GUI_SHAPE_H
#define _ENGINE_GUI_SHAPE_H

#include <Ogre.h>
using namespace Ogre;

class Engine;

#include "engine_object.h"

#include "math3d.h"

class EngineGuiShape : public EngineObject {
    public:
        EngineGuiShape(Engine* engine);
        ~EngineGuiShape();

		virtual void        setPosition(Vec3& vec3);
		virtual Vec3    	getPosition();

		virtual void        setOrientation(Quat& quat);
		virtual Quat 		getOrientation();

		virtual void        setSize(Vec3& vec3);
		virtual Vec3    	getSize();

		virtual EngineGuiShape*			isGuiShape(){return this;}

		void	createBoxEntity();
		void	createMesh(const char* meshName);
		void	enableBones();

		void				setEntity(Entity* entity){mEntity = entity;}
		Entity*				getEntity(){return mEntity;}
		SceneNode*			getNode(){return mNode;}

	private:
        Entity*     		mEntity; 
        SceneNode*  		mNode;

};

#endif
