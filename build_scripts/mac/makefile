
BUILDPATH=../../build
BUILDTEMPPATH=../../build/mac
MAINCODEDIR=../../code_cpp
MAINEXECUTABLEDIR=../../executable
EXECUTABLEDIR=../../executable/mac

VPATH=$(MAINCODEDIR)/common:$(MAINCODEDIR)/engine:$(MAINCODEDIR)/engine_objects:$(MAINCODEDIR)/final
ALLPATHES=$(subst :, ,$(VPATH))

OBJ=$(BUILDTEMPPATH)/main.o
OBJ+=$(foreach dir,$(ALLPATHES), $(patsubst $(dir)/%.cpp,$(BUILDTEMPPATH)/%.o,$(wildcard $(dir)/*.cpp)) )

LINKER=g++

CFLAGS=
CFLAGS+=-I /usr/include/python2.7

CFLAGS+=-I /Users/sinan/etc/PhysX-3.2.2_OSX_SDK_Core/Include/
CFLAGS+=-I /Users/sinan/etc/PhysX-3.2.2_OSX_SDK_Core/Include/extensions/
CFLAGS+=-I /Users/sinan/etc/PhysX-3.2.2_OSX_SDK_Core/Include/foundation/

CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/OSX/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/RenderSystems/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/RenderSystems/GL/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/RTShaderSystem/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/Plugins/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/Plugins/BSPSceneManager/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/Plugins/OctreeSceneManager/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/Plugins/PCZSceneManager/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OGRE/Plugins/ParticleFX/
CFLAGS+=-I /Users/sinan/etc/OgreSDK/include/OIS/

#CFLAGS+=-I /c/Users/Sinan/Downloads/ogre/OgreProceduralSDK_vs10_v0.2/include/OgreProcedural/

CFLAGS+=$(foreach dir,$(ALLPATHES),"-I" $(dir))

#CFLAGS+=`pkg-config --libs --cflags OGRE OIS`
CFLAGS+=-pthread

CFLAGS+=-c
CFLAGS+=-D"NDEBUG"
CFLAGS+=-D"MACOSX"

CC=g++

LIBLIST=
LIBLIST+=-L/Users/sinan/etc/PhysX-3.2.2_OSX_SDK_Core/Lib/osx64
LIBLIST+=-L/Users/sinan/etc/OgreSDK/lib
LIBLIST+=-L/Users/sinan/etc/OgreSDK/lib/release

LIBLIST+=-lpython2.7
LIBLIST+=-lboost_python-mt

LIBLIST+=-lOgrePaging
LIBLIST+=-lOgreProperty
LIBLIST+=-lOgreRTShaderSystem
LIBLIST+=/Users/sinan/etc/OgreSDK/lib/release/Ogre.framework/Ogre
LIBLIST+=-lOIS
LIBLIST+=-lpthread

#LIBLIST+=-lLowLevel
#LIBLIST+=-lLowLevelCloth
#LIBLIST+=-lPhysX3
#LIBLIST+=-lPhysX3Common
#LIBLIST+=-lPhysX3Cooking
#LIBLIST+=-lPhysX3Extensions
#LIBLIST+=-lPvdRuntime
#LIBLIST+=-lPxTask
#LIBLIST+=-lRepX3
#LIBLIST+=-lRepXUpgrader3
#LIBLIST+=-lSceneQuery
#LIBLIST+=-lSimulationController
#LIBLIST+=-lPhysXProfileSDK

LIBLIST+=-lLowLevel
LIBLIST+=-lLowLevelCloth
LIBLIST+=-lPhysX3
LIBLIST+=-lPhysX3CharacterKinematic
LIBLIST+=-lPhysX3Common
LIBLIST+=-lPhysX3Cooking
LIBLIST+=-lPhysX3Extensions
LIBLIST+=-lPhysX3Vehicle
LIBLIST+=-lPhysXProfileSDK
LIBLIST+=-lPhysXVisualDebuggerSDK
LIBLIST+=-lPvdRuntime
LIBLIST+=-lPxTask
LIBLIST+=-lRepX3
LIBLIST+=-lRepXUpgrader3
LIBLIST+=-lSceneQuery
LIBLIST+=-lSimulationController



LIBLIST+=-framework Cocoa
LIBLIST+=-framework IOKit

LIBLIST+=-framework OpenGL
LIBLIST+=-framework AGL


#LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OIS.lib
#LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreProceduralSDK_vs10_v0.2/lib/Release/OgreProcedural.lib
#LIBLIST+=/c/boost_1_47/lib/libboost_thread-vc100-mt-1_47.lib
#LIBLIST+=/c/boost_1_47/lib/libboost_date_time-vc100-mt-1_47.lib

LIBFLAGS=

.PHONY: clean 

show:
	@ echo "cflags: $(CFLAGS)"
	@ echo "vpath: $(VPATH)"
	@ echo "allpathes: $(ALLPATHES)"
	@ echo "obj: $(OBJ)"

all: $(EXECUTABLEDIR)/main

run: all
	@ echo "execute"
	@ cd $(EXECUTABLEDIR) && ./main

$(EXECUTABLEDIR)/main: $(BUILDTEMPPATH)/main.o $(OBJ) | $(EXECUTABLEDIR)
	@ echo "link: $<"
	@ $(LINKER) $(LIBFLAGS) $(LIBLIST) -o $@ $(OBJ)

$(BUILDTEMPPATH)/main.o: $(MAINCODEDIR)/main.cpp | $(BUILDTEMPPATH)
	@ echo "compile: $<"
	@ $(CC) $(CFLAGS) -o $@ $<

$(BUILDTEMPPATH)/%.o: %.cpp %.h
	@ echo "compile: $<"
	@ $(CC) $(CFLAGS) -o $@ $<

$(BUILDTEMPPATH)/%.o: %.cpp
	@ echo "compile: $<"
	@ $(CC) $(CFLAGS) -o $@ $<

$(EXECUTABLEDIR):
	@ mkdir -p $(EXECUTABLEDIR)
	@ # ln -s ../../py_scripts/ $(EXECUTABLEDIR)/py_scripts

$(BUILDTEMPPATH):
	@ mkdir -p $(BUILDTEMPPATH)

clean:
	@ rm -rf $(BUILDTEMPPATH)
	@ rm -rf $(EXECUTABLEDIR)


