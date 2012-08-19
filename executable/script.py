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

class Selection(object):
	def __init__(self):
		self.selected = []

	def add(self,container):
		if not container in self.selected:
			self.selected.append(container)
			container.selectShow()

	def remove(self,container):
		if container in self.selected:
			self.selected.remove(container)
			container.selectHide()

	def clear(self):
		for container in self.selected:
			container.selectHide()
		for i in range(0,len(self.selected)):
			self.selected.pop()

	def get(self):
		return self.selected


objects = {}
#selectContainers = []
selectContainers = Selection() 

modules = []
modules.append(select)
modules.append(navigate)
modules.append(bonescale)
modules.append(temp)
modules.append(powered_doll)
modules.append(misc)
modules.append(creators)

def init():
	for m in modules:
		if hasattr(m,"init"):
			m.init(Engine,EngineModule,objects)

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

