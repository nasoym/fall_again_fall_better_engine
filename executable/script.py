#import inspect

#import scripts.createobjects as create
#import scripts.ragdoll as ragdoll
#import scripts.saveload as saveload

import scripts.temp as temp
import scripts.navigate as navigate
import scripts.bonescale as bonescale
import scripts.select as select
import scripts.powered_doll as powered_doll
import scripts.misc as misc
import scripts.creators as creators
import scripts.main as main

class Selection(object):
	def __init__(self):
		self.selected = []

	def add(self,container):
		alreadyInSelection = False
		for i in range(0,len(self.selected)):
			if self.selected[i].readUuid() == container.readUuid():
				alreadyInSelection = True
				break
		if not alreadyInSelection:
			self.selected.append(container)
			container.selectShow()

	def remove(self,container):
		alreadyInSelection = False
		index = None
		for i in range(0,len(self.selected)):
			if self.selected[i].readUuid() == container.readUuid():
				alreadyInSelection = True
				index = i
				break
		if alreadyInSelection:
			self.selected.remove(self.selected[i])
			container.selectHide()

	def clear(self):
		for container in self.selected:
			container.selectHide()
		for i in range(0,len(self.selected)):
			self.selected.pop()

	def get(self):
		return self.selected


objects = {}
selectContainers = Selection() 

modules = []
modules.append(navigate)
modules.append(select)
modules.append(bonescale)
modules.append(temp)
modules.append(powered_doll)
modules.append(misc)
modules.append(creators)
#modules.append(main)

def init():
	for m in modules:
		if hasattr(m,"init"):
			m.init(Engine,EngineModule,objects)

	print("------------------------------------------------------------------ready")

def keyDown(key):
	for m in modules:
		if hasattr(m,"keyDown"):
			reload(m)
			m.keyDown(Engine,EngineModule,key,selectContainers,objects)

def keyPressed(key):
	for m in modules:
		if hasattr(m,"keyPressed"):
			reload(m)
			m.keyPressed(Engine,EngineModule,key,selectContainers,objects)

	if key == EngineModule.Keys.K_P:
		Engine.physicPauseToggle()

	if key == EngineModule.Keys.K_F1:
		print("")
		print("-" * 40)
		keyText = """
main: 
	f1: show all module info
	p: pause/unpause physics
"""
		print(keyText)
		for m in modules:
			print(m.__doc__)
		print("-" * 40)

def keyReleased(key):
	for m in modules:
		if hasattr(m,"keyReleased"):
			reload(m)
			m.keyReleased(Engine,EngineModule,key,selectContainers,objects)

def guiUpdate():
	pass

def physicUpdate():
	pass

