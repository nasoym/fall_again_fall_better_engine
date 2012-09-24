import animation_helper

#angularForce = False
angularForce = True

def removeFromScene(Engine,EngineModule,objects):
	if ("head" in objects.get() and
		"uarm" in objects.get() and
		"larm" in objects.get() and
		"hand" in objects.get() and
		"breast" in objects.get() and
		"belly" in objects.get() and
		"root" in objects.get() and
		"uleg" in objects.get()
	):
		l =  []
		l += objects.get()["head"] 
		l += objects.get()["uarm"]
		l += objects.get()["larm"]
		l += objects.get()["hand"]
		l += objects.get()["breast"]
		l += objects.get()["belly"]
		l += objects.get()["root"]
		l += objects.get()["uleg"]
		for part in l:
			part.dissableCollisions()

def dissableCollisions(Engine,EngineModule,objects,bodyNames):
	for name in bodyNames:
		if name in objects.get():
			bodyList = objects.get()[name]
			for body in bodyList:
				if body.isActor():
					body.dissableCollisions()

def enableCollisions(Engine,EngineModule,objects,bodyNames):
	for name in bodyNames:
		if name in objects.get():
			bodyList = objects.get()[name]
			for body in bodyList:
				if body.isActor():
					body.enableCollisions()

def backIntoScene(Engine,EngineModule,objects):
	if ("head" in objects.get() and
		"uarm" in objects.get() and
		"larm" in objects.get() and
		"hand" in objects.get() and
		"breast" in objects.get() and
		"belly" in objects.get() and
		"root" in objects.get() and
		"uleg" in objects.get()
	):
		l =  []
		l += objects.get()["head"] 
		l += objects.get()["uarm"]
		l += objects.get()["larm"]
		l += objects.get()["hand"]
		l += objects.get()["breast"]
		l += objects.get()["belly"]
		l += objects.get()["root"]
		l += objects.get()["uleg"]
		for part in l:
			part.enableCollisions()

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
	'time':1000,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		groupPart.setMotorValues( (10**35)*1.5 , (10**35)*1.0 ,angularForce))],
	'start':[(lambda Engine,EngineModule,objects,timePos:
			#removeFromScene(Engine,EngineModule,objects)
			dissableCollisions(Engine,EngineModule,objects,
				["head", "uarm", "larm", "hand", "breast", "belly", "root", "uleg"]
				)
			)
		],
	'end':[(lambda Engine,EngineModule,objects,timePos:
			#backIntoScene(Engine,EngineModule,objects)
			enableCollisions(Engine,EngineModule,objects,
				["head", "uarm", "larm", "hand", "breast", "belly", "root", "uleg"]
				)
			)
		],
	'timePos':[(lambda Engine,EngineModule,objects,timePos:
		animation_helper.setTiming(Engine,EngineModule,objects,timePos,0.1,5.0)
		)],
	}
]

