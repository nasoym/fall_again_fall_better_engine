#ifndef _ACTOR_H
#define _ACTOR_H

#include "PxPhysicsAPI.h"
using namespace physx;

#include "engine_gui_container.h"
#include "engine_gui_shape.h"
#include <vector>

class Engine;
class PhysicShape;
class Joint;

#include "physic_basejoint.h"

class Actor : public EngineGuiContainer {

	protected:
		std::vector<EngineJoint*>    mJoints;

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

		virtual PhysicShape*		addBox(Vec3&);
		virtual PhysicShape*		addSphere(Vec3&);
		virtual PhysicShape*		addCapsule(Vec3&);

		int					howManyPhysicShapes();
		PhysicShape*		getPhysicShapeByIndex(int);	

		void				setGuiUpdatesOff(){mDoGuiUpdates=false;}
		void				setGuiUpdatesOn(){mDoGuiUpdates=true;}

		virtual PxRigidActor*   getActor(){return 0;}
		virtual void        wakeUp(){}

		virtual void        setSize(Vec3& vec3){
			return getShapeByIndex(0)->setLocalSize(vec3);
		}
		virtual Vec3    	getSize(){
		//return Vec3();
			return getShapeByIndex(0)->getLocalSize();
		}

		virtual void		addForce(Vec3){}	

		virtual void		setMass(float mass){}
		virtual void		resetMass(){}
		virtual float		getMass(){return 0;}



		virtual void    deleteAllJoints();
		virtual void    deleteJoint(EngineJoint* joint);
		virtual int     howManyJoints();
		virtual void    addJoint(EngineJoint* joint);
		virtual EngineJoint*  getJoint(int index);


	private:
		bool				mDoGuiUpdates;
};
#endif



