#ifndef _ACTOR_H
#define _ACTOR_H

#include "PxPhysicsAPI.h"
using namespace physx;

#include "gui_container.h"
#include "gui_shape.h"
#include <vector>

class Engine;
class PhysicShape;
class Joint;

class Actor : public GuiContainer {

	protected:
		std::vector<Joint*>    mJoints;

    public:
        Actor(Engine*);

		virtual void		physicUpdate();
		virtual void		guiUpdate();

		virtual void        setPosition(const Vec3& vec3);
		virtual void        setOrientation(const Quat& quat);

		virtual Vec3    	getPosition();
		virtual Quat 		getOrientation();


		virtual Actor*		isActor(){return this;}
		virtual ObjectType	getType(){return ACTOR;}

		virtual PhysicShape*		addBox(Vec3&);
		virtual PhysicShape*		addSphere(Vec3&);
		virtual PhysicShape*		addCapsule(Vec3&);
		virtual PhysicShape*		addPlane();

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

		virtual void		setMass(float mass){mMass = mass;}
		virtual void		resetMass(){mMass = 1000;}
		virtual float		getMass(){return mMass;}

		float			mMass;



		virtual void    deleteAllJoints();
		virtual void    deleteJoint(Joint* joint);
		virtual int     howManyJoints();
		virtual void    addJoint(Joint* joint);
		virtual Joint*  getJoint(int index);


		virtual	void	removeFromScene();
		virtual	void	moveBackToScene();

		void					enableCollisions();
		void					dissableCollisions();

	private:
		bool				mDoGuiUpdates;
};
#endif



