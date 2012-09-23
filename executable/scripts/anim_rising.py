
#angularForce = False
angularForce = True

def removeFromScene(Engine,EngineModule,objects):
	if ("head" in objects.get() and
		"uarm" in objects.get() and
		"larm" in objects.get() and
		"hand" in objects.get() 
	):
		l =  []
		l += objects.get()["head"] 
		l += objects.get()["uarm"]
		l += objects.get()["larm"]
		l += objects.get()["hand"]
		for part in l:
			#part.removeFromScene() 
			part.dissableCollisions()

def backIntoScene(Engine,EngineModule,objects):
	if ("head" in objects.get() and
		"uarm" in objects.get() and
		"larm" in objects.get() and
		"hand" in objects.get() 
	):
		l =  []
		l += objects.get()["head"] 
		l += objects.get()["uarm"]
		l += objects.get()["larm"]
		l += objects.get()["hand"]
		for part in l:
			#part.removeFromScene() 
			part.enableCollisions()

def setTiming(Engine,EngineModule,objects,timePos,startFactor,endFactor):
	timingDelta = endFactor - startFactor
	timing = startFactor + (timingDelta * timePos)
	Engine.setTimingFactor(timing)
	#print("timing: " + str(timing))
	return True
	
SimpleAnimation = [
	{'groups':[
		"foot-joint",
		"lleg-joint",
		"uleg-joint",
		"belly-joint",
		"breast-joint",
		"neck-joint",
		"head-joint",
		"shoulder-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'time':1500,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		groupPart.setMotorValues( (10**35)*1.5 , (10**35)*1.0 ,angularForce))],
	'start':[
		(lambda Engine,EngineModule,objects,timePos:
			#True
			removeFromScene(Engine,EngineModule,objects)
		)
		],
	'end':[
		(lambda Engine,EngineModule,objects,timePos:
			#True
			backIntoScene(Engine,EngineModule,objects)
		)
		],
	'timePos':[(lambda Engine,EngineModule,objects,timePos:
		setTiming(Engine,EngineModule,objects,timePos,0.5,3.0)
		)],
	}
]
"""
	{'groups':[
		"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'time':100,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		groupPart.setMotorValues(0,0,angularForce))]
	},
	,
	{'groups':[
		"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'time':100,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		groupPart.setMotorValues( (10**35)*1.5 , (10**35)*1.0 ,angularForce))],
	},
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

