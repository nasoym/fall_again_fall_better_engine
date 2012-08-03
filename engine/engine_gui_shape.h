
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
        virtual ~EngineGuiShape();

		virtual void        setPosition(Vec3& vec3);
		virtual Vec3    	getPosition();

		virtual void        setOrientation(Quat& quat);
		virtual Quat 		getOrientation();

		virtual void        setSize(Vec3& vec3);
		virtual Vec3    	getSize();

		virtual EngineGuiShape*			isGuiShape(){return this;}

		void	setMaterialName(const char* name);
		void	setColour(float red,float green,float blue,float alpha);
		void	setupCustomMaterial();

		void	createBoxEntity();

		void				setEntity(Entity* entity){mEntity = entity;}
		Entity*				getEntity(){return mEntity;}
		SceneNode*			getNode(){return mNode;}

	private:
        Entity*     		mEntity; 
        SceneNode*  		mNode;
		MaterialPtr	mMaterial;

};

#endif
