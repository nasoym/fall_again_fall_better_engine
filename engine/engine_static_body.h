#ifndef _ENGINE_STATIC_BODY_H
#define _ENGINE_STATIC_BODY_H

#include "engine_body.h"

class Engine;

class EngineStaticBody : public EngineBody {
    public:
        EngineStaticBody(Engine*);
		virtual EngineStaticBody*	 	isStaticBody(){return this;}
		virtual ObjectType		getType(){ return STATICBODY;}
};
#endif

