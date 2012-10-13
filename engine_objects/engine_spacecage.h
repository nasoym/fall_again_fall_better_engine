#ifndef _ENGINE_SPACECAGE_H
#define _ENGINE_SPACECAGE_H

class Engine;

#include "engine_gui_container.h"

class PhysicPlane;

#include "math3d.h"

class EngineSpaceCage : public EngineGuiContainer {
    public:
        EngineSpaceCage(Engine*,Vec3&);
        virtual ~EngineSpaceCage();
		virtual EngineSpaceCage*	 	isSpaceCage(){return this;}
		virtual ObjectType		getType(){ return SPACECAGE;}

		virtual void        setPosition(Vec3& vec3){}
		virtual Vec3    	getPosition(){return Vec3();}

		virtual void        setOrientation(Quat& quat){}
		virtual Quat 		getOrientation(){return Quat();}

		virtual void        setSize(Vec3& vec3){}
		virtual Vec3    	getSize(){return mSpaceCageSize;}

	private:

		Vec3			mSpaceCageSize;
		PhysicPlane*	mBottomPlane;
		PhysicPlane*	mTopPlane;
		PhysicPlane*	mFrontPlane;
		PhysicPlane*	mBackPlane;
		PhysicPlane*	mLeftPlane;
		PhysicPlane*	mRightPlane;
};
#endif
