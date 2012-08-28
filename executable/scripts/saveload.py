import libxml2

def addToUuidTable(Engine,uuidTable,uuid):
	if not uuid in uuidTable:
		uuidTable[uuid] = Engine.createUuid()

def getFromUuidTable(Engine,uuidTable,uuid):
	if uuid in uuidTable:
		return uuidTable[uuid]
	else:
		addToUuidTable(Engine,uuidTable,uuid)
		return uuidTable[uuid]

def load(Engine,EngineModule,fileName,objects):
	doc = libxml2.parseFile(fileName)
	xctxt = doc.xpathNewContext()
	res = xctxt.xpathEval("/scene/*")

	uuidTable = {}

	lastUnresolved=""
	lastResultLength = 0

	while(len(res)>0):

		if len(res) == lastResultLength:
			print("could not resolve dependencies:" + str(lastResultLength))
			print(str(res))
			print(lastUnresolved)
			break
		lastResultLength = len(res)
		for node in res[:]:

			if node.name==str(EngineModule.ObjectType.JOINT):
				if node.hasProp("body1") and node.hasProp("body2"):
					body1 = node.prop("body1")
					body2 = node.prop("body2")

					body1 = getFromUuidTable(Engine,uuidTable,body1)
					body2 = getFromUuidTable(Engine,uuidTable,body2)

					if (isGuiContainerFullfilled(node,Engine,EngineModule,uuidTable) and Engine.getFromUuid(body1) and Engine.getFromUuid(body2)):
						o = Engine.createJoint(Engine.getFromUuid(body1),Engine.getFromUuid(body2))
						loadGuiContainer(node,Engine,EngineModule,o,uuidTable)
						if node.hasProp("anchor1"):
							a = (node.prop("anchor1").split(","))
							anchor1 = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
							o.setAnchor1(anchor1)
						if node.hasProp("anchor2"):
							a = (node.prop("anchor2").split(","))
							anchor2 = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
							o.setAnchor2(anchor2)
						if node.hasProp("anchor1orientation"):
							a = (node.prop("anchor1orientation").split(","))
							anchor1orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
							o.setAnchor1Orientation(anchor1orientation)
						if node.hasProp("anchor2orientation"):
							a = (node.prop("anchor2orientation").split(","))
							anchor2orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
							o.setAnchor2Orientation(anchor2orientation)
						ylimit=0
						zlimit=0
						if node.hasProp("ylimit"):
							ylimit = node.prop("ylimit")
						if node.hasProp("zlimit"):
							zlimit = node.prop("zlimit")
						o.setLimits(float(ylimit),float(zlimit))

						if node.hasProp("motor_target"):
							a = (node.prop("motor_target").split(","))
							motorTarget = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
							o.setMotorTarget(motorTarget)
						if node.hasProp("motor_on"):
							motorOn = loadBool(node,"motor_on")
							if motorOn:
								o.setMotorOn()
							else:
								o.setMotorOff()

						if node.hasProp("uuid"):
							uuid = node.prop("uuid")
							uuid = getFromUuidTable(Engine,uuidTable,uuid)
							o.setUuid(uuid)
						loadEngineObject(node,Engine,EngineModule,o)
						res.remove(node)
					else:
						lastUnresolved = "joint: "
				else:
					res.remove(node)

			elif node.name==str(EngineModule.ObjectType.GUISHAPE):
				res.remove(node)

			elif node.name==str(EngineModule.ObjectType.GUICONTAINER):
				res.remove(node)

			elif node.name==str(EngineModule.ObjectType.MESH):
				bonesList = loadTupleArray(node,"bones")
				allObjectsExist = True
				for boneData in bonesList:
					bonename = boneData[0]
					bodyUuid = boneData[1]
					jointUuid = boneData[2]
					if not bodyUuid == "0":
						bodyUuid = getFromUuidTable(Engine,uuidTable,bodyUuid)
						if not Engine.getFromUuid(bodyUuid):
							allObjectsExist = False
							lastUnresolved = "mesh:  missing: body: " + str(bodyUuid)
							break
					if not jointUuid == "0": 
						jointUuid = getFromUuidTable(Engine,uuidTable,jointUuid)
						if not Engine.getFromUuid(jointUuid):
							allObjectsExist = False
							lastUnresolved = "mesh:  missing: joint: " + str(jointUuid)
							break
				if allObjectsExist:
					if node.hasProp("mesh_file"):
						meshFile = node.prop("mesh_file")
						o = Engine.createMesh(meshFile)
						if node.hasProp("uuid"):
							uuid = node.prop("uuid")
							uuid = getFromUuidTable(Engine,uuidTable,uuid)
							o.setUuid(uuid)
						loadEngineObject(node,Engine,EngineModule,o)
						loadSize(node,Engine,EngineModule,o)
						loadPosition(node,Engine,EngineModule,o)
						loadOrientation(node,Engine,EngineModule,o)
						for boneData in bonesList:
							boneName = boneData[0]
							bodyUuid = boneData[1]
							jointUuid = boneData[2]
							if not bodyUuid == "0":
								bodyUuid = getFromUuidTable(Engine,uuidTable,bodyUuid)
								o.setBodyForBoneName(
									boneName,
									Engine.getFromUuid(bodyUuid))
							if not jointUuid == "0":
								jointUuid = getFromUuidTable(Engine,uuidTable,jointUuid)
								o.setJointForBoneName(
									boneName,
									Engine.getFromUuid(jointUuid))

						if node.hasProp("colour") and node.hasProp("alpha"):
							alpha = float(node.prop("alpha"))
							a = (node.prop("colour").split(","))
							colour = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
							o.setColour(colour.X(),colour.Y(),colour.Z(),alpha)
						if node.hasProp("material"):
							materialName = node.prop("material")
							o.setMaterialName(materialName)

						finalShape = loadBool(node,"final_shape")
						if finalShape:
							o.setFinalShape()
						else:
							o.setNonFinalShape()

					res.remove(node)

			elif node.name==str(EngineModule.ObjectType.BOX):
				o = Engine.createGuiBox()
				if node.hasProp("uuid"):
					uuid = node.prop("uuid")
					uuid = getFromUuidTable(Engine,uuidTable,uuid)
					o.setUuid(uuid)
				loadEngineObject(node,Engine,EngineModule,o)
				loadSize(node,Engine,EngineModule,o)
				loadPosition(node,Engine,EngineModule,o)
				loadOrientation(node,Engine,EngineModule,o)

				if node.hasProp("colour") and node.hasProp("alpha"):
					alpha = float(node.prop("alpha"))
					a = (node.prop("colour").split(","))
					colour = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
					o.setColour(colour.X(),colour.Y(),colour.Z(),alpha)
				if node.hasProp("material"):
					materialName = node.prop("material")
					o.setMaterialName(materialName)

				#if node.hasProp("local_size"):
				#	a = (node.prop("local_size").split(","))
				#	size = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
				#	o.setLocalSize(size)
				if node.hasProp("local_position"):
					a = (node.prop("local_position").split(","))
					pos = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
					o.setLocalPosition(pos)
				if node.hasProp("local_orientation"):
					a = (node.prop("local_orientation").split(","))
					orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
					o.setLocalOrientation(orientation)


				if node.hasProp("scaling"):
					scalingType = node.prop("scaling")
					if scalingType == "None":
						o.setScalingNone()
					elif scalingType == "Fixed":
						o.setScalingFixed()
					elif scalingType == "1To1":
						o.setScaling1To1()
					elif scalingType == "Scaling":
						o.setScalingScaling()
				castShadows = loadBool(node,"cast_shadows")
				if castShadows:
					o.turnOnShadows()
				else:
					o.turnOffShadows()

				finalShape = loadBool(node,"final_shape")
				if finalShape:
					o.setFinalShape()
				else:
					o.setNonFinalShape()

				res.remove(node)

			elif node.name==str(EngineModule.ObjectType.STATICBODY):
				if isGuiContainerFullfilled(node,Engine,EngineModule,uuidTable):
					o = Engine.createPhysicStatic()
					loadGuiContainer(node,Engine,EngineModule,o,uuidTable)
					if node.hasProp("uuid"):
						uuid = node.prop("uuid")
						uuid = getFromUuidTable(Engine,uuidTable,uuid)
						o.setUuid(uuid)
					loadEngineObject(node,Engine,EngineModule,o)
					loadSize(node,Engine,EngineModule,o)
					loadPosition(node,Engine,EngineModule,o)
					loadOrientation(node,Engine,EngineModule,o)
					res.remove(node)
				else:
					lastUnresolved = "staticbody: gui container failed"

			elif node.name==str(EngineModule.ObjectType.BODY):
				if isGuiContainerFullfilled(node,Engine,EngineModule,uuidTable):
					o = Engine.createPhysicBox()
					loadGuiContainer(node,Engine,EngineModule,o,uuidTable)
					if node.hasProp("uuid"):
						uuid = node.prop("uuid")
						uuid = getFromUuidTable(Engine,uuidTable,uuid)
						o.setUuid(uuid)
					loadEngineObject(node,Engine,EngineModule,o)
					loadSize(node,Engine,EngineModule,o)
					loadPosition(node,Engine,EngineModule,o)
					loadOrientation(node,Engine,EngineModule,o)
					res.remove(node)
				else:
					lastUnresolved = "body: gui container failed"

			elif node.name==str(EngineModule.ObjectType.SPACECAGE):
				if isGuiContainerFullfilled(node,Engine,EngineModule,uuidTable):
					if node.hasProp("size"):
						a = (node.prop("size").split(","))
						size = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
						o = Engine.createSpaceCage(size)
						loadGuiContainer(node,Engine,EngineModule,o,uuidTable)
						if node.hasProp("uuid"):
							uuid = node.prop("uuid")
							uuid = getFromUuidTable(Engine,uuidTable,uuid)
							o.setUuid(uuid)
						loadEngineObject(node,Engine,EngineModule,o)
					res.remove(node)
				else:
					lastUnresolved = "spacecage: gui container failed"

			elif node.name=="CAMERA":
				if node.hasProp("position"):
					a = (node.prop("position").split(","))
					pos = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
					Engine.setCameraPosition(pos)
				if node.hasProp("orientation"):
					a = (node.prop("orientation").split(","))
					orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
					Engine.setCameraOrientation(orientation)
				res.remove(node)

			elif node.name=="OBJECTS":
				if node.hasProp("name"):
					name = node.prop("name")
					if node.hasProp("content"):
						contentString = node.prop("content")
						contentList = contentString.split(":",1)
						contentType = contentList[0]
						contentValue = contentList[1]
						content = translateType(Engine,EngineModule,contentType,contentValue,uuidTable)
						#print("name: " + name)
						#print("content: " + str(content))
						if content:
							objects.append(name,content)
						else:
							pass
							#print("not found")
						res.remove(node)
				else:
					res.remove(node)


def translateType(Engine,EngineModule,typeString,valueString,uuidTable):
	if typeString == "str":
		return str(valueString)
	elif typeString == "int":
		return int(valueString)
	elif typeString == "float":
		return float(valueString)
	elif typeString == "engineobject":
		objectUuid = getFromUuidTable(Engine,uuidTable,valueString)
		if Engine.getFromUuid(objectUuid):
			return Engine.getFromUuid(objectUuid)
		else:
			objectsNumber = Engine.howManyObjects()
			for i in range(0,objectsNumber):
				o = Engine.getObject(i)
			return None

	elif typeString == "list":
		content = []
		stringArray = (valueString
			.replace("[","")
			.replace("]","")
			.replace("'","")
			.replace(" ","")
			.split(","))
		if (len(stringArray)==1 and stringArray[0]==''):
			stringArray = []
		for e in stringArray:
			contentList = e.split(":",1)
			contentType = contentList[0]
			contentValue = contentList[1]
			element = translateType(Engine,EngineModule,contentType,contentValue,uuidTable)
			if not element:
				content = None
				break
			content.append(element)
		return content

def save(Engine,EngineModule,fileName,objects):
	doc = libxml2.newDoc("1.0")
	rootNode = libxml2.newNode("scene")
	doc.addChild(rootNode)
	objectsNumber = Engine.howManyObjects()
	for i in range(0,objectsNumber):
		o = Engine.getObject(i)
		node = libxml2.newNode(str(o.getType()))
		node.setProp("uuid",str(o.readUuid()))
		node.setProp("name",str(o.getName()))
		node.setProp("selectable",str(o.isSelectable()))

		if o.getType()==EngineModule.ObjectType.GUISHAPE:
			pass

		elif o.getType()==EngineModule.ObjectType.GUICONTAINER:
			pass

		elif o.getType()==EngineModule.ObjectType.MESH:
			node.setProp("mesh_file",str(o.getFileName()))
			bonesNumber = o.getNumberOfBones()
			bonesList = []
			for i in range(0,bonesNumber):
				body = o.getBodyByIndex(i)
				joint = o.getJointByIndex(i)
				boneName = o.getBoneNameByIndex(i)
				bodyUuid = 0
				jointUuid = 0
				if body and body != 0:
					bodyUuid = body.readUuid()
				if joint and joint != 0:
					jointUuid = joint.readUuid()
				bonesList.append( (boneName,bodyUuid,jointUuid) )
			node.setProp("bones",str(bonesList))
			node.setProp("position",str(o.getPosition()))
			node.setProp("size",str(o.getSize()))
			node.setProp("orientation",str(o.getOrientation()))
			if o.hasColour():
				node.setProp("colour",str(o.getColour()))
				node.setProp("alpha",str(o.getAlpha()))
			#else:
			if o.getMaterialName() != "":
				node.setProp("material",str(o.getMaterialName()))

			node.setProp("final_shape",str(o.isFinalShape()))

		elif o.getType()==EngineModule.ObjectType.STATICBODY:
			saveGuiContainer(node,Engine,EngineModule,o)
			node.setProp("position",str(o.getPosition()))
			node.setProp("size",str(o.getSize()))
			node.setProp("orientation",str(o.getOrientation()))

		elif o.getType()==EngineModule.ObjectType.BODY:
			saveGuiContainer(node,Engine,EngineModule,o)
			node.setProp("position",str(o.getPosition()))
			node.setProp("size",str(o.getSize()))
			node.setProp("orientation",str(o.getOrientation()))

		elif o.getType()==EngineModule.ObjectType.BOX:
			node.setProp("position",str(o.getPosition()))
			node.setProp("size",str(o.getSize()))
			node.setProp("orientation",str(o.getOrientation()))
			node.setProp("local_position",str(o.getLocalPosition()))
			node.setProp("local_size",str(o.getLocalSize()))
			node.setProp("local_orientation",str(o.getLocalOrientation()))

			scalingType = "1To1"
			if o.isScalingFixed():
				scalingType = "Fixed"
			elif o.isScalingNone():
				scalingType = "None"
			elif o.isScaling1To1():
				scalingType = "1To1"
			elif o.isScalingScaling():
				scalingType = "Scaling"
			node.setProp("scaling",str(scalingType))

			node.setProp("final_shape",str(o.isFinalShape()))
			node.setProp("cast_shadows",str(o.getCastShadows()))

			if o.hasColour():
				node.setProp("colour",str(o.getColour()))
				node.setProp("alpha",str(o.getAlpha()))

			if not o.getMaterialName() == "":
				node.setProp("material",str(o.getMaterialName()))
				
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
			node.setProp("motor_target",str(o.getMotorTarget()))
			node.setProp("motor_on",str(o.isMotorOn()))

		elif o.getType()==EngineModule.ObjectType.SPACECAGE:
			saveGuiContainer(node,Engine,EngineModule,o)
			node.setProp("size",str(o.getSize()))

		doc.getRootElement().addChild(node)

	node = libxml2.newNode("CAMERA")
	node.setProp("position",str(Engine.getCameraPosition()))
	node.setProp("orientation",str(Engine.getCameraOrientation()))
	doc.getRootElement().addChild(node)

	for k,v in objects.get().items():
		if objects.isSavable(k):
			node = libxml2.newNode("OBJECTS")
			node.setProp("name",str(k))
			node.setProp("content",str(typeToString(Engine,EngineModule,v)))
			doc.getRootElement().addChild(node)

	doc.saveFormatFile(fileName,1)

def typeToString(Engine,EngineModule,value):
	if type(value) == list:
		stringList = []
		for e in value:
			stringList.append( typeToString(Engine,EngineModule,e))
		return "list:" + str(stringList)
	elif type(value) == str:
		return "str:"+str(value)
	elif type(value) == int:
		return "int:"+str(value)
	elif type(value) == float:
		return "float:"+str(value)
	if issubclass(value.__class__,EngineModule.EngineObject):
		return "engineobject:" + str(value.readUuid())

def loadStringArray(node,attributeName):
	if node.hasProp(attributeName):
		stringArray = (node.prop(attributeName)
			.replace("[","")
			.replace("]","")
			.replace("'","")
			.replace(" ","")
			.split(","))
		if (len(stringArray)==1 and stringArray[0]==''):
			stringArray = []
		return [ num for num in stringArray ]
	else:
		return []

def loadTupleArray(node,attributeName):
	finalArray = []
	tupleArray = (node.prop(attributeName)
		.replace("),",")#")
		.replace("[","")
		.replace("]","")
		.replace("'","")
		.replace(" ","")
		.split("#"))
	for t in tupleArray:
		elementArray = (t
			.replace("(","")
			.replace(")","")
			.split(","))
		finalArray.append( elementArray )
	return finalArray

def isGuiContainerFullfilled(node,Engine,EngineModule,uuidTable):
	shapes = loadStringArray(node,"shapes")
	allShapesExist = True
	for shape in shapes:
		shape = getFromUuidTable(Engine,uuidTable,shape)
		if not Engine.getFromUuid(shape):
			allShapesExist = False
			break
	return allShapesExist

def loadGuiContainer(node,Engine,EngineModule,engineObject,uuidTable):
	shapes = loadStringArray(node,"shapes")
	for shape in shapes:
		shape = getFromUuidTable(Engine,uuidTable,shape)
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
	if node.hasProp("size"):
		a = (node.prop("size").split(","))
		size = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
		engineObject.setSize(size)

def loadPosition(node,Engine,EngineModule,engineObject):
	if node.hasProp("position"):
		a = (node.prop("position").split(","))
		pos = EngineModule.Vec3( float(a[0]),float(a[1]),float(a[2]))
		engineObject.setPosition(pos)

def loadOrientation(node,Engine,EngineModule,engineObject):
	if node.hasProp("orientation"):
		a = (node.prop("orientation").split(","))
		orientation = EngineModule.Quat( float(a[0]),float(a[1]),float(a[2]),float(a[3]))
		engineObject.setOrientation(orientation)

def loadEngineObject(node,Engine,EngineModule,engineObject):
	#if node.hasProp("uuid"):
	#	uuid = node.prop("uuid")
	#	engineObject.setUuid(uuid)
	if node.hasProp("name"):
		name = node.prop("name")
		engineObject.setName(name)
	if node.hasProp("selectable"):
		selectable = loadBool(node,"selectable")
		if selectable:
			engineObject.setSelectable()
		else:
			engineObject.setUnselectable()

def loadBool(node,attributeName):
	if node.hasProp(attributeName):
		return node.prop(attributeName).lower() in ["true","yes","1"]
	return False

