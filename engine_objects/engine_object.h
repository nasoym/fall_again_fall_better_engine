#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "stdio.h"
#include <string>
#include "uuid.h"

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/call_method.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/copy_const_reference.hpp>

#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>

#include "logger.h"

using namespace boost::python;

class Engine;

class GuiShape;
class GuiContainer;
class MeshObject;
class GuiCube;
class Actor;
class PhysicShape;
class DynamicActor;
class Articulation;
class StaticActor;
class Joint;

enum ObjectType {
	OBJECT,
	GUICONTAINER,
	GUISHAPE,
    MESH,
	JOINT,
	BOX,
	ACTOR,
	DYNAMIC_ACTOR,
	PHYSIC_SHAPE,
	ARTICULATION,
	STATIC_ACTOR,
};

class EngineObject {
    public:
        EngineObject(Engine* engine);
        virtual ~EngineObject();

		std::string 	getName(){return mName;}
		void 			setName(std::string name){mName = name;}
		//void 			setName(char * chr_ptr){mName = std::string(chr_ptr);}

		std::string		readUuid(){ return mUuid.toString(); }
		void			setUuid(std::string name){mUuid.fromString(name);}
		Uuid			getUuid(){ return mUuid; }

		Engine*			getEngine(){ return mEngine; }

		virtual ObjectType		getType(){ return OBJECT;}


		virtual GuiShape*			isGuiShape(){return 0;}
		virtual GuiContainer*		isGuiContainer(){return 0;}
		virtual MeshObject*				isMesh(){return 0;}
		virtual GuiCube*				isBox(){return 0;}
		virtual Actor*					isActor(){return 0;}
		virtual DynamicActor*			isDynamicActor(){return 0;}
		virtual PhysicShape*			isPhysicShape(){return 0;}
		virtual Articulation*			isArticulation(){return 0;}
		virtual StaticActor*			isStaticActor(){return 0;}
		virtual Joint*					isJoint(){return 0;}

		void			setSelectable(){mSelectable=true;}
		void			setUnselectable(){mSelectable=false;}
		bool			isSelectable(){return mSelectable;}

		void		setPythonDictionary(object dictionary){
			mPythonDictionary = dictionary;
		}

		void		setPythonScriptObjects(object scriptObjects){
			mPythonScriptObjects = scriptObjects;
		}

		PyObject*		getPythonDictionary(){
			return incref(mPythonDictionary.ptr());
		}

		PyObject*		getPythonScriptObjects(){
			return incref(mPythonScriptObjects.ptr());
		}

		void	pythonScriptObjectsCallMethod(std::string methodName) {
			if (!mPythonScriptObjects.is_none()){
				//Logger::debug("pyscript: is not none");
				boost::python::list scriptList = extract<boost::python::list>(mPythonScriptObjects);
				//if (!scriptList.is_none()){
					//Logger::debug("pyscript: is a list");
					object scriptObject;
					for (int i = 0; i < len(scriptList); ++i) {
						scriptObject = extract<object>(scriptList[i]);

						// method = "physicUpdate"
						//if (PyObject_HasAttrString(scriptObject.ptr(),methodName.c_str()) ) {
							//Logger::debug("pyscript: object has method");
							scriptObject.attr(methodName.c_str())(boost::ref(this));
						//}
					}
				//}
			}
		}

		virtual void	guiUpdate(){
			pythonScriptObjectsCallMethod("guiUpdate");
		}

		virtual void	physicUpdate(){
			pythonScriptObjectsCallMethod("physicUpdate");
		}

	private:
		Engine*		mEngine;
		std::string	mName;
		Uuid		mUuid;
		bool		mSelectable;

		object		mPythonDictionary;
		object		mPythonScriptObjects;
};
#endif
