//-------------------------------------
#ifndef _ENGINE_H
#define _ENGINE_H

#include "engine_physic.h"
#include "box_physic.h"

#include "engine_graphic.h"
#include "box_graphic.h"

//-------------------------------------
class Engine {
    public:
        Engine();
        ~Engine();

        void    run();

    private:
        void    setup();
        void    close();

    private:

        PhysicsEngine*  mPhysicsEngine;
        GraphicsEngine* mGraphicsEngine;
};
//-------------------------------------
#endif
//-------------------------------------


