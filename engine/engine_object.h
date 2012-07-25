#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include <string>
#include "uuid.h"

#include "engine.h"
class Engine;

class EngineObject {
    public:
        EngineObject(Engine* engine);
        virtual ~EngineObject();

		std::string 	getName(){return mName;}
		void 			setName(std::string& name){mName = name;}
		//void 			setName(char * chr_ptr){mName = name;}

		std::string		readUuid(){ return mUuid.toString(); }
		void			setUuid(){}
		Uuid			getUuid(){ return mUuid; }

		Engine*			getEngine(){ return mEngine; }

		virtual void	guiUpdate(){}
		virtual void	physicUpdate(){}

	private:
		Engine*		mEngine;
		std::string	mName;
		Uuid		mUuid;
};
#endif
