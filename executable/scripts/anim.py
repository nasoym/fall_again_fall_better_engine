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


def reloadanim():
	reload(anim_falling)
	reload(anim_rising)
	print("reloading external anim files")

reloadanim()


animLists={}
#animLists["falling"] = anim_falling.FallingAnim
#animLists["rising"] = anim_rising.RisingAnim

animLists["falling"] = anim_falling.SimpleAnimation
animLists["rising"] = anim_rising.SimpleAnimation

def init(Engine,EngineModule,objects):
	objects.get()["anims"] = {}
	objects.setUnsavable("anims")
	random.seed()

	objects.get()["anims"]["stand"] = {"name":"falling","index":0,"starttime":Engine.getTime()}

def guiUpdate(Engine,EngineModule,selection,objects):
	for k,v in objects.get()["anims"].items():
		animName = v["name"]
		if animName in animLists:
			animList = animLists[animName]
			animation_helper.playAnimation(Engine,EngineModule,objects,v,animList)

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
	animation_helper.setMasses(lFingers,
		helpers.getBodyFromName(Engine,EngineModule,"hand-l").getMass()*relation)
	animation_helper.setMasses(rFingers,
		helpers.getBodyFromName(Engine,EngineModule,"hand-r").getMass()*relation)

	#animation_helper.approachEqualMassDistribution(allBodies,0.5)

	#animation_helper.approachEqualMassDistribution(feet,0.9)
	#animation_helper.approachEqualMassDistribution(llegs,0.9)
	
	#animation_helper.multiplyMasses(feet,3.0)
	#animation_helper.multiplyMasses(llegs,3.0)

	animation_helper.multiplyMasses(allBodies,0.01)
	#animation_helper.multiplyMasses(allBodies,0.1)

	Engine.setGravity(EngineModule.Vec3(0,35,0))

def setHeavy(Engine,EngineModule,objects):
	bodyAllGroups = ["feet","lleg","uleg","root","belly","breast","neck","head","shoulder","uarm","larm","hand"]
	allBodies = animation_helper.getBodyListFromGroupNameList(objects,bodyAllGroups)
	animation_helper.resetMasses(allBodies)
	Engine.setGravity(EngineModule.Vec3(0,-10,0))

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

	if key == EngineModule.Keys.K_SEMICOLON:
		print("reset masses")
		animation_helper.resetMasses(allBodies)

	if key == EngineModule.Keys.K_LBRACKET:
		pass
		print("modify masses")
		setLight(Engine,EngineModule,objects)

	if key == EngineModule.Keys.K_RBRACKET:
		pass
		print("------------------------------------------------------")

		animation_helper.showBodyList(joints)

		"""
		print("right head line:")
		animation_helper.showMassRelationToPrev(rHeadLine)

		print("left head line:")
		animation_helper.showMassRelationToPrev(lHeadLine)

		print("right hand line:")
		animation_helper.showMassRelationToPrev(rHandLine)

		print("left hand line:")
		animation_helper.showMassRelationToPrev(lHandLine)

		print("right fingers:")
		animation_helper.showBodyList(rFingers)

		print("left fingers:")
		animation_helper.showBodyList(lFingers)

		#showMassRelationToAll(bodyList)
		"""


		"""
		b = Engine.createGuiBox()
		b.setColour(0,0,1,0.5)
		b.setSize(EngineModule.Vec3(10,10,10))
		b.setPosition(EngineModule.Vec3(0,200,0))
		objects.get()["head-debug"] = b
		"""


	if key == EngineModule.Keys.K_SPACE:
		if not "head" in objects.get():
			return

		if objects.get()["anims"]["stand"]["name"] == "falling":
			print("toggle animation: to rising")
			objects.get()["anims"]["stand"] = {
				"name":"rising","index":0,"starttime":Engine.getTime()}
			setLight(Engine,EngineModule,objects)

		elif objects.get()["anims"]["stand"]["name"] == "rising":
			print("toggle animation: to falling")
			objects.get()["anims"]["stand"] = {
				"name":"falling","index":0,"starttime":Engine.getTime()}
			setHeavy(Engine,EngineModule,objects)
			Engine.setGravity(EngineModule.Vec3(0,-30,0))




