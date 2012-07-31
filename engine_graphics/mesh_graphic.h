#ifndef _GRAPHIC_MESH_H
#define _GRAPHIC_MESH_H

#include <vector>

class GraphicsEngine;
class GraphicsBone;

#include "shape_graphic.h"

class GraphicsMesh : public GraphicsShape {
    public:
        GraphicsMesh(GraphicsEngine*,const char*);


	private:
		void		enableBones();

	private:
		std::vector<GraphicsBone*> 	mMeshBones;	
		std::vector<GraphicsBone*>	mRootBones;
		// mRootBonePhysicBody;

};
#endif

