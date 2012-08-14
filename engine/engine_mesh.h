#ifndef _ENGINE_MESH_H
#define _ENGINE_MESH_H

#include <Ogre.h>
using namespace Ogre;

#include <vector>
#include <string>

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
		//virtual ~EngineMesh();

		void			setupAllBones();
		void			updateBone(Bone* bone);
		void			createAllDebugObjects();
		void			calcLocalPosOfRootBone();
		void			createDebugForBone(Bone* bone);

		virtual void	guiUpdate();

		Bone*			findRootBone();
		Bone*			getBoneParent(Bone* bone);

		Vec3			getBonePosition(Bone* bone);
		Quat			getBoneOrientation(Bone* bone,bool rotated=true);
		float			getBoneSize(Bone* bone);

		void			boneSetPosition(Bone* bone,Vec3 vec3);
		void			boneSetOrientation(Bone* bone,Quat quat,bool rotated=true);

		EngineBody*		getBodyOfBone(Bone* bone);
		EngineJoint*	getJointOfBone(Bone* bone);
		EngineGuiContainer*	getContainerOfBone(Bone* bone);

		Bone*			getBoneOfBody(EngineBody* body);

		void			setBodyForBone(Bone* bone,EngineBody* body);
		void			setJointForBone(Bone* bone,EngineJoint* joint);
		void			setContainerForBone(Bone* bone,EngineGuiContainer* container);

		virtual EngineMesh*				isMesh(){return this;}
		virtual ObjectType		getType(){ return MESH;}

		std::string		getFileName(){return mMeshFileName;}
		int				getNumberOfBones();
		EngineBody*		getBodyByIndex(int);
		EngineJoint*	getJointByIndex(int);
		std::string		getBoneNameByIndex(int);	

		void			setBodyForBoneName(std::string,EngineBody*);
		void			setJointForBoneName(std::string,EngineJoint*);

		Bone*			getBoneFromName(std::string boneName);


		EngineBody*		getBodyOfBoneName(std::string);
		EngineJoint*	getJointOfBoneName(std::string);
		Vec3			getBoneNamePosition(std::string);
		Quat			getBoneNameOrientation(std::string,bool rotated=true);
		float			getBoneNameSize(std::string);
		std::string		getBoneNameParentName(std::string);

		int				getBoneNameChildren(std::string);

		Vec3			getBoneNameLocalPosition(std::string);
		Quat			getBoneNameLocalOrientation(std::string);
		Vec3			getMeshScale();

		std::string		getBoneNameChildName(std::string boneName,int index);

		Bone*			getRootBone(){return mRootBone;}
		std::string		getRootBoneName(){return mRootBone->getName();}


	private:
		std::vector<BoneBody> 	mBoneBodies;
		Bone*					mRootBone;
		Vec3 					mLocalPos;
		Quat 					mLocalQuat;
		std::string				mMeshFileName;


		
};
#endif

