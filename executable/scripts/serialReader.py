import serial

def init(Engine,EngineModule,objects):
	objects.get()["serial"] = None
	objects.setUnsavable("serial")

	objects.get()["serial_state"] = "0"
	objects.setUnsavable("serial_state")

	s = serial.Serial("COM3",9600)
	objects.get()["serial"] = s

def guiUpdate(Engine,EngineModule,selection,objects):
	s = objects.get()["serial"]
	serial_state  = objects.get()["serial_state"]
	old_state = serial_state

	serial_state = None
	if s.inWaiting() > 0:
		serialData = s.read(size=int(s.inWaiting())-1)
		serial_state = s.read(size=1)

		if serial_state != old_state:
			objects.get()["serial_state"] = serial_state
			print("state: " + str(serial_state))
			Engine.callPythonKeyPressed(EngineModule.Keys.K_SPACE)

