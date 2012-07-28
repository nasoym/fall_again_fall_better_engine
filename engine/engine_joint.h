#ifndef _ENGINE_JOINT_H
#define _ENGINE_JOINT_H

#include "engine.h"
class Engine;

#include "engine_gui_shape.h"
class EngineBody;


#include "joint_physic.h"

class EngineJoint : public EngineGuiShape {
    public:
        EngineJoint(Engine*,EngineBody*,EngineBody*);
		virtual void	physicUpdate();
		virtual void	guiUpdate();

        void        setAnchor1Size(Vec3& vec3);
        void        setAnchor2Size(Vec3& vec3);

        void        setAnchor1(Vec3& vec3){mJoint->setAnchor1(vec3);}
        void        setAnchor2(Vec3& vec3){mJoint->setAnchor2(vec3);}

        void        setAnchor1Orientation(Quat& quat){mJoint->setAnchor1Orientation(quat);}
        void        setAnchor2Orientation(Quat& quat){mJoint->setAnchor2Orientation(quat);}

        Vec3        getAnchor1(){return mJoint->getAnchor1();}
        Vec3        getAnchor2(){return mJoint->getAnchor2();}
        
        Quat        getAnchor1Orientation(){return mJoint->getAnchor1Orientation();}
        Quat        getAnchor2Orientation(){return mJoint->getAnchor2Orientation();}

        void        setLimits(float yLimit,float zLimit){mJoint->setLimits(yLimit,zLimit);}
        float       getYLimit(){return mJoint->getYLimit();}
        float       getZLimit(){return mJoint->getZLimit();}

	private:
		PhysicJoint*	mJoint;
		EngineBody*		mBody1;
		EngineBody*		mBody2;
};
#endif

