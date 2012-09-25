import serial

def init(Engine,EngineModule,objects):
	try:
		s = serial.Serial("COM4",9600)
		objects.get()["serial"] = s
		objects.setUnsavable("serial")

		objects.get()["serial_state"] = "0"
		objects.setUnsavable("serial_state")
		Engine.log("found serial port (4) device")

	except serial.SerialException,e: 
		Engine.log("serial exception: " + str(e))

def guiUpdate(Engine,EngineModule,selection,objects):
	if "serial" in objects.get():
		s = objects.get()["serial"]
		serial_state  = objects.get()["serial_state"]
		old_state = serial_state

		serial_state = None
		if s.inWaiting() > 0:
			serialData = s.read(size=int(s.inWaiting())-1)
			serial_state = s.read(size=1)

			if serial_state != old_state:
				if serial_state == "1":
					objects.get()["serial_state"] = serial_state
					Engine.log("state: " + str(serial_state))
					Engine.callPythonKeyPressed(EngineModule.Keys.K_SPACE)
				if serial_state == "0":
					objects.get()["serial_state"] = serial_state
					Engine.log("state: " + str(serial_state))
					Engine.callPythonKeyReleased(EngineModule.Keys.K_SPACE)

