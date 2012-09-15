import random
random.seed()
#random.seed(12345)
random.jumpahead(random.uniform(12345,9994949))

import scripts.temp as temp
import scripts.navigate as navigate
import scripts.select as select
#import scripts.powered_doll as powered_doll
import scripts.misc as misc
import scripts.creators as creators
import scripts.main as main
import scripts.anim as anim
import scripts.serialReader as serialReader
import scripts.test as test
import scripts.edit as edit
import scripts.operations as operations

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
			if hasattr(container,"selectShow"):
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

class Objects(object):
	def __init__(self):
		self.objects = {}
		self.unsavable = []

	def __str__(self):
		text = ""
		for k,v in self.objects.items():
			text += str(k) + " : " + str(v)
			text += "\n"
		return text

	def append(self,key,value):
		if key in self.objects:
			if not type(self.objects[key]) == list:
				self.objects[key] = [self.objects[key]]
			if type(value) == list:
				for e in value[:]:
					self.objects[key].append(e)
			else:
				self.objects[key].append(value)
		else:
			self.objects[key] = value

	def appendList(self,key,value):
		if key in self.objects:
			if not type(self.objects[key]) == list:
				self.objects[key] = [self.objects[key]]
			if type(value) == list:
				for e in value[:]:
					self.objects[key].append(e)
			else:
				self.objects[key].append(value)
		else:
			self.objects[key] = [value]

	def setUnsavable(self,key):
		if not key in self.unsavable:
			self.unsavable.append(key)

	def	isSavable(self,key):
		if key in self.unsavable:
			return False
		return True

	def get(self):
		return self.objects

objects = Objects()
selectContainers = Selection() 

modules = []
#modules.append(powered_doll)

modules.append(navigate)
modules.append(select)
modules.append(temp)
modules.append(creators)
modules.append(misc)
modules.append(anim)
modules.append(edit)
modules.append(operations)

#modules.append(test)
modules.append(serialReader)
#modules.append(main)

guiUpdates=[]

def init():
	for m in modules:
		if hasattr(m,"init"):
			m.init(Engine,EngineModule,objects)

	for m in modules:
		if hasattr(m,"guiUpdate"):
			#guiUpdates.append(m.guiUpdate)
			guiUpdates.append(getattr(m,"guiUpdate"))
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
	for method in guiUpdates:
		method(Engine,EngineModule,selectContainers,objects)
	pass

def physicUpdate():
	pass

