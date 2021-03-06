#ifndef _PHYSIC_SHAPE_H
	#define _PHYSIC_SHAPE_H

#include "PxPhysicsAPI.h"
using namespace physx;

class Engine;
class Actor;

#include "gui_shape.h"

#include <Ogre.h>
using namespace Ogre;

#include "ProceduralStableHeaders.h"
#include "Procedural.h"


class PhysicShape : public GuiShape {
	private:
		enum ShapeType {
			NOP,
			BOX,
			SPHERE,
			CAPSULE,
			PLANE
		};
	
	public:
		PhysicShape(Engine*,Actor*,PxShape*);
		virtual ~PhysicShape();

		virtual PhysicShape*	isPhysicShape(){return this;}
		virtual ObjectType		getType(){ return PHYSIC_SHAPE;}

	public:
		void 					createGuiBox(Vec3&);
		void 					createGuiSphere(Vec3&);
		void 					createGuiCapsule(Vec3&);
		void 					updateGuiCapsule(Vec3&);

		virtual void        	setLocalPosition(Vec3& vec3);
		virtual Vec3    		getLocalPosition();

		virtual void        	setLocalOrientation(Quat& quat);
		virtual Quat 			getLocalOrientation();

		virtual void        	setLocalSize(Vec3& vec3);
		virtual Vec3    		getLocalSize();

		bool					isBoxShape();
		bool					isSphereShape();
		bool					isCapsuleShape();
		bool					isPlaneShape();

		void					setBoxShape();
		void					setSphereShape();
		void					setCapsuleShape();
		void					setPlaneShape();

		Actor*					getActor(){return mActor;}

		void					enableCollisions();
		void					dissableCollisions();

	private:
        PxShape*            	mShape;
		Actor*					mActor;
		Mesh*					mMesh;
		ShapeType				mShapeType;	
};
#endif
