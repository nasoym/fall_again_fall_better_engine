#ifndef _GRAPHIC_SHAPE_H
#define _GRAPHIC_SHAPE_H

#include <Ogre.h>
using namespace Ogre;

class GraphicsEngine;

#include "math3d.h"

class GraphicsShape {
    public:
        GraphicsShape(GraphicsEngine*);
        virtual ~GraphicsShape();

		void        setPosition(Vec3& vec3);
		Vec3    	getPosition();

		void        setOrientation(Quat& quat);
		Quat 		getOrientation();

		void        setSize(Vec3& vec3);
		Vec3    	getSize();

		void				setEntity(Entity* entity){mEntity = entity;}
		Entity*				getEntity(){return mEntity;}
		SceneNode*			getNode(){return mNode;}
		GraphicsEngine*		getGraphicsEngine(){return mGraphicsEngine;}

	private:
        GraphicsEngine* 	mGraphicsEngine;
        Entity*     		mEntity; 
        SceneNode*  		mNode;
};
#endif
