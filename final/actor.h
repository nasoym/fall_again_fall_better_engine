#ifndef _ACTOR_H
#define _ACTOR_H

#include "PxPhysicsAPI.h"
using namespace physx;

#include "engine_gui_container.h"
#include "engine_gui_shape.h"
#include <vector>

class Engine;
class PhysicShape;

#include "physic_basejoint.h"

class Actor : public EngineGuiContainer {

	protected:
		std::vector<BaseJoint*>    mJoints;

    public:
        Actor(Engine*);

		virtual void		physicUpdate();
		virtual void		guiUpdate();

		virtual void        setPosition(Vec3& vec3);
		virtual void        setOrientation(Quat& quat);

		virtual Vec3    	getPosition();
		virtual Quat 		getOrientation();


		virtual Actor*		isActor(){return this;}
		virtual ObjectType	getType(){return ACTOR;}

		PhysicShape*		addBox(Vec3&);
		PhysicShape*		addSphere(Vec3&);
		PhysicShape*		addCapsule(Vec3&);

		void				setGuiUpdatesOff(){mDoGuiUpdates=false;}
		void				setGuiUpdatesOn(){mDoGuiUpdates=true;}

		virtual PxRigidActor*   getActor(){return 0;}
		virtual void        wakeUp(){}

		virtual void        setSize(Vec3& vec3){}
		virtual Vec3    	getSize(){
		//return Vec3();
			return getShapeByIndex(0)->getLocalSize();
		}

		virtual void		addForce(Vec3){}	

		virtual void		setMass(float mass){}
		virtual void		resetMass(){}
		virtual float		getMass(){return 0;}

    virtual void    Actor::deleteAllJoints() {
        std::vector<BaseJoint*>::iterator  mJointsIterator;
        for (mJointsIterator = mJoints.begin(); 
            mJointsIterator != mJoints.end(); ++mJointsIterator) {
            delete (*mJointsIterator);
        }
        mJoints.clear();
    }

    virtual void    Actor::deleteJoint(BaseJoint* joint) {
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

    virtual int     Actor::howManyJoints() {
        return mJoints.size();
    }

    virtual void    Actor::addJoint(BaseJoint* joint){
        mJoints.push_back(joint);
    }

    virtual BaseJoint*  Actor::getJoint(int index) {
        return mJoints[index];
    }

	private:
		bool				mDoGuiUpdates;
};
#endif



