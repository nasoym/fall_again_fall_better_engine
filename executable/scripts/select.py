"""
select:
	mouseRight: create new selection
	lshift: add to selection
	lctrl: remove from selection
	lalt: select unselectable
"""

def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,key,selection,objects):
	pass

def keyPressed(Engine,EngineModule,key,selection,objects):
	pass

	if key == EngineModule.Keys.K_MRIGHT:
		selectedContainer = None
		queryList = Engine.getMouseQuery()
		for q in queryList:
			shape = Engine.getFromUuid(q[1])
			container = Engine.getObjectOfShape(Engine.getFromUuid(q[1]))
			if Engine.isKeyDown(EngineModule.Keys.K_LMENU):
				selectedContainer = container
				break
			else:
				if shape.isSelectable() and container.isSelectable():
					selectedContainer = container
					break

		if selectedContainer:
			if Engine.isKeyDown(EngineModule.Keys.K_LSHIFT):
				selection.add(selectedContainer)

			elif Engine.isKeyDown(EngineModule.Keys.K_LCONTROL):
				selection.remove(selectedContainer)
				pass

			else:
				selection.clear()
				selection.add(selectedContainer)
		else:
			pass
			selection.clear()

	if key == EngineModule.Keys.K_BACK:
		for o in selection.get()[:]:
			selection.remove(o)
			#TODO why is object deletion not working
			#Engine.deleteObject(o)

	if key == EngineModule.Keys.K_I:
		for o in selection.get():
			print("object: " + str(o))
			print("name: " + str(o.getName()))
			print("uuid: " + str(o.readUuid()))

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass


