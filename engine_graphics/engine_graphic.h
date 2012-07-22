//-------------------------------------
#ifndef _GRAPHIC_ENGINE_H
#define _GRAPHIC_ENGINE_H

#include <Ogre.h>
using namespace Ogre;

//-------------------------------------
class GraphicsEngine {
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        void    render();
    private:
        void    setup();
        void    close();
        void    setupResources();

    private:
        Root*           mRoot;
        LogManager*     mLogger;
        Camera*         mCamera;
        SceneManager*   mSceneMgr;
        RenderWindow*   mWindow;
        Viewport*       mViewport;
};
//-------------------------------------
#endif
//-------------------------------------

