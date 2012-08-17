
def selectContainerAdd(container,selection):
	if not container in selection:
		selection.append(container)
		container.selectShow()

def selectContainerRemove(container,selection):
	if container in selection:
		selection.remove(container)
		container.selectHide()

def selectContainerClear(selection):
	for container in selection:
		container.selectHide()
	selection = []

def init(Engine,EngineModule):
	pass

def keyDown(Engine,EngineModule,key,selection):
	pass

def keyPressed(Engine,EngineModule,key,selection):
	pass

	if key == EngineModule.Keys.K_MRIGHT:
		if Engine.isKeyDown(EngineModule.Keys.K_LSHIFT):
			pass
		else:
			selectContainerClear(selection)

		queryList = Engine.getMouseQuery()
		#q = queryList[0]
		for q in queryList:
			shape = Engine.getFromUuid(q[1])
			container = Engine.getObjectOfShape(Engine.getFromUuid(q[1]))
			if shape.isSelectable() and container.isSelectable():
				selectContainerAdd(container,selection)
				break

def keyReleased(Engine,EngineModule,key,selection):
	pass


