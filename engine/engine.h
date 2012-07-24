//-------------------------------------
#ifndef _ENGINE_H
#define _ENGINE_H

#include "engine_physic.h"
#include "box_physic.h"

#include "engine_graphic.h"
#include "box_graphic.h"

#include "logger.h"

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
		bool			mLoopRendering;
};

class EngineKeyListener : public KeyboardListener {
    private:
        GraphicsEngine* mGraphicsEngine;
    public:
		EngineKeyListener(GraphicsEngine* graphicsEngine) :
			mGraphicsEngine(graphicsEngine) {
			
		}

		virtual void keyPressed(const OIS::KeyEvent& evt){
			if (evt.key == OIS::KC_ESCAPE) {
				Logger::debug("esc pressed");
			}
			if (evt.key == OIS::KC_1) {
				new GraphicsBox(mGraphicsEngine);
			}
		}
		virtual void keyReleased(const OIS::KeyEvent& evt){
			if (evt.key == OIS::KC_ESCAPE) {
				Logger::debug("esc released");
			}
		}

		virtual void	mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
			if(id == OIS::MB_Left)  {
				Logger::debug("left pressed");
			}
		}
		virtual void	mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
			if(id == OIS::MB_Left)  {
				Logger::debug("left released");
			}
		}
};
//-------------------------------------
#endif
//-------------------------------------


