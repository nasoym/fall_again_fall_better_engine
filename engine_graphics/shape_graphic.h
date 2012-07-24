//-------------------------------------
#ifndef _GRAPHIC_SHAPE_H
#define _GRAPHIC_SHAPE_H

#include <Ogre.h>
using namespace Ogre;

#include "engine_graphic.h"

//-------------------------------------
class GraphicsShape {
    public:
        GraphicsShape(GraphicsEngine*);
        virtual ~GraphicsShape();

        virtual void        setPosition(float,float,float){}
        virtual void        setPosition(Vector3&){}
        //virtual Vector3&    getPosition(){return Vector3();}
        virtual Vector3    getPosition(){return Vector3();}

        virtual void        setOrientation(float,float,float,float){}
        virtual void        setOrientation(Quaternion&){}
        virtual Quaternion getOrientation(){return Quaternion();}

        virtual void        setSize(float,float,float){}
        virtual void        setSize(Vector3&){}
        virtual Vector3    getSize(){return Vector3();}


		void				setEntity(Entity* entity){mEntity = entity;}
		Entity*				getEntity(){return mEntity;}
		SceneNode*			getNode(){return mNode;}
		GraphicsEngine*		getGraphicsEngine(){return mGraphicsEngine;}

    //protected:
	private:
        GraphicsEngine* 	mGraphicsEngine;
        Entity*     		mEntity; 
        SceneNode*  		mNode;
};
//-------------------------------------
#endif
//-------------------------------------



