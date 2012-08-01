#ifndef _BASE_ACTOR_H
	#define _BASE_ACTOR_H

#include "PxPhysicsAPI.h"
using namespace physx;

#include <vector>

#include "basejoint.h"

class PhysicBody {
protected:
    std::vector<BaseJoint*>    mJoints;

public:
    PhysicBody(){}
    virtual ~PhysicBody(){}
    virtual PxRigidActor*   getBody(){return 0;}
    virtual void            wakeUp(){}

		Vec3				getPosition();
		Quat				getOrientation();
		Vec3				getSize();

		void				setPosition(Vec3);
		void				setOrientation(Quat);
		void				setSize(Vec3);

    virtual void    PhysicBody::deleteAllJoints() {
        std::vector<BaseJoint*>::iterator  mJointsIterator;
        for (mJointsIterator = mJoints.begin(); 
            mJointsIterator != mJoints.end(); ++mJointsIterator) {
            delete (*mJointsIterator);
        }
        mJoints.clear();
    }

    virtual void    PhysicBody::deleteJoint(BaseJoint* joint) {
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

    virtual int     PhysicBody::howManyJoints() {
        return mJoints.size();
    }

    virtual void    PhysicBody::addJoint(BaseJoint* joint){
        mJoints.push_back(joint);
    }

    virtual BaseJoint*  PhysicBody::getJoint(int index) {
        return mJoints[index];
    }

};
#endif
