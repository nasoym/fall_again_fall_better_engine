#ifndef _MESH_H
#define _MESH_H

#include <Ogre.h>
using namespace Ogre;

#include <vector>
#include <string>

#include "gui_shape.h"

class Engine;
class GuiContainer;
class Actor;

struct BoneBody {
	Bone*		bone;
	Actor*	body;
	Joint*joint;
	GuiContainer* container;
	BoneBody(Bone* b) : bone(b),body(0),joint(0), container(0) {}
};

class MeshObject : public GuiShape {

    public:
        MeshObject(Engine*,const char*);
		//virtual ~MeshObject();
		virtual MeshObject*				isMesh(){return this;}
		virtual ObjectType		getType(){ return MESH;}

		void			setupAllBones();
		virtual void	guiUpdate();
		void			updateBone(Bone* bone);

		Bone*			findRootBone();
		Bone*			getBoneParent(Bone* bone);

		void			boneSetPosition(Bone* bone,Vec3 vec3);
		void			boneSetOrientation(Bone* bone,Quat quat,bool rotated=true);

		Actor*		getBodyOfBone(Bone* bone);
		Joint*	getJointOfBone(Bone* bone);
		Bone*			getBoneOfBody(Actor* body);
		void			setBodyForBone(Bone* bone,Actor* body);
		void			setJointForBone(Bone* bone,Joint* joint);
		Bone*			getBoneFromName(std::string boneName);
		Bone*			getRootBone(){return mRootBone;}

		//Debug
		void			setContainerForBone(Bone* bone,GuiContainer* container);
		GuiContainer*	getContainerOfBone(Bone* bone);
		void			createAllDebugObjects();
		void			createDebugForBone(Bone* bone);


		// Python Api
		std::string		getFileName(){return mMeshFileName;}
		int				getNumberOfBones();
		Actor*		getBodyByIndex(int);
		Joint*	getJointByIndex(int);
		std::string		getBoneNameByIndex(int);	

		Actor*		getBodyOfBoneName(std::string);
		Joint*	getJointOfBoneName(std::string);

		void			setBodyForBoneName(std::string,Actor*);
		void			setJointForBoneName(std::string,Joint*);

		Vec3			getBoneNamePosition(std::string);
		Quat			getBoneNameOrientation(std::string,bool rotated=true);
		float			getBoneNameSize(std::string);
		std::string		getBoneNameParentName(std::string);
		int				getBoneNameChildren(std::string);
		Vec3			getBoneNameLocalPosition(std::string);
		Quat			getBoneNameLocalOrientation(std::string);
		std::string		getBoneNameChildName(std::string boneName,int index);

		std::string		getRootBoneName(){return mRootBone->getName();}
		Vec3			getMeshScale();

		Vec3			getBonePosition(Bone* bone);
		Quat			getBoneOrientation(Bone* bone,bool rotated=true);
		float			getBoneSize(Bone* bone);

		void			calcLocalPosOfRootBone();

		void			setLocalPos(Vec3 vec){mLocalPos = vec;}
		void			setLocalQuat(Quat quat){mLocalQuat = quat;}

		Vec3			getLocalPos(){ return mLocalPos;}
		Quat			getLocalQuat(){ return mLocalQuat;}

		void			setRotationX(float val){mRotationX=val;}
		void			setRotationY(float val){mRotationY=val;}
		void			setRotationZ(float val){mRotationZ=val;}

	private:
		std::vector<BoneBody> 	mBoneBodies;
		Bone*					mRootBone;
		Vec3 					mLocalPos;
		Quat 					mLocalQuat;
		std::string				mMeshFileName;
		GuiContainer*			mRootShape;

		float					mRotationX;
		float					mRotationY;
		float					mRotationZ;

};
#endif
