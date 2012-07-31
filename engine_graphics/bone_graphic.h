#ifndef _GRAPHIC_BONE_H
#define _GRAPHIC_BONE_H

#include <Ogre.h>
using namespace Ogre;

class GraphicsEngine;
class GraphicsMesh;

#include "math3d.h"

class GraphicsBone {
    public:
        GraphicsBone(GraphicsEngine*,GraphicsMesh*,Bone*);
        virtual ~GraphicsBone();

		void        setPosition(Vec3& vec3);
		Vec3    	getPosition();

		void        setOrientation(Quat& quat);
		Quat 		getOrientation();

		void        setSize(Vec3& vec3);
		Vec3    	getSize();

	private:
        GraphicsEngine* 	mGraphicsEngine;
		Bone*				mBone;
		GraphicsMesh*		mMesh;
		
};
#endif

