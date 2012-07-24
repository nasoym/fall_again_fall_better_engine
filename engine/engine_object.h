//-------------------------------------
#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include <string>
#include "uuid.h"

#include "engine.h"
class Engine;
//-------------------------------------
class EngineObject {
    public:
        EngineObject(Engine* engine);
        ~EngineObject();

		std::string 	getName(){return mName;}
		void 			setName(std::string& name){mName = name;}
		//void 			setName(char * chr_ptr){mName = name;}

		std::string		readUuid(){ return mUuid.toString(); }
		void			setUuid(){}
		Uuid			getUuid(){ return mUuid; }

		void			guiUpdate();
		void			physicUpdate();

		Engine*			getEngine(){ return mEngine; }

	private:
		Engine*		mEngine;
		std::string	mName;
		Uuid		mUuid;
};
//-------------------------------------
#endif
//-------------------------------------

