#ifndef _BASE_ACTOR_H
	#define _BASE_ACTOR_H

#include "basejoint.h"

#include "PxPhysicsAPI.h"
using namespace physx;

#include <vector>

class BaseJoint;

class BaseActor {
protected:
    std::vector<BaseJoint*>    mJoints;

public:
    BaseActor(){}
    virtual ~BaseActor(){}
    virtual PxRigidActor*   getBody(){return 0;}
    virtual void            wakeUp(){}

    virtual void    BaseActor::deleteAllJoints() {
        std::vector<BaseJoint*>::iterator  mJointsIterator;
        for (mJointsIterator = mJoints.begin(); 
            mJointsIterator != mJoints.end(); ++mJointsIterator) {
            delete (*mJointsIterator);
        }
        mJoints.clear();
    }

    virtual void    BaseActor::deleteJoint(BaseJoint* joint) {
        std::vector<BaseJoint*>::iterator  mJointsIterator;
        for (mJointsIterator = mJoints.begin(); 
            mJointsIterator != mJoints.end(); ++mJointsIterator) {
            if ( (*mJointsIterator) == joint ){
                delete (*mJointsIterator);
                mJoints.erase( mJointsIterator);
                break;
            }
        }
    }

    virtual int     BaseActor::howManyJoints() {
        return mJoints.size();
    }

    virtual void    BaseActor::addJoint(BaseJoint* joint){
        mJoints.push_back(joint);
    }

    virtual BaseJoint*  BaseActor::getJoint(int index) {
        return mJoints[index];
    }

};
#endif
