
#ifndef _ENGINE_GUI_SHAPE_H
#define _ENGINE_GUI_SHAPE_H

#include <Ogre.h>
using namespace Ogre;

class Engine;
class EngineGuiContainer;

#include "engine_object.h"

#include "math3d.h"

enum GuiScaling {
	FIX,
	NONE,
	ONE_TO_ONE,
	SCALING
};

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

		void				setEntity(Entity* entity){mEntity = entity;}
		Entity*				getEntity(){return mEntity;}
		SceneNode*			getNode(){return mNode;}


		virtual void        setLocalPosition(Vec3& vec3){mLocalPosition = vec3;}
		virtual Vec3    	getLocalPosition(){return mLocalPosition;}

		virtual void        setLocalOrientation(Quat& quat){mLocalOrientation = quat;}
		virtual Quat 		getLocalOrientation(){return mLocalOrientation;}

		virtual void        setLocalSize(Vec3& vec3); //{mLocalSize = vec3;}
		virtual Vec3    	getLocalSize(){return mLocalSize;}

		void				setContainer(EngineGuiContainer* container);
		EngineGuiContainer* getContainer();

		void			setScalingFixed(){mScalingType=FIX;}
		void			setScalingNone(){mScalingType=NONE;}
		void			setScaling1To1(){mScalingType=ONE_TO_ONE;}
		void			setScalingScaling(){mScalingType=SCALING;}

	private:
        Entity*     		mEntity; 
        SceneNode*  		mNode;
		MaterialPtr			mMaterial;

		Vec3				mLocalPosition;
		Quat				mLocalOrientation;
		Vec3				mLocalSize;

		EngineGuiContainer*	mContainer;
		GuiScaling			mScalingType;

};

#endif
