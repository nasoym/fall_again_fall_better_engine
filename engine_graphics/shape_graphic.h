#ifndef _GRAPHIC_SHAPE_H
#define _GRAPHIC_SHAPE_H

#include <Ogre.h>
using namespace Ogre;

#include "engine_graphic.h"

#include "math3d.h"

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>

class GraphicsShape {
    public:
        GraphicsShape(GraphicsEngine*);
        virtual ~GraphicsShape();

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

		void				setEntity(Entity* entity){mEntity = entity;}
		Entity*				getEntity(){return mEntity;}
		SceneNode*			getNode(){return mNode;}
		GraphicsEngine*		getGraphicsEngine(){return mGraphicsEngine;}

	private:
        GraphicsEngine* 	mGraphicsEngine;
        Entity*     		mEntity; 
        SceneNode*  		mNode;
};
#endif
