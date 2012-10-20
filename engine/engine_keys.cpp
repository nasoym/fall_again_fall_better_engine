#include "logger.h"
#include "engine_keys.h"
#include "engine.h"

#include <map>
#include <vector>
#include "boost/assign.hpp"

#include "gui_shape.h"

//OIS::MouseButtonID
//std::map<int,Keys> keyList = 
std::map<OIS::KeyCode,Keys> keyList = 
boost::assign::map_list_of
	(OIS::KC_F1,K_F1) (OIS::KC_F2,K_F2) (OIS::KC_F3,K_F3) (OIS::KC_F4,K_F4) (OIS::KC_F5,K_F5) (OIS::KC_F6,K_F6) (OIS::KC_F7,K_F7) (OIS::KC_F8,K_F8) (OIS::KC_F9,K_F9) (OIS::KC_F10,K_F10) (OIS::KC_F11,K_F11) (OIS::KC_F12,K_F12)
	(OIS::KC_0,K_0) (OIS::KC_1,K_1) (OIS::KC_2,K_2) (OIS::KC_3,K_3) (OIS::KC_4,K_4) (OIS::KC_5,K_5) (OIS::KC_6,K_6) (OIS::KC_7,K_7) (OIS::KC_8,K_8) (OIS::KC_9,K_9)
	(OIS::KC_A,K_A) (OIS::KC_B,K_B) (OIS::KC_C,K_C) (OIS::KC_D,K_D) (OIS::KC_E,K_E) (OIS::KC_F,K_F) (OIS::KC_G,K_G) (OIS::KC_H,K_H) (OIS::KC_I,K_I) (OIS::KC_J,K_J) (OIS::KC_K,K_K) (OIS::KC_L,K_L) (OIS::KC_M,K_M) (OIS::KC_N,K_N) (OIS::KC_O,K_O) (OIS::KC_P,K_P) (OIS::KC_Q,K_Q) (OIS::KC_R,K_R) (OIS::KC_S,K_S) (OIS::KC_T,K_T) (OIS::KC_U,K_U) (OIS::KC_V,K_V) (OIS::KC_W,K_W) (OIS::KC_X,K_X) (OIS::KC_Y,K_Y) (OIS::KC_Z,K_Z)

	(OIS::KC_LSHIFT,K_LSHIFT) (OIS::KC_RSHIFT,K_RSHIFT)
	(OIS::KC_LCONTROL,K_LCONTROL) (OIS::KC_RCONTROL,K_RCONTROL)
	(OIS::KC_LMENU,K_LMENU)(OIS::KC_RMENU,K_RMENU)
	(OIS::KC_CAPITAL,K_CAPITAL)

	(OIS::KC_TAB,K_TAB)
	(OIS::KC_BACK,K_BACK)
	(OIS::KC_BACKSLASH,K_BACKSLASH)
	(OIS::KC_DELETE,K_DELETE)

	(OIS::KC_COMMA,K_COMMA)
	(OIS::KC_PERIOD,K_PERIOD)
	(OIS::KC_SLASH,K_SLASH)

	(OIS::KC_MINUS,K_MINUS)
	(OIS::KC_EQUALS,K_EQUALS)

	(OIS::KC_SEMICOLON,K_SEMICOLON)
	(OIS::KC_APOSTROPHE,K_APOSTROPHE)

	(OIS::KC_LBRACKET,K_LBRACKET)
	(OIS::KC_RBRACKET,K_RBRACKET)

	(OIS::KC_SPACE,K_SPACE)
	(OIS::KC_RETURN,K_RETURN)
	(OIS::KC_ESCAPE,K_ESCAPE)

	(OIS::KC_LEFT,K_LEFT) (OIS::KC_RIGHT,K_RIGHT)
	(OIS::KC_UP,K_UP) (OIS::KC_DOWN,K_DOWN)
	(OIS::KC_PGDOWN,K_PGDOWN) (OIS::KC_PGUP,K_PGUP)

	//(OIS::MB_Left,K_MLEFT) (OIS::MB_Right,K_MRIGHT) (OIS::MB_Middle,K_MMIDDLE) 
;

Keys	Engine::keyEventToKeys(const OIS::KeyEvent & evt) {
	std::map<OIS::KeyCode,Keys>::iterator keyListIterator;
	keyListIterator = keyList.find(evt.key);
	if (keyListIterator != keyList.end()) {
		return keyListIterator->second;
	}
	return K_NOP;
}

OIS::KeyCode	Engine::keysToKeyCode(Keys key){
	std::map<OIS::KeyCode,Keys>::iterator keyListIterator;
	for(keyListIterator=keyList.begin();keyListIterator!=keyList.end();++keyListIterator){
		if ( (*keyListIterator).second == key) {
			Logger::debug(format("found key:%1%") % key );
			return (*keyListIterator).first;
		}
	}
	Logger::debug(format("could not find key:%1%") % key );
	return OIS::KC_0;
}

void Engine::updateKeysDown() {
	std::vector<Keys>::iterator  pressedKeysIterator;
	for (pressedKeysIterator = mPressedKeys.begin(); 
		pressedKeysIterator != mPressedKeys.end(); ++pressedKeysIterator) {
		callPythonKeyDown((*pressedKeysIterator));
	}
}

bool Engine::isKeyDown(Keys key){
	//return mKeyboard->isKeyDown(keysToKeyCode(key));
	std::vector<Keys>::iterator  pressedKeysIterator;
	for (pressedKeysIterator = mPressedKeys.begin(); 
		pressedKeysIterator != mPressedKeys.end(); ++pressedKeysIterator) {
		if ( (*pressedKeysIterator) == key) {
			return true;
		}
	}
	return false;
}

void	Engine::storePressedKey(Keys key){
	mPressedKeys.push_back(key);
	//Logger::debug(format("storePressedKey:%1%") % key );
}

void	Engine::removePressedKey(Keys key){
	std::vector<Keys>::iterator  pressedKeysIterator;
	for (pressedKeysIterator = mPressedKeys.begin(); 
		pressedKeysIterator != mPressedKeys.end(); ++pressedKeysIterator) {
		if ( (*pressedKeysIterator) == key) {
			mPressedKeys.erase(pressedKeysIterator);
			break;
		}
	}
}

bool Engine::keyPressed(const OIS::KeyEvent& evt){
	/*
	if (evt.key == OIS::KC_ESCAPE) {
		Logger::debug("esc pressed");
		quit();
	}
	*/
	Keys key = keyEventToKeys(evt);
	if (key != K_NOP) {
		storePressedKey(key);
		callPythonKeyPressed(key);
	}
	return true;

}

bool Engine::keyReleased(const OIS::KeyEvent& evt){
	Keys key = keyEventToKeys(evt);
	if (key != K_NOP) {
		removePressedKey(key);
		callPythonKeyReleased(key);
	}
	return true;
}

bool Engine::mouseMoved(const OIS::MouseEvent& evt) {
	const OIS::MouseState &ms = mMouse->getMouseState();
	//if( ms.buttonDown( OIS::MB_Left ) ) {
	/*
	if (isKeyDown(K_MLEFT)){
		mCamera->yaw(Degree(-ms.X.rel * 0.13));
		mCamera->pitch(Degree(-ms.Y.rel * 0.13));
	}
	*/
    return true;
}

bool	Engine::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
    //Logger::debug("mousePressed");
	if (id == OIS::MB_Left)  {
		storePressedKey(K_MLEFT);
		pyFunctionKeyPressed(K_MLEFT);
	} else if (id == OIS::MB_Right) {
		storePressedKey(K_MRIGHT);
		pyFunctionKeyPressed(K_MRIGHT);
	} else if (id == OIS::MB_Middle) {
		storePressedKey(K_MMIDDLE);
		pyFunctionKeyPressed(K_MMIDDLE);
	}
	return true;
}

bool	Engine::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
	if (id == OIS::MB_Left)  {
		removePressedKey(K_MLEFT);
		pyFunctionKeyReleased(K_MLEFT);
	} else if (id == OIS::MB_Right) {
		removePressedKey(K_MRIGHT);
		pyFunctionKeyReleased(K_MRIGHT);
	} else if (id == OIS::MB_Middle) {
		removePressedKey(K_MMIDDLE);
		pyFunctionKeyReleased(K_MMIDDLE);
	}
	return true;
}


	
