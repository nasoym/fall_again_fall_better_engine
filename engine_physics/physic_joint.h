//-------------------------------------
#ifndef _PHYSIC_JOINT_H
	#define _PHYSIC_JOINT_H

#include "PxPhysicsAPI.h"
using namespace physx;

#include "physic_basejoint.h"

#include "physic_body.h"

#include "physic_engine.h"

#include "math3d.h"

	#ifndef PI
		#define 	PI (3.14159265f)
	#endif
	#ifndef DEG2RAD
		#define 	DEG2RAD (PI / 180.0f)
	#endif 
	#ifndef RAD2DEG
		#define 	RAD2DEG (180.0f / PI)
	#endif 

//-------------------------------------
class Actor;
class Engine;

class PhysicJoint : public BaseJoint {
    private:
        PhysicsEngine*         mEngine;

        Actor*          mActor1;
        Actor*          mActor2;

        PxD6Joint *     mJoint;

        bool            mMotorOn;

    private: //debug
        float           mDMotorSpring;
        float           mDMotorDamping;
        bool            mDMotorAccel;

        float           mDContactDistance;

    public:
        PhysicJoint(PhysicsEngine*,Actor*,Actor*);
        virtual ~PhysicJoint();

    protected:
        void        unregisterJoint();
        void        recreateJoint();
        void        createJoint();

    public:
        Actor*      getActor1();
        Actor*      getActor2();

        void        setAnchor1(Vec3&);
        void        setAnchor2(Vec3&);

        void        setAnchor1Orientation(Quat&);
        void        setAnchor2Orientation(Quat&);

        Vec3        getAnchor1();
        Vec3        getAnchor2();
        
        Quat        getAnchor1Orientation();
        Quat        getAnchor2Orientation();

        void        setLimits(float,float);
        float       getYLimit();
        float       getZLimit();

		void 		setMotorValues(float spring,float damping,bool accel);

        void        setMotorOn();
        void        setMotorOff();
        bool        isMotorOn();
        void        setMotorTarget(Quat&);
        Quat        getMotorTarget();

        void        setMotorStrength(float);
        float       getMotorStrength();

    public: //debug
        void        dsetMotorSpring(float);
        void        dsetMotorDamping(float);
        void        dsetMotorAccel(bool);
        void        dsetContactDistance(float);

        void        dLockSwing1();
        void        dUnLockSwing1();
        void        dLockSwing2();
        void        dUnLockSwing2();
        void        dResetLimits();

    private:
        void        updateBodies();
};
//-------------------------------------
#endif
//-------------------------------------
