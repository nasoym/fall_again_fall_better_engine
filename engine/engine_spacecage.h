#ifndef _ENGINE_SPACECAGE_H
#define _ENGINE_SPACECAGE_H

class Engine;

#include "engine_gui_container.h"

class PhysicPlane;

#include "math3d.h"

class EngineSpaceCage : public EngineGuiContainer {
    public:
        EngineSpaceCage(Engine*,Vec3&);

	private:
		PhysicPlane*	mBottomPlane;
		PhysicPlane*	mTopPlane;
		PhysicPlane*	mFrontPlane;
		PhysicPlane*	mBackPlane;
		PhysicPlane*	mLeftPlane;
		PhysicPlane*	mRightPlane;
};
#endif
