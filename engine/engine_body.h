#ifndef _ENGINE_BODY_H
#define _ENGINE_BODY_H

#include "engine_gui_container.h"

class Engine;
class PhysicBody;

class EngineBody : public EngineGuiContainer {

    public:
        EngineBody(Engine*);
		virtual void		physicUpdate();
		virtual void		guiUpdate();

		virtual void        setPosition(Vec3& vec3);
		virtual void        setOrientation(Quat& quat);
		virtual void        setSize(Vec3& vec3);

		virtual Vec3    	getPosition();
		virtual Quat 		getOrientation();
		virtual Vec3    	getSize();

		void				setPhysicBody(PhysicBody* physicBody){mPhysicBody=physicBody;}
		PhysicBody*			getPhysicBody(){return mPhysicBody;}

		virtual EngineBody*				isBody(){return this;}
		virtual ObjectType		getType(){ return BODY;}

		void				setGuiUpdatesOff(){mDoGuiUpdates=false;}
		void				setGuiUpdatesOn(){mDoGuiUpdates=true;}
	private:

		PhysicBody*		mPhysicBody;
		bool			mDoGuiUpdates;
};
#endif


