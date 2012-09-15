"""anim:
	[: select set of objects
	]: print all objects
	;: set masses of body parts
		1:set by fixed factor (0.02)
		2:double 3:half
		else:print masses
	space: toggle animation

"""

import random
random.seed()
import animation_helper
import helpers

import anim_falling
import anim_rising

animLists={}
animLists["falling"] = anim_falling.FallingAnim
animLists["rising"] = anim_rising.RisingAnim

def init(Engine,EngineModule,objects):
	objects.get()["anims"] = {}
	objects.setUnsavable("anims")

def guiUpdate(Engine,EngineModule,selection,objects):
	for k,v in objects.get()["anims"].items():
		animName = v["name"]
		if animName in animLists:
			animList = animLists[animName]
			animation_helper.playAnimation(Engine,EngineModule,objects,v,animList)

def keyPressed(Engine,EngineModule,key,selection,objects):

	bodyAllGroups = ["feet","lleg","uleg","root","belly","breast","neck","head","shoulder","uarm","larm","hand"]
	bodyRightHeadLine = [ "toes-r", "foot-r", "lleg-r", "uleg-r", "root", "belly", "cheast", "breast", "neck", "head"]
	bodyLeftHeadLine = [ "toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head"]
	bodyRightHandLine = [ "toes-r", "foot-r", "lleg-r", "uleg-r", "root", "belly", "cheast", "breast", "shoulder-r", "uarm-r", "larm-r", "hand-r" ]
	bodyLeftHandLine = [ "toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "shoulder-l", "uarm-l", "larm-l", "hand-l" ]
	bodyRightFingers = [ "thumb-high-r", "finger-index-high-r", "finger-middle-high-r", "finger-ring-high-r", "finger-rittle-high-r"]
	bodyLeftFingers = ["thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ling-high-l", "finger-little-high-l"]

	if key == EngineModule.Keys.K_SPACE:
		if not "head" in objects.get():
			return

		if not "stand" in objects.get()["anims"]:
			print("toggle animation: to falling")
			objects.get()["anims"]["stand"] = {
				"name":"falling","index":0,"starttime":Engine.getTime()}
		else:
			if objects.get()["anims"]["stand"]["name"] == "falling":
				print("toggle animation: to rising")
				objects.get()["anims"]["stand"] = {
					"name":"rising","index":0,"starttime":Engine.getTime()}

				#setMasses(Engine,EngineModule,selection,objects,0.01)

				"""
				setMassesList(Engine,EngineModule,selection,
					objects,10,["feet","lleg"])
				setMassesList(Engine,EngineModule,selection,
					objects,20,["uleg"])

				setMassesList(Engine,EngineModule,selection,
					objects,0.02,["root","belly","breast"])

				setMassesList(Engine,EngineModule,selection,
					objects,0.1,["uarm","larm","hand","shoulder","neck"])

				setMassesList(Engine,EngineModule,selection,
					objects,0.01,["head"])

				bodies = ["toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head","shoulder-l","uarm-l","larm-l","hand-l", "thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]
				calcMasses(Engine,EngineModule,bodies,0.2)

				bodies = ["toes-r", "foot-r", "lleg-r", "uleg-r", "root", "belly", "cheast", "breast", "neck", "head","shoulder-r","uarm-r","larm-r","hand-r", "thumb-high-r", "finger-index-high-r", "finger-middle-high-r", "finger-ring-high-r", "finger-little-high-r"]
				calcMasses(Engine,EngineModule,bodies,0.2)
					"""


				parts = ["feet","lleg","uleg","root","belly",
					"breast","shoulder","neck","uarm","larm","head","hand"]
				for p in parts:
					bodyList = objects.get()[p]
					for b in bodyList:
						newMass = b.getMass() * 0.5
						b.setMass(newMass)

				bodies = ["toes-l", "foot-l", "lleg-l", "uleg-l"]
				calcMasses(Engine,EngineModule,bodies,0.2)

				bodies = ["toes-r", "foot-r", "lleg-r", "uleg-r"]
				calcMasses(Engine,EngineModule,bodies,0.2)

				bodies = ["uleg-l", "root", "belly", "cheast", "breast", "neck", "head","shoulder-l","uarm-l","larm-l","hand-l", "thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]
				calcMasses(Engine,EngineModule,bodies,0.5)

				bodies = ["uleg-r", "root", "belly", "cheast", "breast", "neck", "head","shoulder-r","uarm-r","larm-r","hand-r", "thumb-high-r", "finger-index-high-r", "finger-middle-high-r", "finger-ring-high-r", "finger-little-high-r"]
				calcMasses(Engine,EngineModule,bodies,0.5)

			elif objects.get()["anims"]["stand"]["name"] == "rising":
				print("toggle animation: to falling")

				setMasses(Engine,EngineModule,selection,objects,fallingMass)

				partsList = objects.get()["head"]
				for part in partsList:
					part.setMass(part.getMass() * 0.3)

				partsList = objects.get()["breast"]
				for part in partsList:
					part.setMass(part.getMass() * 0.3)

				objects.get()["anims"]["stand"] = {
					"name":"falling","index":0,"starttime":Engine.getTime()}


	if key == EngineModule.Keys.K_SEMICOLON:
		pass
		allBodyList = ["toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head","shoulder-l","uarm-l","larm-l","hand-l", "thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]
		bodies = ["uleg-l", "root", "belly", "cheast", "breast", "neck", "head","shoulder-l","uarm-l","larm-l","hand-l", "thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]
		bodies = ["toes-l", 
			"foot-l", 
			"lleg-l", 
			"uleg-l", 
			"root", 
			"belly", 
			"cheast", 
			"breast", 
			"neck", 
			"head"
			]

		print("------------setMassRelations-------------")
		bodyList = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodies)
		animation_helper.resetMasses(bodyList)
		print("-------------------------")

		#animation_helper.showMassRelationToPrev(bodyList)
		#animation_helper.approachRelationToPrev(bodyList,0.5,0.5)
		#print("-------------------------")
		#animation_helper.showMassRelationToPrev(bodyList)

		animation_helper.showMassRelationToAll(bodyList)
		animation_helper.approachEqualMassDistribution(bodyList,0.5)
		print("-------------------------")
		animation_helper.showMassRelationToAll(bodyList)

	if key == EngineModule.Keys.K_RBRACKET:
		pass
		b = Engine.createGuiBox()
		b.setColour(0,0,1,0.5)
		b.setSize(EngineModule.Vec3(10,10,10))
		b.setPosition(EngineModule.Vec3(0,200,0))
		objects.get()["head-debug"] = b

	if key == EngineModule.Keys.K_LBRACKET:
		pass
		print("l")
		bodies = ["toes-l", 
			"foot-l", 
			"lleg-l", 
			"uleg-l", 
			"root", 
			"belly", 
			"cheast", 
			"breast", 
			"neck", 
			"head"
			]
		bodyList = animation_helper.getBodyListFromGroupName(objects,"feet")
		animation_helper.showBodyList(bodyList)
		bodyList = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodies)
		animation_helper.showBodyList(bodyList)






def setMasses(Engine,EngineModule,selection,objects,factor):
	parts = ["feet","lleg","uleg","root","belly",
		"breast","shoulder","neck","uarm","larm","head","hand"]
	for p in parts:
		bodyList = objects.get()[p]
		for b in bodyList:
			b.resetMass()
			newMass = b.getMass() * factor
			b.setMass(newMass)

def setMassesList(Engine,EngineModule,selection,objects,parts,factor):
	for p in parts:
		if p in objects.get():
			bodyList = objects.get()[p]
			if bodyList:
				for b in bodyList:
					if b:
						b.setMass(b.getMass() * factor)

def calcMasses(Engine,EngineModule,bodies,factor):
	for i in range(0,len(bodies)):
		bodyName = bodies[i]
		body = helpers.getBodyFromName(Engine,EngineModule,bodyName)
		if body:
			bodyMass = body.getMass()
			if i > 0:
				otherBodyName = bodies[i-1]
				otherBody = helpers.getBodyFromName(Engine,EngineModule,otherBodyName)
				otherBodyMass = otherBody.getMass()
				body.setMass( otherBodyMass * factor);

