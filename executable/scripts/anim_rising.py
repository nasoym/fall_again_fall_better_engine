
#angularForce = False
angularForce = True

"""
	{'groups':[
		#"shoulder-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'end':[], 'time':50,
	'start':[(lambda Engine,EngineModule,objects,groupPart:
		groupPart.setMotorValues(10,20,angularForce))]
	},
	"""
SimpleAnimation = [
	{'groups':[
		"foot-joint",
		"lleg-joint",
		"uleg-joint",
		"belly-joint",
		"breast-joint",
		"neck-joint",
		"head-joint"
		"shoulder-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'end':[], 'time':500,
	'start':[(lambda Engine,EngineModule,objects,groupPart:
		groupPart.setMotorValues( (10**35)*1.5 , (10**35)*1.0 ,angularForce))]
	}
]
"""
,
{'groups':[
	#"shoulder-joint",
	"uarm-joint",
	"larm-joint",
	"hand-joint"
	],
'end':[], 'time':500,
'start':[(lambda Engine,EngineModule,objects,groupPart:
	groupPart.setMotorValues( (10**1)*1.5 , (10**1)*1.0 ,angularForce))]
}
"""

