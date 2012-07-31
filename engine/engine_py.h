#ifndef _ENGINE_PY_H
#define _ENGINE_PY_H

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/call_method.hpp>
using namespace boost::python;

#include "math3d.h"

#include "engine_keys.h"

#include "engine.h"

#include "engine_object.h"
#include "engine_gui_shape.h"

#include "engine_spacecage.h"
#include "engine_body.h"
#include "engine_joint.h"
#include "engine_mesh.h"

BOOST_PYTHON_MODULE(EngineModule) {

	enum_<Keys>("Keys")
	.value("K_F1",K_F1) .value("K_F2",K_F2) .value("K_F3",K_F3) .value("K_F4",K_F4) .value("K_F5",K_F5) .value("K_F6",K_F6) .value("K_F7",K_F7) .value("K_F8",K_F8) .value("K_F9",K_F9) .value("K_F10",K_F10) .value("K_F11",K_F11) .value("K_F12",K_F12)
	.value("K_0",K_0) .value("K_1",K_1) .value("K_2",K_2) .value("K_3",K_3) .value("K_4",K_4) .value("K_5",K_5) .value("K_6",K_6) .value("K_7",K_7) .value("K_8",K_8) .value("K_9",K_9)
	.value("K_A",K_A) .value("K_B",K_B) .value("K_C",K_C) .value("K_D",K_D) .value("K_E",K_E) .value("K_F",K_F) .value("K_G",K_G) .value("K_H",K_H) .value("K_I",K_I) .value("K_J",K_J) .value("K_K",K_K) .value("K_L",K_L) .value("K_M",K_M) .value("K_N",K_N) .value("K_O",K_O) .value("K_P",K_P) .value("K_Q",K_Q) .value("K_R",K_R) .value("K_S",K_S) .value("K_T",K_T) .value("K_U",K_U) .value("K_V",K_V) .value("K_W",K_W) .value("K_X",K_X) .value("K_Y",K_Y) .value("K_Z",K_Z)

	.value("K_LSHIFT",K_LSHIFT) .value("K_RSHIFT",K_RSHIFT)
	.value("K_LCONTROL",K_LCONTROL) .value("K_RCONTROL",K_RCONTROL)
	.value("K_LMENU",K_LMENU).value("K_RMENU",K_RMENU)
	.value("K_CAPITAL",K_CAPITAL)

	.value("K_TAB",K_TAB)
	.value("K_BACK",K_BACK)
	.value("K_BACKSLASH",K_BACKSLASH)
	.value("K_DELETE",K_DELETE)

	.value("K_COMMA",K_COMMA)
	.value("K_PERIOD",K_PERIOD)
	.value("K_SLASH",K_SLASH)

	.value("K_MINUS",K_MINUS)
	.value("K_EQUALS",K_EQUALS)

	.value("K_SEMICOLON",K_SEMICOLON)
	.value("K_APOSTROPHE",K_APOSTROPHE)

	.value("K_LBRACKET",K_LBRACKET)
	.value("K_RBRACKET",K_RBRACKET)

	.value("K_SPACE",K_SPACE)
	.value("K_RETURN",K_RETURN)
	.value("K_ESCAPE",K_ESCAPE)

	.value("K_LEFT",K_LEFT) .value("K_RIGHT",K_RIGHT)
	.value("K_UP",K_UP) .value("K_DOWN",K_DOWN)
	.value("K_PGDOWN",K_PGDOWN) .value("K_PGUP",K_PGUP)

	.value("K_MLEFT",K_MLEFT) .value("K_MRIGHT",K_MRIGHT) .value("K_MMIDDLE",K_MMIDDLE)
	;


    class_<EngineObject>("EngineObject", init<Engine*>())
        .def("getName",&EngineObject::getName)
        .def("setName",&EngineObject::setName)
		;

    class_<EngineGuiShape, bases<EngineObject> >("EngineGuiShape", init<Engine*>())
		.def("setPosition",&EngineGuiShape::setPosition)
		.def("getPosition",&EngineGuiShape::getPosition)
		.def("setOrientation",&EngineGuiShape::setOrientation)
		.def("getOrientation",&EngineGuiShape::getOrientation)
		.def("setSize",&EngineGuiShape::setSize)
		.def("getSize",&EngineGuiShape::getSize)

		.def("isGuiShape",&EngineGuiShape::isGuiShape,return_value_policy<reference_existing_object>() )
		;

	class_<EngineSpaceCage,bases<EngineGuiShape> >("EngineSpaceCage", init<Engine*,Vec3&>())
		;

	class_<EngineBody,bases<EngineGuiShape> >("EngineBody", init<Engine*>())
		;

	class_<EngineMesh,bases<EngineGuiShape> >("EngineMesh", init<Engine*>())
		;

	class_<EngineJoint,bases<EngineGuiShape> >("EngineJoint", init<Engine*,EngineBody*,EngineBody*>())
		.def("setAnchor1Size",&EngineJoint::setAnchor1Size)
		.def("setAnchor2Size",&EngineJoint::setAnchor2Size)
		.def("setAnchor1",&EngineJoint::setAnchor1)
		.def("setAnchor2",&EngineJoint::setAnchor2)
		.def("setAnchor1Orientation",&EngineJoint::setAnchor1Orientation)
		.def("setAnchor2Orientation",&EngineJoint::setAnchor2Orientation)
		.def("getAnchor1",&EngineJoint::getAnchor1)
		.def("getAnchor2",&EngineJoint::getAnchor2)
		.def("getAnchor1Orientation",&EngineJoint::getAnchor1Orientation)
		.def("getAnchor2Orientation",&EngineJoint::getAnchor2Orientation)
		.def("setLimits",&EngineJoint::setLimits)
		.def("getYLimit",&EngineJoint::getYLimit)
		.def("getZLimit",&EngineJoint::getZLimit)
		.def("setMotorOn",&EngineJoint::setMotorOn)
		.def("setMotorOff",&EngineJoint::setMotorOff)
		.def("isMotorOn",&EngineJoint::isMotorOn)
		.def("setMotorTarget",&EngineJoint::setMotorTarget)
		.def("getMotorTarget",&EngineJoint::getMotorTarget)
		;

    class_<Engine>("Engine")
        .def("createGuiBox",&Engine::createGuiBox,return_value_policy<reference_existing_object>() )
        .def("createSpaceCage",&Engine::createSpaceCage,return_value_policy<reference_existing_object>() )
        .def("createPhysicBox",&Engine::createPhysicBox,return_value_policy<reference_existing_object>() )
        .def("createJoint",&Engine::createJoint,return_value_policy<reference_existing_object>() )
        .def("createPhysicStatic",&Engine::createPhysicStatic,return_value_policy<reference_existing_object>() )
		.def("createMesh",&Engine::createMesh,return_value_policy<reference_existing_object>() )

        .def("step",&Engine::step)
        .def("quit",&Engine::quit)

        .def("setTimingFactor",&Engine::setTimingFactor)
        .def("getTimingFactor",&Engine::getTimingFactor)

		.def("setCameraPosition",&Engine::setCameraPosition)
		.def("setCameraOrientation",&Engine::setCameraOrientation)
		.def("getCameraPosition",&Engine::getCameraPosition)
		.def("getCameraOrientation",&Engine::getCameraOrientation)
        ;

    class_<Vec3>("Vec3",init<>())
		.def(init<float,float,float>())
		.def(init<object&>())

		.def(self *= float())
		.def(self * float())

		.def(self /= float())
		.def(self / float())

		.def(self *= Vec3())
		.def(self * Vec3())

		.def(self += Vec3())
		.def(self + Vec3())

		.def(self -= Vec3())
		.def(self - Vec3())

		.def("length",&Vec3::length)
		.def("distance",&Vec3::distance)
		.def("normalise",&Vec3::normalise)

		.def("X",&Vec3::X)
		.def("Y",&Vec3::Y)
		.def("Z",&Vec3::Z)
		
		.def("toTuple",&Vec3::toTuple)

		;

    class_<Quat>("Quat",init<>())
		.def(init<float,float,float,float>())
		.def(init<object&>())
		.def("fromAngle",&Quat::fromAngle)
		.def("tupleFromAngle",&Quat::tupleFromAngle)

		.def(self * Vec3())
		.def(self * Quat())
		.def(self + Quat())
		.def(self - Quat())

		.def("inverse",&Quat::inverse)
		.def("normalise",&Quat::normalise)

		.def("W",&Quat::W)
		.def("X",&Quat::X)
		.def("Y",&Quat::Y)
		.def("Z",&Quat::Z)
		.def("toTuple",&Quat::toTuple)

		;


}

#endif

