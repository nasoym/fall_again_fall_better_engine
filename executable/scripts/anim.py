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
import datetime

import anim_falling
import anim_rising

import saveload


def reloadanim():
	reload(anim_falling)
	reload(anim_rising)
	#print("reloading external anim files")

reloadanim()

animLists={}
#animLists["falling"] = anim_falling.FallingAnim
#animLists["rising"] = anim_rising.RisingAnim

animLists["falling"] = anim_falling.SimpleAnimation
animLists["lying"] = anim_falling.LyingAnimation
animLists["rising"] = anim_rising.SimpleAnimation

def init(Engine,EngineModule,objects):
	if not "anims" in objects.get():
		objects.get()["anims"] = {}
		objects.setUnsavable("anims")
	random.seed()

	objects.get()["anims"]["stand"] = {"name":"rising","index":0,"starttime":Engine.getTime(),"done":True}
	Engine.setGravity(EngineModule.Vec3(0,-10,0))
	Engine.setTimingFactor(2.0)

def guiUpdate(Engine,EngineModule,selection,objects):
	for k,v in objects.get()["anims"].items():
		animName = v["name"]
		if animName in animLists:
			animList = animLists[animName]
			animation_helper.playAnimation(Engine,EngineModule,objects,v,animList)

def setMiddleArms(Engine,EngineModule,objects):
	bodyRightHandLine = [ "shoulder-r", "uarm-r", "larm-r", "hand-r" ]
	bodyLeftHandLine = [ "shoulder-l", "uarm-l", "larm-l", "hand-l" ]
	lHandLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyLeftHandLine)
	rHandLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyRightHandLine)
	animation_helper.multiplyMasses(lHandLine,100.0)
	animation_helper.multiplyMasses(rHandLine,100.0)

	animation_helper.multiplyMasses(animation_helper.getBodyListFromNameList(
		Engine,EngineModule,["hand-l"]),5.0)
	animation_helper.multiplyMasses(animation_helper.getBodyListFromNameList(
		Engine,EngineModule,["hand-r"]),5.0)


def setLight(Engine,EngineModule,objects):
	bodyAllGroups = ["feet","lleg","uleg","root","belly","breast","neck","head","shoulder","uarm","larm","hand"]
	bodyRightHeadLine = [ "toes-r", "foot-r", "lleg-r", "uleg-r", "root", "belly", "cheast", "breast", "neck", "head"]
	bodyLeftHeadLine = [ "toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head"]
	bodyRightHandLine = [ "breast", "shoulder-r", "uarm-r", "larm-r", "hand-r" ]
	bodyLeftHandLine = [ "breast", "shoulder-l", "uarm-l", "larm-l", "hand-l" ]
	bodyRightFingers = [ "thumb-high-r", "finger-index-high-r", "finger-middle-high-r", "finger-ring-high-r", "finger-little-high-r"]
	bodyLeftFingers = ["thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]

	allBodies = animation_helper.getBodyListFromGroupNameList(objects,bodyAllGroups)
	lHandLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyLeftHandLine)
	rHandLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyRightHandLine)
	lHeadLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyLeftHeadLine)
	rHeadLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyRightHeadLine)

	lFingers = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyLeftFingers)
	rFingers = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyRightFingers)

	feet = animation_helper.getBodyListFromGroupNameList(objects,["feet"])
	llegs = animation_helper.getBodyListFromGroupNameList(objects,["lleg"])




	animation_helper.resetMasses(allBodies)

	#animation_helper.approachEqualMassDistribution(allBodies,0.9)

	relation = 0.6
	relation = 0.4
	animation_helper.approachRelationToPrev(rHeadLine,relation,1.0)
	animation_helper.approachRelationToPrev(lHeadLine,relation,1.0)
	animation_helper.approachRelationToPrev(rHandLine,relation,1.0)
	animation_helper.approachRelationToPrev(lHandLine,relation,1.0)
	hand_l = helpers.getBodyFromName(Engine,EngineModule,"hand-l")
	if hand_l:
		animation_helper.setMasses(lFingers,hand_l.getMass()*relation)
	hand_r = helpers.getBodyFromName(Engine,EngineModule,"hand-r")
	if hand_r:
		animation_helper.setMasses(rFingers,hand_r.getMass()*relation)

	#animation_helper.approachEqualMassDistribution(allBodies,0.5)

	#animation_helper.approachEqualMassDistribution(feet,0.9)
	#animation_helper.approachEqualMassDistribution(llegs,0.9)
	
	#animation_helper.multiplyMasses(feet,3.0)
	#animation_helper.multiplyMasses(llegs,3.0)

	animation_helper.multiplyMasses(allBodies,0.01)
	#animation_helper.multiplyMasses(allBodies,0.1)


def setHeavy(Engine,EngineModule,objects):
	bodyAllGroups = ["feet","lleg","uleg","root","belly","breast","neck","head","shoulder","uarm","larm","hand"]
	allBodies = animation_helper.getBodyListFromGroupNameList(objects,bodyAllGroups)
	animation_helper.resetMasses(allBodies)

def setMiddle(Engine,EngineModule,objects):
	bodyAllGroups = ["feet","lleg","uleg","root","belly","breast","neck","head","shoulder","uarm","larm","hand"]
	allBodies = animation_helper.getBodyListFromGroupNameList(objects,bodyAllGroups)
	#animation_helper.resetMasses(allBodies)
	animation_helper.multiplyMasses(allBodies,1000.0)

def keyPressed(Engine,EngineModule,key,selection,objects):

	bodyAllGroups = ["feet","lleg","uleg","root","belly","breast","neck","head","shoulder","uarm","larm","hand"]

	bodyRightHeadLine = [ "toes-r", "foot-r", "lleg-r", "uleg-r", "root", "belly", "cheast", "breast", "neck", "head"]
	bodyLeftHeadLine = [ "toes-l", "foot-l", "lleg-l", "uleg-l", "root", "belly", "cheast", "breast", "neck", "head"]

	bodyRightHandLine = [ "breast", "shoulder-r", "uarm-r", "larm-r", "hand-r" ]
	bodyLeftHandLine = [ "breast", "shoulder-l", "uarm-l", "larm-l", "hand-l" ]

	bodyRightFingers = [ "thumb-high-r", "finger-index-high-r", "finger-middle-high-r", "finger-ring-high-r", "finger-little-high-r"]
	bodyLeftFingers = ["thumb-high-l", "finger-index-high-l", "finger-middle-high-l", "finger-ring-high-l", "finger-little-high-l"]



	allBodies = animation_helper.getBodyListFromGroupNameList(objects,bodyAllGroups)

	lHandLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyLeftHandLine)
	rHandLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyRightHandLine)
	lHeadLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyLeftHeadLine)
	rHeadLine = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyRightHeadLine)

	lFingers = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyLeftFingers)
	rFingers = animation_helper.getBodyListFromNameList(Engine,EngineModule,bodyRightFingers)

	feet = animation_helper.getBodyListFromGroupNameList(objects,["feet"])
	llegs = animation_helper.getBodyListFromGroupNameList(objects,["lleg"])

	jointGroupNames = [ "foot-joint", "lleg-joint", "uleg-joint", "belly-joint", "breast-joint", "shoulder-joint", "neck-joint", "head-joint", "uarm-joint", "larm-joint", "hand-joint" ]
	joints = animation_helper.getBodyListFromGroupNameList(objects,jointGroupNames)

	if key == EngineModule.Keys.K_LBRACKET:
		pass
		#head_joints = objects.get()["head-joint"]
		#print("head joints: " + str(head_joints))

		#bodies = objects.get()["larm-r"]
		for body in selection.get():
			if body.isActor():
				#body.removeFromScene()
				#body.moveBackToScene()
				body.dissableCollisions()
				#body.enableCollisions()


	if key == EngineModule.Keys.K_SPACE:
		if not "head" in objects.get():
			return
		#print("now: " + str(datetime.datetime.now()))
		#print(str(objects.get()["anims"]["stand"]["done"]))
		print("space is pressed")
		if objects.get()["anims"]["stand"]["done"]:
			if objects.get()["anims"]["stand"]["name"] == "rising":
				print("toggle animation: to falling")
				Engine.physicsUnpause()
				objects.get()["anims"]["stand"] = {
					"name":"falling","index":0,"starttime":Engine.getTime(),"done":False}
				setHeavy(Engine,EngineModule,objects)

				"""
				animation_helper.multiplyMasses(animation_helper.getBodyListFromNameList(
					Engine,EngineModule,["head"]),0.01)
				animation_helper.multiplyMasses(animation_helper.getBodyListFromNameList(
					Engine,EngineModule,["neck"]),0.01)
				animation_helper.multiplyMasses(animation_helper.getBodyListFromNameList(
					Engine,EngineModule,["breast"]),0.01)
					"""

				#setLight(Engine,EngineModule,objects)
				#setMiddle(Engine,EngineModule,objects)

				anim_falling.findMiddlePos(Engine,EngineModule,objects)

				Engine.setGravity(EngineModule.Vec3(0,-350,0))

				Engine.setTimingFactor(1.0)


		else:
			pass
			#print("set on done to true")
			#	objects.get()["anims"]["stand"]["ondone"] = True

def keyReleased(Engine,EngineModule,key,selection,objects):

	if key == EngineModule.Keys.K_SPACE:
		if not "head" in objects.get():
			return

		print("space is released")
		if objects.get()["anims"]["stand"]["done"]:
			if ((objects.get()["anims"]["stand"]["name"] == "falling") or 
				(objects.get()["anims"]["stand"]["name"] == "lying")
			):
				print("toggle animation: to rising")
				Engine.physicsUnpause()
				objects.get()["anims"]["stand"] = {
					"name":"rising","index":0,"starttime":Engine.getTime(),"done":False}
				setLight(Engine,EngineModule,objects)
				Engine.setGravity(EngineModule.Vec3(0,-10,0))

		else:
			print("set on done to true")
			objects.get()["anims"]["stand"]["ondone"] = True


