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
	BoneBody(Bone* b) : bone(b),body(0) {}
	BoneBody(Bone* b,EngineBody* eb) : bone(b),body(eb) {}
};

class EngineMesh : public EngineGuiShape {

    public:

        EngineMesh(Engine*,const char*);
		virtual ~EngineMesh();

		void	enableBones();

		virtual void	guiUpdate();
		virtual void	physicUpdate();

		void	createRootBone();
		void	createPhysicBodies();
		void	createPhsyisJoints();

		Vec3	getBonePosition(Bone* bone);
		Quat	getBoneOrientation(Bone* bone);
		float	getBoneSize(Bone* bone);
		EngineBody*	getBodyOfBone(Bone* bone);
		Bone*	getBoneParent(Bone* bone);
		void	checkForJointCollision();

		Bone*	getBoneOfBody(EngineBody* body);
		void	updateBone(Bone* bone);
		void	boneSetOrientation(Bone* bone,Quat quat);

		virtual EngineMesh*				isMesh(){return this;}
		EngineBody*				getRootBone();
	private:
		EngineBody*		mRootBody;
		Bone*			mRootBone;

		std::vector<BoneBody> mBoneBodies;


		
};
#endif

