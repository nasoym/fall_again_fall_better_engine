#ifndef _ENGINE_MESH_H
#define _ENGINE_MESH_H

#include <Ogre.h>
using namespace Ogre;

#include <vector>

#include "engine_gui_shape.h"

class Engine;
class EngineBody;

struct BoneBody {
	Bone*		bone;
	EngineBody*	body;
	EngineJoint*joint;
	BoneBody(Bone* b) : bone(b),body(0),joint(0) {}
	BoneBody(Bone* b,EngineBody* eb) : bone(b),body(eb),joint(0) {}
};

class EngineMesh : public EngineGuiShape {

    public:

        EngineMesh(Engine*,const char*);
		virtual ~EngineMesh();

		void	enableBones();

		virtual void	guiUpdate();
		//virtual void	physicUpdate();

		void	createPhysicBodies(Bone* bone);
		//void	createPhsyisJoints();

		Vec3	getBonePosition(Bone* bone);
		Quat	getBoneOrientation(Bone* bone,bool rotated=true);
		float	getBoneSize(Bone* bone);
		EngineBody*	getBodyOfBone(Bone* bone);
		EngineJoint*	getJointOfBone(Bone* bone);
		Bone*	getBoneParent(Bone* bone);
		void	checkForJointCollision(Bone* bone);
		void	boneSetPosition(Bone* bone,Vec3 vec3);

		Bone*	getBoneOfBody(EngineBody* body);
		void	updateBone(Bone* bone);
		void	boneSetOrientation(Bone* bone,Quat quat);
		void	createPhysics(Bone* bone);

		void	createDebugObjects();
		void	setBodyForBone(Bone* bone,EngineBody* body);
		void	setJointForBone(Bone* bone,EngineJoint* joint);
		void		printEulerAngles(Quat quat);

		Vec3		translateGlobalAnchorToLocal(EngineBody* body,Vec3 & globalAnchor);
		void	calcLocalPosOfRootBone();

		bool	hasBoneAParent(Bone* bone);
		EngineJoint* 	createJointToParent(Bone* bone);

		Bone*	findRootBone();

		virtual EngineMesh*				isMesh(){return this;}
	private:
		Bone*			mRootBone;

		std::vector<BoneBody> mBoneBodies;

		Vec3 mLocalPos;
		Quat mLocalQuat;

		EngineGuiShape*	mRootShape;

		
};
#endif

