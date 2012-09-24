import random
import animation_helper
import anim_weight


def setLyingAnimation(Engine,EngineModule,objects):
	objects.get()["anims"]["stand"] = {"name":"lying","index":0,"starttime":Engine.getTime(),"done":True}
	return True

LyingAnimation = [
	{ 'time':2000,
	'timePos':[
		(lambda Engine,EngineModule,objects,timePos:
		animation_helper.setTiming(Engine,EngineModule,objects,
			timePos,1.0,0.5))
		]
	},
	{ 'time':100,
	'timePos':[
		(lambda Engine,EngineModule,objects,timePos:
		animation_helper.setTiming(Engine,EngineModule,objects,
			timePos,0.5,0.0))
		],
	'end':[
		(lambda Engine,EngineModule,objects,timePos:
		Engine.physicsPause()
		)
		]
	}
	]

SimpleAnimation = [
	{'groups':[
		"foot-joint",
		"lleg-joint",
		"uleg-joint",
		"belly-joint",
		"breast-joint",
		"shoulder-joint",
		"neck-joint",
		#"head-joint",
		"uarm-joint",
		"larm-joint",
		"hand-joint"
		],
	'time':1000,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		#groupPart.setMotorValues(0,0,True)
		groupPart.setMotorValues(0,100,True)
		)],
	'start':[
		#(lambda Engine,EngineModule,objects,timePos:
		#[part.setMotorValues(0,300,True) for part in objects.get()["head-joint"]]),

		#(lambda Engine,EngineModule,objects,timePos:
		#Engine.setTimingFactor(1.0)),

		(lambda Engine,EngineModule,objects,timePos:
		Engine.setGravity(EngineModule.Vec3(0,-350,0))),

		(lambda Engine,EngineModule,objects,timePos:
		anim_weight.resetAllMasses(Engine,EngineModule,objects)),

		#(lambda Engine,EngineModule,objects,timePos:
		#	anim_weight.multiplyAllMasses(Engine,EngineModule,objects,10.0)
		#	),

		(lambda Engine,EngineModule,objects,timePos:
		[animation_helper.applyForceToDebug(Engine,EngineModule,objects,
			part,500000) for part in objects.get()["breast"]]),
		(lambda Engine,EngineModule,objects,timePos:
		[animation_helper.applyForwardForce(Engine,EngineModule,objects,
			part,50000) for part in objects.get()["root"]])
		],
	'timePos':[
		(lambda Engine,EngineModule,objects,timePos:
			animation_helper.setTiming(Engine,EngineModule,objects,
				timePos,0.8,1.2)
			)
		#,
		#(lambda Engine,EngineModule,objects,timePos:
		#	anim_weight.multiplyAllMasses(Engine,EngineModule,objects,1.02)
		#	)
		]
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
	'time':800,
	'start-groups':[(lambda Engine,EngineModule,objects,groupPart:
		#groupPart.setMotorValues(0,350,True)
		groupPart.setMotorValues(10,200,True)
		)],

	'end':[
		(lambda Engine,EngineModule,objects,timePos:
		setLyingAnimation(Engine,EngineModule,objects)
		)
		]
	}

	]

