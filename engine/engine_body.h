#ifndef _ENGINE_BODY_H
#define _ENGINE_BODY_H

#include "engine.h"
class Engine;

#include "engine_gui_shape.h"

#include "box_physic.h"
#include "body_physic.h"

class EngineBody : public EngineGuiShape {

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

		void				setGuiUpdatesOff(){mDoGuiUpdates=false;}
		void				setGuiUpdatesOn(){mDoGuiUpdates=true;}
	private:

		PhysicBody*		mPhysicBody;
		bool			mDoGuiUpdates;
};
#endif


