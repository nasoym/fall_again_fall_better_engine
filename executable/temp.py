import libxml2

def launch(Engine,EngineModule,objects):

	#Engine.setTimingFactor(0.0001)
	#print("timingfactor: " +str(Engine.getTimingFactor()))

	objects["mesh"] = Engine.createMesh("Character.mesh")
	#objects["mesh"] = Engine.createMesh("tube.mesh")
	#objects["mesh"] = Engine.createMesh("Cube.mesh")
	#objects["mesh"] = Engine.createMesh("sphere.mesh")
	#Engine.simulatePhysics(1.0/60.0)
	#Engine.physicPauseToggle()

	#objects["mesh"].setSize(EngineModule.Vec3(1000,1000,1000))

def loadStringArray(node,attributeName):
	stringArray = (node.prop(attributeName)
		.replace("[","")
		.replace("]","")
		.replace("'","")
		.replace(" ","")
		.split(","))
	if (len(stringArray)==1 and stringArray[0]==''):
		stringArray = []
	return [ num for num in stringArray ]

def isGuiContainerFullfilled(node,Engine,EngineModule):
	shapes = loadStringArray(node,"shapes")
	allShapesExist = True
	for shape in shapes:
		if not Engine.getFromUuid(shape):
			allShapesExist = False
	return allShapesExist

def loadGuiContainer(node,Engine,EngineModule,engineObject):
	shapes = loadStringArray(node,"shapes")
	for shape in shapes:
		if Engine.getFromUuid(shape):
			engineObject.addShape(Engine.getFromUuid(shape))

def saveGuiContainer(node,Engine,EngineModule,engineObject):
	shapesNumber = engineObject.howManyShapes()
	shapesList = []
	for i in range(0,shapesNumber):
		shape = engineObject.getShapeByIndex(i)
		shapesList.append(shape.readUuid())
	node.setProp("shapes",str(shapesList))

def loadSize(node,Engine,EngineModule,engineObject):
	a = (node.prop("size").split(","))
	size = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
	engineObject.setSize(size)

def loadPosition(node,Engine,EngineModule,engineObject):
	a = (node.prop("position").split(","))
	pos = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
	engineObject.setPosition(pos)

def loadOrientation(node,Engine,EngineModule,engineObject):
	a = (node.prop("orientation").split(","))
	orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
	engineObject.setOrientation(orientation)

def loadEngineObject(node,Engine,EngineModule,engineObject):
	uuid = node.prop("uuid")
	engineObject.setUuid(uuid)
	#name = node.prop("name")
	#engineObject.setName(name)

def init(Engine,EngineModule,objects):
	pass

def keyDown(Engine,EngineModule,objects,key):
	pass

def keyPressed(Engine,EngineModule,objects,key):
	if key == EngineModule.Keys.K_7:
		"""
		objectsNumber = Engine.howManyObjects()
		print("objects: " + str(objectsNumber))
		for i in range(0,objectsNumber):
			print(i)
			print(Engine.getObject(i))
			print(Engine.getObject(i).getType())
			"""
		doc = libxml2.parseFile("xmlscene/file1.xml")
		xctxt = doc.xpathNewContext()
		res = xctxt.xpathEval("/scene/*")
		while(len(res)>0):
			for node in res[:]:
				pass

				if node.name==str(EngineModule.ObjectType.JOINT):
					body1 = node.prop("body1")
					body2 = node.prop("body2")
					if (isGuiContainerFullfilled(node,Engine,EngineModule) and Engine.getFromUuid(body1) and Engine.getFromUuid(body2)):
						o = Engine.createLLJoint(Engine.getFromUuid(body1),Engine.getFromUuid(body2))
						a = (node.prop("anchor1").split(","))
						anchor1 = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
						a = (node.prop("anchor2").split(","))
						anchor2 = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
						a = (node.prop("anchor1orientation").split(","))
						anchor1orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
						a = (node.prop("anchor2orientation").split(","))
						anchor2orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
						ylimit = node.prop("ylimit")
						zlimit = node.prop("zlimit")
						o.setAnchor1(anchor1)
						o.setAnchor2(anchor2)
						o.setAnchor1Orientation(anchor1orientation)
						o.setAnchor2Orientation(anchor2orientation)
						o.setLimits(float(ylimit),float(zlimit))
						res.remove(node)

				elif node.name==str(EngineModule.ObjectType.BOX):
					o = Engine.createLLBox()
					loadEngineObject(node,Engine,EngineModule,o)
					loadSize(node,Engine,EngineModule,o)
					loadPosition(node,Engine,EngineModule,o)
					loadOrientation(node,Engine,EngineModule,o)
					res.remove(node)

				elif node.name==str(EngineModule.ObjectType.BODY):
					if isGuiContainerFullfilled(node,Engine,EngineModule):
						o = Engine.createLLPhysicBody()
						loadGuiContainer(node,Engine,EngineModule,o)
						loadEngineObject(node,Engine,EngineModule,o)
						loadSize(node,Engine,EngineModule,o)
						loadPosition(node,Engine,EngineModule,o)
						loadOrientation(node,Engine,EngineModule,o)
						res.remove(node)

				elif node.name==str(EngineModule.ObjectType.SPACECAGE):
					if isGuiContainerFullfilled(node,Engine,EngineModule):
						a = (node.prop("size").split(","))
						size = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
						o = Engine.createLLSpaceCage(size)
						loadGuiContainer(node,Engine,EngineModule,o)
						loadEngineObject(node,Engine,EngineModule,o)
						res.remove(node)

	if key == EngineModule.Keys.K_6:
		doc = libxml2.newDoc("1.0")
		rootNode = libxml2.newNode("scene")
		doc.addChild(rootNode)
		objectsNumber = Engine.howManyObjects()
		for i in range(0,objectsNumber):
			o = Engine.getObject(i)
			#print(o)
			#print(dir(o))
			#print(o.isGuiShape())
			#print(o.getType())

			node = libxml2.newNode(str(o.getType()))
			node.setProp("uuid",str(o.readUuid()))
			node.setProp("name",str(o.getName()))
			if o.getType()==EngineModule.ObjectType.GUISHAPE:
				pass

			elif o.getType()==EngineModule.ObjectType.GUICONTAINER:
				pass
			elif o.getType()==EngineModule.ObjectType.MESH:
				pass

			elif o.getType()==EngineModule.ObjectType.BODY:
				saveGuiContainer(node,Engine,EngineModule,o)
				node.setProp("position",str(o.getPosition()))
				node.setProp("size",str(o.getSize()))
				node.setProp("orientation",str(o.getOrientation()))

			elif o.getType()==EngineModule.ObjectType.BOX:
				node.setProp("position",str(o.getPosition()))
				node.setProp("size",str(o.getSize()))
				node.setProp("orientation",str(o.getOrientation()))
				#localPos,Orien,Size  material colour scaling type

			elif o.getType()==EngineModule.ObjectType.JOINT:
				saveGuiContainer(node,Engine,EngineModule,o)
				node.setProp("body1",str(o.getBody1().readUuid()))
				node.setProp("body2",str(o.getBody2().readUuid()))
				node.setProp("anchor1",str(o.getAnchor1()))
				node.setProp("anchor2",str(o.getAnchor2()))
				node.setProp("anchor1orientation",str(o.getAnchor1Orientation()))
				node.setProp("anchor2orientation",str(o.getAnchor2Orientation()))
				node.setProp("ylimit",str(o.getYLimit()))
				node.setProp("zlimit",str(o.getZLimit()))

			elif o.getType()==EngineModule.ObjectType.SPACECAGE:
				saveGuiContainer(node,Engine,EngineModule,o)
				node.setProp("size",str(o.getSize()))

			doc.getRootElement().addChild(node)

		doc.saveFormatFile("xmlscene/file1.xml",1)

	pass

def keyReleased(Engine,EngineModule,objects,key):
	pass

