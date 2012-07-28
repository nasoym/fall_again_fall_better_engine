#include "logger.h"
#include "engine.h"
#include "engine.py.h"

void	Engine::closePython() {
	Logger::debug("close python");
	Py_Finalize();
	mPythonInitialized = false;
}

void	Engine::setupPython() {
	Logger::debug("setup python");
	Py_Initialize();
	//printf("Py_GetPath: %s\n",Py_GetPath());
	object main_module(( handle<>(borrowed(PyImport_AddModule("__main__"))) ));
	main_namespace = main_module.attr("__dict__");
	PyImport_AppendInittab("EngineModule", &initEngineModule ); 
	object engineModule(( handle<>(borrowed(PyImport_ImportModule("EngineModule"))) ));
	main_namespace["EngineModule"] = engineModule;
	main_namespace["Engine"] = ptr(this);

	mPythonInitialized = true;
}

void    Engine::runPython(){
	if (!mPythonInitialized) {
		setupPython();
	}
	Logger::debug("run python file");
	try {
        PyObject* file = PyFile_FromString("script.py", "r+");
        PyRun_File(PyFile_AsFile(file), "script.py", Py_file_input, 
			main_namespace.ptr(), main_namespace.ptr()
			);

		pyFunctionKeyPressed = main_namespace["keyPressed"];
		pyFunctionKeyDown = main_namespace["keyDown"];
		pyFunctionKeyReleased = main_namespace["keyReleased"];
		pyFunctionInit = main_namespace["init"];
		pyFunctionGuiUpdate = main_namespace["guiUpdate"];
		pyFunctionPhysicUpdate = main_namespace["physicUpdate"];

		pyFunctionInit();

    } catch( error_already_set ) {
		Logger::debug("python error");
        PyErr_Print();
    }
}

void	Engine::callPythonKeyPressed(Keys key) {
	if (mPythonInitialized) {
		try {
			pyFunctionKeyPressed(key);
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

void	Engine::callPythonKeyDown(Keys keyDown) {
	if (mPythonInitialized) {
		try {
			pyFunctionKeyDown(keyDown);
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

void	Engine::callPythonKeyReleased(Keys key) {
	if (mPythonInitialized) {
		try {
			pyFunctionKeyReleased(key);
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

void	Engine::callPythonKeyGuiUpdate() {
	if (mPythonInitialized) {
		try {
			pyFunctionGuiUpdate();
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

void	Engine::callPythonKeyPysicUpdate() {
	if (mPythonInitialized) {
		try {
			pyFunctionPhysicUpdate();
		} catch( error_already_set ) {
			Logger::debug("Python error");
			PyErr_Print();
		}
	}
}

