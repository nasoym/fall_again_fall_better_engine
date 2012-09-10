#ifndef _ACTOR_H
#define _ACTOR_H

#include "PxPhysicsAPI.h"
using namespace physx;

#include "engine_gui_container.h"
#include <vector>

class Engine;
class PhysicShape;

class Actor : public EngineGuiContainer {

    public:
        Actor(Engine*);

		virtual void		physicUpdate();
		virtual void		guiUpdate();

		virtual void        setPosition(Vec3& vec3);
		virtual void        setOrientation(Quat& quat);

		virtual Vec3    	getPosition();
		virtual Quat 		getOrientation();


		virtual Actor*				isActor(){return this;}
		virtual ObjectType		getType(){ return ACTOR;}

		PhysicShape*		addBox();
		PhysicShape*		addSphere();
		PhysicShape*		addCapsule();

		void				setGuiUpdatesOff(){mDoGuiUpdates=false;}
		void				setGuiUpdatesOn(){mDoGuiUpdates=true;}

		virtual PxRigidActor*   getActor(){return 0;}
		virtual void        wakeUp(){}

		virtual void        setSize(Vec3& vec3){}
		virtual Vec3    	getSize(){return Vec3();}
		virtual void		addForce(Vec3){}	
		virtual void		setMass(float mass){}
		virtual void		resetMass(){}
		virtual float		getMass(){return 0;}

	private:
		bool				mDoGuiUpdates;
};
#endif



