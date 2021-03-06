#include "logger.h"
#include "engine_py.h"
#include "engine.h"
#include <boost/python/list.hpp>



void	Engine::closePython() {
	Logger::debug("close python");
	Py_Finalize();
	mPythonInitialized = false;
}

void	Engine::setupPython() {
	Logger::debug("setup python");
	Py_Initialize();
	//Logger::debug(format("Py_GetPath (before set): %p\n") % Py_GetPath());
	//PySys_SetPath("../");
	//Logger::debug(format("Py_GetPath (after set): %p\n") % Py_GetPath());

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
		Logger::debug("run main.py");
        PyObject* file = PyFile_FromString("../main.py", "r+");
        PyRun_File(PyFile_AsFile(file), "main.py", Py_file_input, 
			main_namespace.ptr(), main_namespace.ptr()
			);
		//PyRun_SimpleString("print(globals())");

		Logger::debug("load keyPressed");
		pyFunctionKeyPressed = main_namespace["keyPressed"];
		Logger::debug("load keyDown");
		pyFunctionKeyDown = main_namespace["keyDown"];
		Logger::debug("load keyReleased");
		pyFunctionKeyReleased = main_namespace["keyReleased"];
		Logger::debug("load init");
		pyFunctionInit = main_namespace["init"];
		Logger::debug("load guiUpdate");
		pyFunctionGuiUpdate = main_namespace["guiUpdate"];
		Logger::debug("load physicUpdate");
		pyFunctionPhysicUpdate = main_namespace["physicUpdate"];

		Logger::debug("run init");
		pyFunctionInit();

    } catch( error_already_set ) {
		mPythonInitialized = false;
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

