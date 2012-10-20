#ifndef _ENGINE_PY_H
#define _ENGINE_PY_H

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/call_method.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/copy_const_reference.hpp>
using namespace boost::python;

#include "math3d.h"

#include "engine_keys.h"

#include "engine.h"

#include "engine_object.h"
#include "gui_shape.h"
#include "gui_container.h"

#include "gui_cube.h"

#include "joint.h"
#include "mesh.h"

#include "actor.h"
#include "dynamic_actor.h"
#include "static_actor.h"
#include "physic_shape.h"
#include "articulation.h"

BOOST_PYTHON_MODULE(EngineModule) {

	enum_<ObjectType>("ObjectType")
	.value("OBJECT",OBJECT)
	.value("GUISHAPE",GUISHAPE)
	.value("MESH",MESH)
	.value("SPACECAGE",SPACECAGE)
	.value("JOINT",JOINT)
	.value("BODY",BODY)
	.value("STATICBODY",STATICBODY)
	.value("BOX",BOX)
	.value("GUICONTAINER",GUICONTAINER)
	.value("ACTOR",ACTOR)
	.value("DYNAMIC_ACTOR",DYNAMIC_ACTOR)
	.value("PHYSIC_SHAPE",PHYSIC_SHAPE)
	.value("STATIC_ACTOR",STATIC_ACTOR)
	;


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
	.value("K_DELETE",K_DELETE)

	.value("K_COMMA",K_COMMA)
	.value("K_PERIOD",K_PERIOD)
	.value("K_SLASH",K_SLASH)

	.value("K_SEMICOLON",K_SEMICOLON)
	.value("K_APOSTROPHE",K_APOSTROPHE)
	.value("K_BACKSLASH",K_BACKSLASH)

	.value("K_LBRACKET",K_LBRACKET)
	.value("K_RBRACKET",K_RBRACKET)

	.value("K_MINUS",K_MINUS)
	.value("K_EQUALS",K_EQUALS)

	.value("K_SPACE",K_SPACE)
	.value("K_RETURN",K_RETURN)
	.value("K_ESCAPE",K_ESCAPE)

	.value("K_LEFT",K_LEFT) .value("K_RIGHT",K_RIGHT)
	.value("K_UP",K_UP) .value("K_DOWN",K_DOWN)
	.value("K_PGDOWN",K_PGDOWN) .value("K_PGUP",K_PGUP)

	.value("K_MLEFT",K_MLEFT) .value("K_MRIGHT",K_MRIGHT) .value("K_MMIDDLE",K_MMIDDLE)

	.value("K_FOCUS_CHANGE",K_FOCUS_CHANGE)

	.value("K_EXTREME_VELOCITY",K_EXTREME_VELOCITY)

	;


    class_<EngineObject>("EngineObject", init<Engine*>())
        .def("getName",&EngineObject::getName)
        .def("setName",&EngineObject::setName)

        .def("readUuid",&EngineObject::readUuid)
        .def("setUuid",&EngineObject::setUuid)

		.def("getType",&EngineObject::getType)

		.def("isGuiShape",&EngineObject::isGuiShape,return_value_policy<reference_existing_object>())
		.def("isGuiContainer",&EngineObject::isGuiContainer,return_value_policy<reference_existing_object>())
		.def("isJoint",&EngineObject::isJoint,return_value_policy<reference_existing_object>())
		.def("isMesh",&EngineObject::isMesh,return_value_policy<reference_existing_object>())
		.def("isActor",&EngineObject::isActor,return_value_policy<reference_existing_object>())
		.def("isDynamicActor",&EngineObject::isDynamicActor,return_value_policy<reference_existing_object>())
		.def("isPhysicShape",&EngineObject::isPhysicShape,return_value_policy<reference_existing_object>())
		.def("isArticulation",&EngineObject::isArticulation,return_value_policy<reference_existing_object>())
		.def("isStaticActor",&EngineObject::isStaticActor,return_value_policy<reference_existing_object>())
		.def("isBox",&EngineObject::isBox,return_value_policy<reference_existing_object>())

		.def("setSelectable",&EngineObject::setSelectable)
		.def("setUnselectable",&EngineObject::setUnselectable)
		.def("isSelectable",&EngineObject::isSelectable)
		;

    class_<GuiShape, bases<EngineObject> >("GuiShape", init<Engine*>())
		.def("setPosition",&GuiShape::setPosition)
		.def("getPosition",&GuiShape::getPosition)
		.def("setOrientation",&GuiShape::setOrientation)
		.def("getOrientation",&GuiShape::getOrientation)
		.def("setSize",&GuiShape::setSize)
		.def("getSize",&GuiShape::getSize)

		.def("setMaterialName",&GuiShape::setMaterialName)
		.def("setColour",&GuiShape::setColour)

		.def("setScalingNone",&GuiShape::setScalingNone)
		.def("setScaling1To1",&GuiShape::setScaling1To1)
		.def("setScalingScaling",&GuiShape::setScalingScaling)
		.def("setScalingFixed",&GuiShape::setScalingFixed)

		.def("isScalingFixed",&GuiShape::isScalingFixed)
		.def("isScalingNone",&GuiShape::isScalingNone)
		.def("isScaling1To1",&GuiShape::isScaling1To1)
		.def("isScalingScaling",&GuiShape::isScalingScaling)

		.def("setLocalPosition",&GuiShape::setLocalPosition)
		.def("getLocalPosition",&GuiShape::getLocalPosition)
		.def("setLocalOrientation",&GuiShape::setLocalOrientation)
		.def("getLocalOrientation",&GuiShape::getLocalOrientation)
		.def("setLocalSize",&GuiShape::setLocalSize)
		.def("getLocalSize",&GuiShape::getLocalSize)

		.def("getMaterialName",&GuiShape::getMaterialName)
		.def("hasColour",&GuiShape::hasColour)
		.def("getAlpha",&GuiShape::getAlpha)
		.def("getColour",&GuiShape::getColour)

		.def("selectShow",&GuiShape::selectShow)
		.def("selectHide",&GuiShape::selectHide)
		.def("setCustomMaterial",&GuiShape::setCustomMaterial)

		.def("isFinalShape",&GuiShape::isFinalShape)
		.def("setFinalShape",&GuiShape::setFinalShape)
		.def("setNonFinalShape",&GuiShape::setNonFinalShape)

		.def("hide",&GuiShape::hide)
		.def("show",&GuiShape::show)

		.def("turnOffShadows",&GuiShape::turnOffShadows)
		.def("turnOnShadows",&GuiShape::turnOnShadows)
		.def("getCastShadows",&GuiShape::getCastShadows)


		;

    class_<GuiContainer, bases<EngineObject> >("GuiContainer", init<Engine*>())
		.def("setPosition",&GuiContainer::setPosition)
		.def("getPosition",&GuiContainer::getPosition)
		.def("setOrientation",&GuiContainer::setOrientation)
		.def("getOrientation",&GuiContainer::getOrientation)
		.def("setSize",&GuiContainer::setSize)
		.def("getSize",&GuiContainer::getSize)

		.def("getShapeByIndex",&GuiContainer::getShapeByIndex,return_value_policy<reference_existing_object>() )
		.def("getShapeByName",&GuiContainer::getShapeByName,return_value_policy<reference_existing_object>() )
		.def("addShape",&GuiContainer::addShape)
		.def("removeShape",&GuiContainer::removeShape)
		.def("howManyShapes",&GuiContainer::howManyShapes)
		.def("addDebugAxises",&GuiContainer::addDebugAxises)

		.def("selectShow",&GuiContainer::selectShow)
		.def("selectHide",&GuiContainer::selectHide)
		;

	class_<Actor,bases<GuiContainer> >("Actor", init<Engine*>())
		//.def("x",&Actor::x,return_value_policy<reference_existing_object>())
		//.def("x",&Actor::x)
		.def("addBox",&Actor::addBox,return_value_policy<reference_existing_object>())
		.def("addSphere",&Actor::addSphere,return_value_policy<reference_existing_object>())
		.def("addCapsule",&Actor::addCapsule,return_value_policy<reference_existing_object>())
		.def("addPlane",&Actor::addPlane,return_value_policy<reference_existing_object>())

		.def("getPhysicShapeByIndex",&Actor::getPhysicShapeByIndex,return_value_policy<reference_existing_object>())
		.def("howManyPhysicShapes",&Actor::howManyPhysicShapes)

		.def("addForce",&Actor::addForce)

		.def("setMass",&Actor::setMass)
		.def("resetMass",&Actor::resetMass)
		.def("getMass",&Actor::getMass)

		.def("howManyJoints",&Actor::howManyJoints)
		.def("getJoint",&Actor::getJoint,return_value_policy<reference_existing_object>())

		.def("removeFromScene",&Actor::removeFromScene)
		.def("moveBackToScene",&Actor::moveBackToScene)

		.def("enableCollisions",&Actor::enableCollisions)
		.def("dissableCollisions",&Actor::dissableCollisions)

		;

	class_<DynamicActor,bases<Actor> >("DynamicActor", init<Engine*,Vec3&>())
		.def("setSolverIterations",&DynamicActor::setSolverIterations)
		.def("getLinearVelocity",&DynamicActor::getLinearVelocity)
		;

	class_<StaticActor,bases<Actor> >("StaticActor", init<Engine*,Vec3&>())
		;

	class_<Articulation,bases<Actor> >("Articulation", init<Engine*>())
		.def(init<Engine*,Articulation*>())

		.def("addArticulation",&Articulation::addArticulation,return_value_policy<reference_existing_object>())

		.def("addToScene",&Articulation::addToScene)
		.def("getParentAnchor",&Articulation::getParentAnchor)
		.def("getParentAnchorOrientation",&Articulation::getParentAnchorOrientation)
		.def("getChildAnchor",&Articulation::getChildAnchor)
		.def("getChildAnchorOrientation",&Articulation::getChildAnchorOrientation)
		.def("setParentAnchor",&Articulation::setParentAnchor)
		.def("setChildAnchor",&Articulation::setChildAnchor)
		.def("setParentAnchorOrientation",&Articulation::setParentAnchorOrientation)
		.def("setChildAnchorOrientation",&Articulation::setChildAnchorOrientation)
		.def("getMotorTarget",&Articulation::getMotorTarget)
		.def("setMotorTarget",&Articulation::setMotorTarget)
		.def("setSpring",&Articulation::setSpring)
		.def("getSpring",&Articulation::getSpring)
		.def("setDamping",&Articulation::setDamping)
		.def("getDamping",&Articulation::getDamping)
		.def("setSolverIterationCounts",&Articulation::setSolverIterationCounts)
		.def("setSwingLimits",&Articulation::setSwingLimits)
		.def("getSwingYLimit",&Articulation::getSwingYLimit)
		.def("getSwingZLimit",&Articulation::getSwingZLimit)
		.def("setSwingLimitEnabled",&Articulation::setSwingLimitEnabled)
		.def("setSwingLimitDisabled",&Articulation::setSwingLimitDisabled)
		.def("setTwistLimits",&Articulation::setTwistLimits)
		.def("getTwistLowerLimit",&Articulation::getTwistLowerLimit)
		.def("getTwistUpperLimit",&Articulation::getTwistUpperLimit)
		.def("setTwistLimitEnabled",&Articulation::setTwistLimitEnabled)
		.def("setTwistLimitDisabled",&Articulation::setTwistLimitDisabled)
		;

	class_<PhysicShape,bases<GuiShape> >("PhysicShape",no_init)
		.def("isBoxShape",&PhysicShape::isBoxShape)
		.def("isSphereShape",&PhysicShape::isSphereShape)
		.def("isCapsuleShape",&PhysicShape::isCapsuleShape)
		.def("isPlaneShape",&PhysicShape::isPlaneShape)


		.def("createGuiBox",&PhysicShape::createGuiBox)
		.def("createGuiSphere",&PhysicShape::createGuiSphere)
		.def("createGuiCapsule",&PhysicShape::createGuiCapsule)


		.def("getActor",&PhysicShape::getActor,return_value_policy<reference_existing_object>())

		.def("enableCollisions",&PhysicShape::enableCollisions)
		.def("dissableCollisions",&PhysicShape::dissableCollisions)
		;


	class_<GuiCube,bases<GuiShape> >("GuiCube", init<Engine*>())
		;

	class_<MeshObject,bases<GuiShape> >("MeshObject", init<Engine*,const char*>())
		.def("getFileName",&MeshObject::getFileName)
		.def("getNumberOfBones",&MeshObject::getNumberOfBones)
		.def("getBodyByIndex",&MeshObject::getBodyByIndex,return_value_policy<reference_existing_object>())
		.def("getJointByIndex",&MeshObject::getJointByIndex,return_value_policy<reference_existing_object>())
		.def("getBoneNameByIndex",&MeshObject::getBoneNameByIndex)
		.def("setBodyForBoneName",&MeshObject::setBodyForBoneName)
		.def("setJointForBoneName",&MeshObject::setJointForBoneName)

		.def("getBodyOfBoneName",&MeshObject::getBodyOfBoneName,return_value_policy<reference_existing_object>())
		.def("getJointOfBoneName",&MeshObject::getJointOfBoneName,return_value_policy<reference_existing_object>())
		.def("getBoneNamePosition",&MeshObject::getBoneNamePosition)
		.def("getBoneNameOrientation",&MeshObject::getBoneNameOrientation)
		.def("getBoneNameSize",&MeshObject::getBoneNameSize)
		.def("getBoneNameParentName",&MeshObject::getBoneNameParentName)
		.def("getBoneNameLocalPosition",&MeshObject::getBoneNameLocalPosition)
		.def("getBoneNameLocalOrientation",&MeshObject::getBoneNameLocalOrientation)
		.def("getMeshScale",&MeshObject::getMeshScale)

		.def("getBoneNameChildren",&MeshObject::getBoneNameChildren)
		.def("getBoneNameChildName",&MeshObject::getBoneNameChildName)
		.def("getRootBoneName",&MeshObject::getRootBoneName)
		.def("calcLocalPosOfRootBone",&MeshObject::calcLocalPosOfRootBone)

		.def("setRotationX",&MeshObject::setRotationX)
		.def("setRotationY",&MeshObject::setRotationY)
		.def("setRotationZ",&MeshObject::setRotationZ)

		.def("setLocalPos",&MeshObject::setLocalPos)
		.def("setLocalQuat",&MeshObject::setLocalQuat) 

		.def("getLocalPos",&MeshObject::getLocalPos)
		.def("getLocalQuat",&MeshObject::getLocalQuat) 

		;

	class_<Joint,bases<GuiContainer> >("Joint", init<Engine*,Actor*,Actor*>())
		.def("setAnchor1Size",&Joint::setAnchor1Size)
		.def("setAnchor2Size",&Joint::setAnchor2Size)
		.def("setAnchor1",&Joint::setAnchor1)
		.def("setAnchor2",&Joint::setAnchor2)
		.def("setAnchor1Orientation",&Joint::setAnchor1Orientation)
		.def("setAnchor2Orientation",&Joint::setAnchor2Orientation)
		.def("getAnchor1",&Joint::getAnchor1)
		.def("getAnchor2",&Joint::getAnchor2)
		.def("getAnchor1Size",&Joint::getAnchor1Size)
		.def("getAnchor2Size",&Joint::getAnchor2Size)
		.def("getAnchor1Orientation",&Joint::getAnchor1Orientation)
		.def("getAnchor2Orientation",&Joint::getAnchor2Orientation)
		.def("setLimits",&Joint::setLimits)
		.def("getYLimit",&Joint::getYLimit)
		.def("getZLimit",&Joint::getZLimit)
		.def("setMotorOn",&Joint::setMotorOn)
		.def("setMotorOff",&Joint::setMotorOff)
		.def("isMotorOn",&Joint::isMotorOn)
		.def("setMotorTarget",&Joint::setMotorTarget)
		.def("getMotorTarget",&Joint::getMotorTarget)
		.def("getBody1",&Joint::getBody1,return_value_policy<reference_existing_object>() )
		.def("getBody2",&Joint::getBody2,return_value_policy<reference_existing_object>() )

		.def("setMotorValues",&Joint::setMotorValues)


		.def("dsetMotorSpring",&Joint::dsetMotorSpring)
		.def("dsetMotorDamping",&Joint::dsetMotorDamping)
		.def("dsetMotorAccel",&Joint::dsetMotorAccel)
		.def("dsetContactDistance",&Joint::dsetContactDistance)

		;




    class_<Engine>("Engine")
        .def("createGuiBox",&Engine::createGuiBox,return_value_policy<reference_existing_object>() )
        .def("createJoint",&Engine::createJoint,return_value_policy<reference_existing_object>() )
		.def("createMesh",&Engine::createMesh,return_value_policy<reference_existing_object>() )
		.def("createArticulation",&Engine::createArticulation,return_value_policy<reference_existing_object>() )
		.def("createDynamicActor",&Engine::createDynamicActor,return_value_policy<reference_existing_object>() )
		.def("createStaticActor",&Engine::createStaticActor,return_value_policy<reference_existing_object>() )

        .def("step",&Engine::step)
        .def("quit",&Engine::quit)

        .def("setTimingFactor",&Engine::setTimingFactor)
        .def("getTimingFactor",&Engine::getTimingFactor)

		.def("setCameraPosition",&Engine::setCameraPosition)
		.def("setCameraOrientation",&Engine::setCameraOrientation)
		.def("getCameraPosition",&Engine::getCameraPosition)
		.def("getCameraOrientation",&Engine::getCameraOrientation)
		.def("simulatePhysics",&Engine::simulatePhysics)

		.def("physicPauseToggle",&Engine::physicPauseToggle)
		.def("physicsPause",&Engine::physicsPause)
		.def("physicsUnpause",&Engine::physicsUnpause)

        .def("howManyObjects",&Engine::howManyObjects)
        .def("getObject",&Engine::getObject,return_value_policy<reference_existing_object>() )
        .def("getFromUuid",&Engine::getFromUuid,return_value_policy<reference_existing_object>() )

        .def("getMouseQuery",&Engine::getMouseQuery)
        .def("getObjectOfShape",&Engine::getObjectOfShape,return_value_policy<reference_existing_object>() )
        .def("isKeyDown",&Engine::isKeyDown)

        .def("createUuid",&Engine::createUuid)
        .def("deleteObject",&Engine::deleteObject)

        .def("getTime",&Engine::getTime)
        .def("getTimeDifference",&Engine::getTimeDifference)

        .def("test",&Engine::test)

		.def("callPythonKeyPressed",&Engine::callPythonKeyPressed)
		.def("callPythonKeyDown",&Engine::callPythonKeyDown)
		.def("callPythonKeyReleased",&Engine::callPythonKeyReleased)

        .def("getMemoryUsage",&Engine::getMemoryUsage)
        .def("log",&Engine::log)

		.def("setAmbientLight",&Engine::setAmbientLight)
		.def("getAmbientLight",&Engine::getAmbientLight)
		.def("setCameraFOV",&Engine::setCameraFOV)
		.def("getCameraFOV",&Engine::getCameraFOV)
		.def("setGravity",&Engine::setGravity)
		.def("getGravity",&Engine::getGravity)
		.def("cameraRotateY",&Engine::cameraRotateY)
		.def("cameraRotateZ",&Engine::cameraRotateZ)
		.def("getMouseRelX",&Engine::getMouseRelX)
		.def("getMouseRelY",&Engine::getMouseRelY)

		.def("isFullscreen",&Engine::isFullscreen)

		.def("lightsOff",&Engine::lightsOff)
		.def("lightsOn",&Engine::lightsOn)
		.def("getExactTime",&Engine::getExactTime)

		.def("getDefaultShadedMaterialName",&Engine::getDefaultShadedMaterialName)

        ;

    class_<Vec3>("Vec3",init<>())
		.def(init<float,float,float>())
		//.def(init<object&>())
		.def("__str__",&Vec3::toString)

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
		.def("cross",&Vec3::cross)
		.def("dot",&Vec3::dot)

		.def_readwrite("x", &Vec3::x)
		.def_readwrite("y", &Vec3::y)
		.def_readwrite("z", &Vec3::z)

		.def("X",&Vec3::X)
		.def("Y",&Vec3::Y)
		.def("Z",&Vec3::Z)
		
		//.def("toTuple",&Vec3::toTuple)

		;

    class_<Quat>("Quat",init<>())
		.def(init<float,float,float,float>())
		//.def(init<object&>())
		.def("fromAngles",&Quat::fromAngles)
		.def("__str__",&Quat::toString)
		//.def("tupleFromAngle",&Quat::tupleFromAngle)

		.def(self * Vec3())
		.def(self * Quat())
		.def(self + Quat())
		.def(self - Quat())

		.def("inverse",&Quat::inverse)
		.def("normalise",&Quat::normalise)

		.def("toAngle",&Quat::toAngle)
		.def("toAxis",&Quat::toAxis)
		.def("fromAngleAxis",&Quat::fromAngleAxis)
		.def("toAngles",&Quat::toAngles)
		.def("fromAngles",&Quat::fromAngles)

		.def_readwrite("x", &Quat::x)
		.def_readwrite("y", &Quat::y)
		.def_readwrite("z", &Quat::z)
		.def_readwrite("w", &Quat::w)

		.def("W",&Quat::W)
		.def("X",&Quat::X)
		.def("Y",&Quat::Y)
		.def("Z",&Quat::Z)
		//.def("toTuple",&Quat::toTuple)

		;


}

#endif

