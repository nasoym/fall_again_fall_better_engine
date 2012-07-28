

def createHumanBodyParts(engine,module,ragdoll,size=1):

    #ragdoll.parts["base"] = (physicstaticbody.PhysicStaticBody(app, (10*size,1*size,10*size), (0,0.5*size,0) )
    #ragdoll.parts["base"].setStatic()

	ragdoll.parts["base"] = engine.createPhysicBox()
	ragdoll.parts["base"].setSize(module.Vec3(10*size,1*size,10*size))
	ragdoll.parts["base"].setPosition(module.Vec3(0,-0.5*size,0))

	ragdoll.parts["hip"] = engine.createPhysicBox()
	ragdoll.parts["hip"].setSize(module.Vec3(1*size,1*size,5*size))
	ragdoll.parts["ruleg"] = engine.createPhysicBox()
	ragdoll.parts["ruleg"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["luleg"] = engine.createPhysicBox()
	ragdoll.parts["luleg"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["rlleg"] = engine.createPhysicBox()
	ragdoll.parts["rlleg"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["llleg"] = engine.createPhysicBox()
	ragdoll.parts["llleg"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["belly"] = engine.createPhysicBox()
	ragdoll.parts["belly"].setSize(module.Vec3(3*size,1*size,1*size))
	ragdoll.parts["breast"] = engine.createPhysicBox()
	ragdoll.parts["breast"].setSize(module.Vec3(3*size,1*size,1*size))
	ragdoll.parts["shoulder"] = engine.createPhysicBox()
	ragdoll.parts["shoulder"].setSize(module.Vec3(1*size,1*size,5*size))
	ragdoll.parts["ruarm"] = engine.createPhysicBox()
	ragdoll.parts["ruarm"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["luarm"] = engine.createPhysicBox()
	ragdoll.parts["luarm"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["rlarm"] = engine.createPhysicBox()
	ragdoll.parts["rlarm"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["llarm"] = engine.createPhysicBox()
	ragdoll.parts["llarm"].setSize(module.Vec3(4*size,1*size,1*size))
	ragdoll.parts["neck"] = engine.createPhysicBox()
	ragdoll.parts["neck"].setSize(module.Vec3(1*size,1*size,1*size))
	ragdoll.parts["head"] = engine.createPhysicBox()
	ragdoll.parts["head"].setSize(module.Vec3(3.5*size,2*size,2*size))

def createHumanJoints(engine,module,ragdoll):
    ragdoll.joints["j_rfoot"] = engine.createJoint(ragdoll.parts["base"], ragdoll.parts["rlleg"] )
    ragdoll.joints["j_rfoot"].setAnchor1Size( module.Vec3(0,1,0.35) )
    ragdoll.joints["j_rfoot"].setAnchor2Size( module.Vec3(-1,0,0) )
    ragdoll.joints["j_rfoot"].setAnchor1Orientation( module.Quat().fromAngle(0,1,90) )

    ragdoll.joints["j_lfoot"] = engine.createJoint(ragdoll.parts["base"], ragdoll.parts["llleg"] )
    ragdoll.joints["j_lfoot"].setAnchor1Size( module.Vec3(0,1,-0.35) )
    ragdoll.joints["j_lfoot"].setAnchor2Size( module.Vec3(-1,0,0) )
    ragdoll.joints["j_lfoot"].setAnchor1Orientation( module.Quat().fromAngle(0,1,90) )

    ragdoll.joints["j_rknee"] = engine.createJoint(ragdoll.parts["rlleg"], ragdoll.parts["ruleg"] )
    ragdoll.joints["j_rknee"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_rknee"].setAnchor2Size( module.Vec3(-1,0,0) )

    ragdoll.joints["j_lknee"] = engine.createJoint(ragdoll.parts["llleg"], ragdoll.parts["luleg"] )
    ragdoll.joints["j_lknee"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_lknee"].setAnchor2Size( module.Vec3(-1,0,0) )

    ragdoll.joints["j_rhip"] = engine.createJoint(ragdoll.parts["ruleg"], ragdoll.parts["hip"] )
    ragdoll.joints["j_rhip"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_rhip"].setAnchor2Size( module.Vec3(-1.1,0,0.7) )

    ragdoll.joints["j_lhip"] = engine.createJoint(ragdoll.parts["luleg"], ragdoll.parts["hip"] )
    ragdoll.joints["j_lhip"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_lhip"].setAnchor2Size( module.Vec3(-1.1,0,-0.7) )

    ragdoll.joints["j_belly"] = engine.createJoint(ragdoll.parts["belly"], ragdoll.parts["hip"] )
    ragdoll.joints["j_belly"].setAnchor1Size( module.Vec3(-1,0,0) )
    ragdoll.joints["j_belly"].setAnchor2Size( module.Vec3(1,0,0) )

    ragdoll.joints["j_breast"] = engine.createJoint(ragdoll.parts["breast"], ragdoll.parts["belly"] )
    ragdoll.joints["j_breast"].setAnchor1Size( module.Vec3(-1,0,0) )
    ragdoll.joints["j_breast"].setAnchor2Size( module.Vec3(1,0,0) )

    ragdoll.joints["j_shoulder"] = engine.createJoint(ragdoll.parts["shoulder"], ragdoll.parts["breast"] )
    ragdoll.joints["j_shoulder"].setAnchor1Size( module.Vec3(-1,0,0) )
    ragdoll.joints["j_shoulder"].setAnchor2Size( module.Vec3(1,0,0) )

    ragdoll.joints["j_neck"] = engine.createJoint(ragdoll.parts["neck"], ragdoll.parts["shoulder"] )
    ragdoll.joints["j_neck"].setAnchor1Size( module.Vec3(-1,0,0) )
    ragdoll.joints["j_neck"].setAnchor2Size( module.Vec3(1,0,0) )

    ragdoll.joints["j_head"] = engine.createJoint(ragdoll.parts["head"], ragdoll.parts["neck"] )
    ragdoll.joints["j_head"].setAnchor1Size( module.Vec3(-1,0,0) )
    ragdoll.joints["j_head"].setAnchor2Size( module.Vec3(1,0,0) )

    ragdoll.joints["j_rshoulder"] = engine.createJoint(ragdoll.parts["ruarm"], ragdoll.parts["shoulder"] )
    ragdoll.joints["j_rshoulder"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_rshoulder"].setAnchor2Size( module.Vec3(-1.1,0,0.7) )

    ragdoll.joints["j_lshoulder"] = engine.createJoint(ragdoll.parts["luarm"], ragdoll.parts["shoulder"] )
    ragdoll.joints["j_lshoulder"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_lshoulder"].setAnchor2Size( module.Vec3(-1.1,0,-0.7) )

    ragdoll.joints["j_relbow"] = engine.createJoint(ragdoll.parts["rlarm"], ragdoll.parts["ruarm"] )
    ragdoll.joints["j_relbow"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_relbow"].setAnchor2Size( module.Vec3(-1,0,0) )

    ragdoll.joints["j_lelbow"] = engine.createJoint(ragdoll.parts["llarm"], ragdoll.parts["luarm"] )
    ragdoll.joints["j_lelbow"].setAnchor1Size( module.Vec3(1,0,0) )
    ragdoll.joints["j_lelbow"].setAnchor2Size( module.Vec3(-1,0,0) )

def createLimits(engine,module,ragdoll,limit):
    ragdoll.joints["j_rfoot"].setLimits(limit,limit)
    ragdoll.joints["j_lfoot"].setLimits(limit,limit)

    ragdoll.joints["j_rhip"].setLimits(limit,limit)
    ragdoll.joints["j_lhip"].setLimits(limit,limit)

    ragdoll.joints["j_rknee"].setLimits(limit,limit)
    ragdoll.joints["j_lknee"].setLimits(limit,limit)

    ragdoll.joints["j_belly"].setLimits(limit,limit)
    ragdoll.joints["j_breast"].setLimits(limit,limit)
    ragdoll.joints["j_shoulder"].setLimits(limit,limit)
    ragdoll.joints["j_neck"].setLimits(limit,limit)
    ragdoll.joints["j_head"].setLimits(limit,limit)

    ragdoll.joints["j_rshoulder"].setLimits(limit,limit)
    ragdoll.joints["j_lshoulder"].setLimits(limit,limit)

    ragdoll.joints["j_relbow"].setLimits(limit,limit)
    ragdoll.joints["j_lelbow"].setLimits(limit,limit)

def createLimitsHuman(engine,module,ragdoll):
    ragdoll.joints["j_rfoot"].setLimits(90,90)
    ragdoll.joints["j_lfoot"].setLimits(90,90)

    ragdoll.joints["j_rknee"].setLimits(1,80)
    ragdoll.joints["j_rknee"].setAnchor1Orientation( module.Quat().fromAngle(0,1,80) )
    #ragdoll.joints["j_rknee"].setMotorTarget( module.Quat().fromAngle(0,1,-80) )
    ragdoll.joints["j_lknee"].setLimits(1,80)
    ragdoll.joints["j_lknee"].setAnchor1Orientation( module.Quat().fromAngle(0,1,80) )
    #ragdoll.joints["j_lknee"].setMotorTarget( module.Quat().fromAngle(0,1,-80) )

    ragdoll.joints["j_rhip"].setLimits(60,60)
    ragdoll.joints["j_lhip"].setLimits(60,60)

    ragdoll.joints["j_rshoulder"].setLimits(40,40)
    ragdoll.joints["j_lshoulder"].setLimits(40,40)

    ragdoll.joints["j_relbow"].setLimits(1,80)
    ragdoll.joints["j_relbow"].setAnchor1Orientation( module.Quat().fromAngle(0,1,-80) )
    #ragdoll.joints["j_relbow"].setMotorTarget( module.Quat().fromAngle(0,1,80) )
    ragdoll.joints["j_lelbow"].setLimits(1,80)
    ragdoll.joints["j_lelbow"].setAnchor1Orientation( module.Quat().fromAngle(0,1,-80) )
    #ragdoll.joints["j_lelbow"].setMotorTarget( module.Quat().fromAngle(0,1,80) )

"""

def driveJoints(app,ragdoll):
    ragdoll.joints["j_rfoot"].setMotorOn()
    ragdoll.joints["j_lfoot"].setMotorOn()

    ragdoll.joints["j_rknee"].setMotorOn()
    ragdoll.joints["j_lknee"].setMotorOn()

    ragdoll.joints["j_rhip"].setMotorOn()
    ragdoll.joints["j_lhip"].setMotorOn()

    ragdoll.joints["j_belly"].setMotorOn()

    ragdoll.joints["j_breast"].setMotorOn()
    ragdoll.joints["j_shoulder"].setMotorOn()
    ragdoll.joints["j_neck"].setMotorOn()
    ragdoll.joints["j_head"].setMotorOn()

def driveJointsOff(app,ragdoll):
    ragdoll.joints["j_rfoot"].setMotorOff()
    ragdoll.joints["j_lfoot"].setMotorOff()

    ragdoll.joints["j_rhip"].setMotorOff()
    ragdoll.joints["j_lhip"].setMotorOff()

    ragdoll.joints["j_rknee"].setMotorOff()
    ragdoll.joints["j_lknee"].setMotorOff()

    ragdoll.joints["j_belly"].setMotorOff()
    ragdoll.joints["j_breast"].setMotorOff()
    ragdoll.joints["j_shoulder"].setMotorOff()
    ragdoll.joints["j_neck"].setMotorOff()
    ragdoll.joints["j_head"].setMotorOff()


"""
