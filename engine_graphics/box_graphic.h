//-------------------------------------
#ifndef _GRAPHIC_BOX_H
#define _GRAPHIC_BOX_H

#include <Ogre.h>
using namespace Ogre;

#include "engine_graphic.h"

//-------------------------------------
class GraphicsBox {
    public:

        GraphicsBox(GraphicsEngine*);
        ~GraphicsBox();


        void        setPosition(float,float,float);
        void        setPosition(Vector3&);
        Vector3&    getPosition();

        void        setOrientation(float,float,float,float);
        void        setOrientation(Quaternion&);
        Quaternion& getOrientation();

        void        setSize(float,float,float);
        void        setSize(Vector3&);
        Vector3&    getSize();

    private:
        GraphicsEngine* mGraphicsEngine;
        Entity*     mEntity; 
        SceneNode*  mNode;
};
//-------------------------------------
#endif
//-------------------------------------


