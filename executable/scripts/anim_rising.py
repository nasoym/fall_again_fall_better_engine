RisingAnimTime = 200
RisingAnimTime = 150
exp=38
RisingSpring=(10 ** exp) * 1.2
RisingDamping=(10 ** exp) * 1.0

RisingStandSpring=(10 ** exp) * 1.2
RisingStandDamping=(10 ** exp) * 1.0

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


