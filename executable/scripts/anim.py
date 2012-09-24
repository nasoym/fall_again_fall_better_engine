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
import helpers
import datetime

import anim_falling
import anim_rising
import animation_helper
import anim_weight

import saveload


def reloadanim():
	reload(anim_falling)
	reload(anim_rising)
	reload(anim_weight)
	reload(animation_helper)
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


def keyPressed(Engine,EngineModule,key,selection,objects):

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
		print("space is pressed")
		if objects.get()["anims"]["stand"]["done"]:
			if objects.get()["anims"]["stand"]["name"] == "rising":
				print("toggle animation: to falling")
				Engine.physicsUnpause()
				objects.get()["anims"]["stand"] = {
					"name":"falling","index":0,"starttime":Engine.getTime(),"done":False}
				animation_helper.findMiddlePos(Engine,EngineModule,objects)
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

		else:
			print("set on done to true")
			objects.get()["anims"]["stand"]["ondone"] = True


