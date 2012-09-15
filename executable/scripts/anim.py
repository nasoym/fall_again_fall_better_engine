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
import animation_helper
import helpers

import anim_falling
import anim_rising

animLists={}
#animLists["falling"] = anim_falling.FallingAnim
#animLists["rising"] = anim_rising.RisingAnim

animLists["falling"] = anim_falling.SimpleAnimation
animLists["rising"] = anim_rising.SimpleAnimation

def init(Engine,EngineModule,objects):
	objects.get()["anims"] = {}
	objects.setUnsavable("anims")

	objects.get()["anims"]["stand"] = {"name":"rising","index":0,"starttime":Engine.getTime()}

	random.seed()

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

	jointGroupNames = [ "foot-joint", "lleg-joint", "uleg-joint", "belly-joint", "breast-joint", "shoulder-joint", "neck-joint", "head-joint", "uarm-joint", "larm-joint", "hand-joint" ]


	if key == EngineModule.Keys.K_LBRACKET:
		pass

		number = 0
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)
			#if o.isDynamicActor():
			if o.isJoint():
				number += 1
				print("found: " + o.getName())

		print("total : " + str(number))
		#bodyList = animation_helper.getBodyListFromGroupNameList(objects,bodyAllGroups)
		bodyList = animation_helper.getBodyListFromGroupNameList(objects,jointGroupNames)
		animation_helper.showBodyList(bodyList)
		print("list total : " + str(len(bodyList)))


		"""
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

		bodyList = animation_helper.getBodyListFromGroupName(objects,"feet")
		animation_helper.showBodyList(bodyList)
		bodyList = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodies)
		animation_helper.showBodyList(bodyList)
		"""

	if key == EngineModule.Keys.K_RBRACKET:
		pass
		b = Engine.createGuiBox()
		b.setColour(0,0,1,0.5)
		b.setSize(EngineModule.Vec3(10,10,10))
		b.setPosition(EngineModule.Vec3(0,200,0))
		objects.get()["head-debug"] = b



	if key == EngineModule.Keys.K_SPACE:
		if not "head" in objects.get():
			return

		if objects.get()["anims"]["stand"]["name"] == "falling":
			print("toggle animation: to rising")
			objects.get()["anims"]["stand"] = {
				"name":"rising","index":0,"starttime":Engine.getTime()}

		elif objects.get()["anims"]["stand"]["name"] == "rising":
			print("toggle animation: to falling")
			objects.get()["anims"]["stand"] = {
				"name":"falling","index":0,"starttime":Engine.getTime()}

