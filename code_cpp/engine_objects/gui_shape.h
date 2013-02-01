
#ifndef _GUI_SHAPE_H
#define _GUI_SHAPE_H

#include <Ogre.h>
using namespace Ogre;

class Engine;
class GuiContainer;

#include "engine_object.h"

#include <string>

#include "math3d.h"

enum GuiScaling {
	FIX,
	NONE,
	ONE_TO_ONE,
	SCALING
};

class GuiShape : public EngineObject {
    public:
        GuiShape(Engine* engine);
        virtual ~GuiShape();

		virtual void        setPosition(Vec3& vec3);
		virtual Vec3    	getPosition();

		virtual void        setOrientation(Quat& quat);
		virtual Quat 		getOrientation();

		virtual void        setSize(Vec3& vec3);
		virtual Vec3    	getSize();

		virtual GuiShape*			isGuiShape(){return this;}
		virtual ObjectType		getType(){ return GUISHAPE;}

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

		void				setContainer(GuiContainer* container);
		GuiContainer* getContainer();

		void			setScalingFixed(){mScalingType=FIX;}
		void			setScalingNone(){mScalingType=NONE;}
		void			setScaling1To1(){mScalingType=ONE_TO_ONE;}
		void			setScalingScaling(){mScalingType=SCALING;}


		bool			isScalingFixed(){if (mScalingType==FIX) return true; return false;}
		bool			isScalingNone(){if (mScalingType==NONE) return true; return false;}
		bool			isScaling1To1(){if (mScalingType==ONE_TO_ONE) return true; return false;}
		bool			isScalingScaling(){if (mScalingType==SCALING) return true; return false;}

		bool				hasColour();
		float 				getAlpha();
		Vec3 				getColour();
		std::string			getMaterialName(){return mMaterialName;}

		void 				setCustomMaterial();

		void				selectShow();
		void				selectHide();

		bool				isFinalShape(){return mFinalShape;}
		void				setFinalShape(){mFinalShape = true;}
		void				setNonFinalShape(){mFinalShape = false;}

		void				hide(){mNode->setVisible(false);}
		void				show(){mNode->setVisible(true);}

		void				turnOffShadows(){
				if (mEntity) { 
					mEntity->setCastShadows(false);
					}
				}
		void				turnOnShadows(){
				if (mEntity) { 
					mEntity->setCastShadows(true);
					}
				}
		bool				getCastShadows(){
				if (mEntity) { 
					return mEntity->getCastShadows();
				} else {
					return false;
				}
			}


	private:
        Entity*     		mEntity; 
        SceneNode*  		mNode;
		MaterialPtr			mMaterial;

		Vec3				mLocalPosition;
		Quat				mLocalOrientation;

		GuiContainer*	mContainer;
		GuiScaling			mScalingType;

		std::string			mMaterialName;

		bool				mFinalShape;
	protected:
		Vec3				mLocalSize;

};

#endif
