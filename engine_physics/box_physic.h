#ifndef _PHYSIC_BOX_H
	#define _PHYSIC_BOX_H

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>

#include "baseactor.h"

#include "PxPhysicsAPI.h"
using namespace physx;

#include "engine_physic.h"

using ::boost::python::object;
using ::boost::python::tuple;
using ::boost::python::make_tuple;
using ::boost::python::extract;

class PhysicsEngine;

class Actor : public BaseActor {
    private:
        PhysicsEngine*      mEngine;
        float               mSizeX;
        float               mSizeY;
        float               mSizeZ;

        PxRigidDynamic *    mBody;
        PxShape *           mShape;
    public:
        PxRigidActor*     getBody();
        void                wakeUp();

    public: // python
        Actor(PhysicsEngine&, object, object);
        ~Actor();
        tuple           getPosition();
        tuple           getOrientation();
        tuple           getSize();

        void            setPosition(object);
        void            setOrientation(object);
        void            setSize(object);

        float           getMass();
        void            setMass(float);

        void            addForce(object);

    public: //python debug
        float           getForceFactor();
        int             dGetSolverIterCount();
        int             dGetVelocityIterCount();
        void            dSetSolverIterCount(int);
        void            dSetVelocityIterCount(int);
};
#endif
