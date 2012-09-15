RisingAnimTime = 200
RisingAnimTime = 150
exp=38
RisingSpring=(10 ** exp) * 1.2
RisingDamping=(10 ** exp) * 1.0

RisingStandSpring=(10 ** exp) * 1.2
RisingStandDamping=(10 ** exp) * 1.0


#RisingSpring  = 500000
#RisingDamping = 900000000
#FootRisingSpring  = 500000000
#FootRisingDamping = 900000000


exp=38
FootRisingSpring=(10 ** exp) * 1.2
FootRisingDamping=(10 ** exp) * 1.0


exp=28
RisingSpring=(10 ** exp) * 0.5
exp=28
RisingDamping=(10 ** exp) * 1.0

angularForce = False
#angularForce = True

"""
	{'groups':[
		"foot-joint"
		],
		'time':5,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		},
		"""
Timing = 1000
SimpleAnimation = [
	{'groups':[ "foot-joint" ],
		'time':Timing,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		},
	{'groups':[ "lleg-joint" ],
		'time':Timing,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		},
	{'groups':[ "uleg-joint" ],
		'time':Timing,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		},
	{'groups':[
		"foot-joint",
		"lleg-joint",
		"uleg-joint",
		"belly-joint",
		"breast-joint",
		"shoulder-joint",
		"neck-joint",
		"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
		'time':500,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,angularForce))],
		}
	]

RisingAnim = [
	{'groups':["foot-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},
	{'groups':["lleg-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},
	{'groups':["uleg-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},

	{'groups':["belly-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},

	{'groups':["breast-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		},

	{'groups':["shoulder-joint","neck-joint","head-joint"],
		'time':RisingAnimTime,
		'start':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingSpring,RisingDamping,True))],
		'end':[(lambda Engine,EngineModule,objects,groupPart:
			groupPart.setMotorValues(RisingStandSpring,RisingStandDamping,True))]
		}
	]


