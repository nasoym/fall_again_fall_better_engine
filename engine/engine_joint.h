#ifndef _ENGINE_JOINT_H
#define _ENGINE_JOINT_H

class Engine;
class EngineBody;

#include "math3d.h"

#include "engine_gui_container.h"

#include "physic_joint.h"

class EngineJoint : public EngineGuiContainer {
    public:
        EngineJoint(Engine*,EngineBody*,EngineBody*);

		virtual void		guiUpdate();

		virtual Vec3    	getPosition();
		virtual Quat 		getOrientation();

        void        setAnchor1Size(Vec3& vec3);
        void        setAnchor2Size(Vec3& vec3);

        void        setAnchor1(Vec3& vec3){mJoint->setAnchor1(vec3);}
        void        setAnchor2(Vec3& vec3){mJoint->setAnchor2(vec3);}

        void        setAnchor1Orientation(Quat& quat){mJoint->setAnchor1Orientation(quat);}
        void        setAnchor2Orientation(Quat& quat){mJoint->setAnchor2Orientation(quat);}

        Vec3        getAnchor1(){return mJoint->getAnchor1();}
        Vec3        getAnchor2(){return mJoint->getAnchor2();}

        Vec3        getAnchor1Size();
        Vec3        getAnchor2Size();
        
        Quat        getAnchor1Orientation(){return mJoint->getAnchor1Orientation();}
        Quat        getAnchor2Orientation(){return mJoint->getAnchor2Orientation();}

        void        setLimits(float yLimit,float zLimit){mJoint->setLimits(yLimit,zLimit);}
        float       getYLimit(){return mJoint->getYLimit();}
        float       getZLimit(){return mJoint->getZLimit();}

        void        setMotorOn(){mJoint->setMotorOn();}
        void        setMotorOff(){mJoint->setMotorOff();}
        bool        isMotorOn(){return mJoint->isMotorOn();}
        void        setMotorTarget(Quat& quat){mJoint->setMotorTarget(quat);}
        Quat        getMotorTarget(){return mJoint->getMotorTarget();}

		void 		setMotorValues(float spring,float damping,bool accel);

		virtual EngineJoint*			isJoint(){return this;}
		virtual ObjectType		getType(){ return JOINT;}

		EngineBody*		getBody1();
		EngineBody*		getBody2();

		//debug
        void        dsetMotorSpring(float);
        void        dsetMotorDamping(float);
        void        dsetMotorAccel(bool);
        void        dsetContactDistance(float);

	private:
		PhysicJoint*	mJoint;
		EngineBody*		mBody1;
		EngineBody*		mBody2;
};
#endif

