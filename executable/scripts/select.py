"""
select:
	mouseRight: create new selection
	lshift: add to selection
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
			if shape.isSelectable() and container.isSelectable():
				selectedContainer = container
				break

		if selectedContainer:
			if Engine.isKeyDown(EngineModule.Keys.K_LSHIFT):
				selection.add(selectedContainer)

			elif Engine.isKeyDown(EngineModule.Keys.K_LCONTROL):
				#TODO not working
				selection.remove(selectedContainer)
				pass
			else:
				selection.clear()
				selection.add(selectedContainer)
		else:
			pass
			#selection.clear()

	#TODO override unselectable by key

def keyReleased(Engine,EngineModule,key,selection,objects):
	pass


