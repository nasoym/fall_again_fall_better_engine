//-------------------------------------
#ifndef _KEYBOARD_LISTENER_H
#define _KEYBOARD_LISTENER_H

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

//-------------------------------------
class KeyboardListener {
    public:
        KeyboardListener(){}
        ~KeyboardListener(){}
		virtual void keyPressed(const OIS::KeyEvent& evt){}
		virtual void keyReleased(const OIS::KeyEvent& evt){}
		virtual void mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){}
		virtual void mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){}
/*
			if (evt.key == OIS::KC_ESCAPE) {
KC_F1 .. KC_F12
KC_LSHIFT
KC_A .. KC_Z
KC_UP KC_DOWN
KC_RIGHT KC_LEFT
KC_PGUP KCPGDOWN
KC_ESCAPE
			if (id != OIS::MB_Left) 

MB_LEFT
MB_RIGHT

*/
};
//-------------------------------------
#endif
//-------------------------------------
