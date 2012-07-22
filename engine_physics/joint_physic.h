//-------------------------------------
#ifndef _PHYSIC_JOINT_H
	#define _PHYSIC_JOINT_H

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>

using ::boost::python::object;
using ::boost::python::tuple;
using ::boost::python::make_tuple;
using ::boost::python::extract;

#include "PxPhysicsAPI.h"
using namespace physx;

#include "basejoint.h"
#include "baseactor.h"

#include "engine_physic.h"

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
class BaseActor;
class Engine;

class Joint : public BaseJoint {
    private:
        Engine*         mEngine;

        BaseActor*          mActor1;
        BaseActor*          mActor2;

        PxD6Joint *     mJoint;

        bool            mMotorOn;

    private: //debug
        float           mDMotorSpring;
        float           mDMotorDamping;
        bool            mDMotorAccel;

        float           mDContactDistance;

    public:
        Joint(Engine&,BaseActor&,BaseActor&);
        virtual ~Joint();

    protected:
        void        unregisterJoint();
        void        recreateJoint();
        void        createJoint();

    public:
        BaseActor*      getActor1();
        BaseActor*      getActor2();

        void        setAnchor1(object);
        void        setAnchor2(object);

        void        setAnchor1Orientation(object);
        void        setAnchor2Orientation(object);

        tuple       getAnchor1();
        tuple       getAnchor2();
        
        tuple       getAnchor1Orientation();
        tuple       getAnchor2Orientation();

        void        setLimits(object);
        tuple       getLimits();

        void        setMotorOn();
        void        setMotorOff();
        bool        isMotorOn();
        void        setMotorTarget(object);
        tuple       getMotorTarget();

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
