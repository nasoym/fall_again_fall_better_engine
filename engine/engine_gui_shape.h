
#ifndef _ENGINE_GUI_SHAPE_H
#define _ENGINE_GUI_SHAPE_H

#include "engine.h"
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

		void        setPosition(Vec3& vec3);
		Vec3    	getPosition();

		void        setOrientation(Quat& quat);
		Quat 		getOrientation();

		void        setSize(Vec3& vec3);
		Vec3    	getSize();

		virtual EngineGuiShape*			isGuiShape(){return this;}

	private:
		GraphicsShape*	mShape;

};

#endif
