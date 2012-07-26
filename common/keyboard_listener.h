#ifndef _KEYBOARD_LISTENER_H
#define _KEYBOARD_LISTENER_H

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

class KeyboardListener {
    public:
        KeyboardListener(){}
        ~KeyboardListener(){}
		virtual void keyPressed(const OIS::KeyEvent& evt){}
		virtual void keyReleased(const OIS::KeyEvent& evt){}
		virtual void mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){}
		virtual void mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){}
};
#endif
