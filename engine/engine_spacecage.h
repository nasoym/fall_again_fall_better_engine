#ifndef _ENGINE_SPACECAGE_H
#define _ENGINE_SPACECAGE_H

#include "engine.h"

#include "engine_gui_shape.h"

#include "plane_physic.h"

class EngineSpaceCage : public EngineGuiShape {
    public:
        EngineSpaceCage(Engine*);

	private:
		PhysicPlane*	mBottomPlane;
		PhysicPlane*	mTopPlane;
		PhysicPlane*	mFrontPlane;
		PhysicPlane*	mBackPlane;
		PhysicPlane*	mLeftPlane;
		PhysicPlane*	mRightPlane;
};
#endif
