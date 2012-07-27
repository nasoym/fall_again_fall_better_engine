import temp

print("main.py:hello")

print("Engine: " + str(Engine))
print("EngineModule: " + str(EngineModule))

print(globals())


objects = {}


def init():
	print("init")

def keyPressed(key):
	if key ==  EngineModule.Keys.K_A:
		print("a pressed")
	if key ==  EngineModule.Keys.K_Q:
		print("q pressed")
		Engine.quit()
	if key ==  EngineModule.Keys.K_1:
		objects["gui1"] = Engine.createGuiBox()
	if key ==  EngineModule.Keys.K_T:
		print("t pressed")
		reload(temp)
		temp.launch(Engine,objects,EngineModule)

def keyReleased(key):
	if key ==  EngineModule.Keys.K_A:
		print("a released")
	pass

def guiUpdate():
	#print("g")
	pass

def physicUpdate():
	#print("p")
	pass

