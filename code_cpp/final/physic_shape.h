#ifndef _PHYSIC_SHAPE_H
	#define _PHYSIC_SHAPE_H

#include "PxPhysicsAPI.h"
using namespace physx;

class Engine;
class Actor;

#include "gui_shape.h"

#include <Ogre.h>
using namespace Ogre;

#ifdef OGRE_PROCEDURAL
    #include "ProceduralStableHeaders.h"
    #include "Procedural.h"
#endif


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
		void 					createGuiBox(const Vec3&);
		void 					createGuiSphere(const Vec3&);
		void 					createGuiCapsule(const Vec3&);
		void 					updateGuiCapsule(const Vec3&);

		virtual void        	setLocalPosition(const Vec3& vec3);
		virtual Vec3    		getLocalPosition();

		virtual void        	setLocalOrientation(const Quat& quat);
		virtual Quat 			getLocalOrientation();

		virtual void        	setLocalSize(const Vec3& vec3);
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
