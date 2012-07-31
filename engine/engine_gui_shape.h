
#ifndef _ENGINE_GUI_SHAPE_H
#define _ENGINE_GUI_SHAPE_H

class Engine;

#include "engine_object.h"
class EngineObject;

#include "shape_graphic.h"

class EngineGuiShape : public EngineObject {
    public:
        EngineGuiShape(Engine* engine);

		void		setShape(GraphicsShape* shape){mShape=shape;}

		void        tupleSetPosition(boost::python::object& tupleObject);
		boost::python::tuple tupleGetPosition();

		void        tupleSetOrientation(boost::python::object& tupleObject);
		boost::python::tuple tupleGetOrientation();

		void        tupleSetSize(boost::python::object& tupleObject);
		boost::python::tuple tupleGetSize();

		virtual void        setPosition(Vec3& vec3);
		virtual Vec3    	getPosition();

		virtual void        setOrientation(Quat& quat);
		virtual Quat 		getOrientation();

		virtual void        setSize(Vec3& vec3);
		virtual Vec3    	getSize();

		virtual EngineGuiShape*			isGuiShape(){return this;}

	private:
		GraphicsShape*	mShape;

};

#endif
