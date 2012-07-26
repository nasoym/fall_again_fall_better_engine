#ifndef _ENGINE_PY_H
#define _ENGINE_PY_H

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/call_method.hpp>

#include "engine.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(physics_nvidia_3_1_lib) {
    //class_<BaseActor>("BaseActor");
    //class_<ActorStatic, bases<BaseActor> >("ActorStatic", init<Engine&,object,object>())

    class_<Engine>("Engine")
        .def("simulate",&Engine::simulate)
        .def("getForceFactor",&Engine::getForceFactor)
        .def("setForceFactor",&Engine::setForceFactor)
        ;
}

#endif

