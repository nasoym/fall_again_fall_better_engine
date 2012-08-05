#ifndef _ENGINE_MESH_H
#define _ENGINE_MESH_H

#include <Ogre.h>
using namespace Ogre;

#include <vector>

#include "engine_gui_shape.h"

class Engine;
class EngineBody;
class EngineGuiContainer;

struct BoneBody {
	Bone*		bone;
	EngineBody*	body;
	EngineJoint*joint;
	EngineGuiContainer* container;

	BoneBody(Bone* b) : bone(b),body(0),joint(0), container(0) {}
};

class EngineMesh : public EngineGuiShape {

    public:
        EngineMesh(Engine*,const char*);
		virtual ~EngineMesh();

		void			enableBones();
		void			createPhysicBodies(Bone* bone);
		void			checkForJointCollision(Bone* bone);
		void			updateBone(Bone* bone);
		void			createPhysics(Bone* bone);
		void			createDebugObjects();
		Vec3			translateGlobalAnchorToLocal(EngineBody* body,Vec3 & globalAnchor);
		void			calcLocalPosOfRootBone();
		EngineJoint* 	createJointToParent(Bone* bone);
		Quat			calcJointOrientation(Bone* bone);

		virtual void	guiUpdate();

		Bone*			findRootBone();
		bool			hasBoneAParent(Bone* bone);
		Bone*			getBoneParent(Bone* bone);

		Vec3			getBonePosition(Bone* bone);
		Quat			getBoneOrientation(Bone* bone,bool rotated=true);
		float			getBoneSize(Bone* bone);

		void			boneSetPosition(Bone* bone,Vec3 vec3);
		void			boneSetOrientation(Bone* bone,Quat quat);

		EngineBody*		getBodyOfBone(Bone* bone);
		EngineJoint*	getJointOfBone(Bone* bone);
		EngineGuiContainer*	getContainerOfBone(Bone* bone);

		Bone*			getBoneOfBody(EngineBody* body);

		void			setBodyForBone(Bone* bone,EngineBody* body);
		void			setJointForBone(Bone* bone,EngineJoint* joint);
		void			setContainerForBone(Bone* bone,EngineGuiContainer* container);

		virtual EngineMesh*				isMesh(){return this;}

	private:
		EngineGuiShape*			mRootShape;
		std::vector<BoneBody> 	mBoneBodies;
		Bone*					mRootBone;
		Vec3 mLocalPos;
		Quat mLocalQuat;


		
};
#endif

