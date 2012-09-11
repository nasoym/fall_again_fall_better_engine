
VPATH=common:engine:final:engine_physics:stereoManager
ALLPATHES=$(subst :, ,$(VPATH))

OBJ=build/main.obj
OBJ+=$(foreach dir,$(ALLPATHES), $(patsubst $(dir)/%.cpp,build/%.obj,$(wildcard $(dir)/*.cpp)) )

LINK=/c/Procs/MicrosoftVisualStudio10.0/VC/bin/link.exe


CFLAGS=
CFLAGS+=-I /c/Procs/MicrosoftVisualStudio10.0/VC/include
CFLAGS+=-I /c/Procs/MicrosoftSDKs/Windows/v7.0A/Include
CFLAGS+=-I /c/Procs/MicrosoftPlatformSDK/Include
CFLAGS+=-I /c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/
CFLAGS+=-I /c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/OGRE/
CFLAGS+=-I /c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/OGRE/RTShaderSystem
CFLAGS+=-I /c/Users/Sinan/Downloads/ogre/OgreProceduralSDK_vs10_v0.2/include/OgreProcedural/

CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/include/
CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/include/extensions/
CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/include/pxtask/
CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/include/foundation/

CFLAGS+=-I /c/Python27/include
CFLAGS+=-I /c/boost_1_47/
CFLAGS+=$(foreach dir,$(ALLPATHES),"-I" $(dir))
CFLAGS+=-c -MD -EHsc -D "NDEBUG" -nologo

CC=cl.exe

LIBLIST=
LIBLIST+=/c/Python27/libs/python27.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/msvcprt.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/msvcrt.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/oldnames.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/libcpmt.lib
LIBLIST+=/c/Procs/MicrosoftSDKs/Windows/v7.0A/Lib/Kernel32.Lib
LIBLIST+=/c/Procs/MicrosoftSDKs/Windows/v7.0A/Lib/Psapi.Lib
LIBLIST+=/c/Procs/MicrosoftSDKs/Windows/v7.0A/Lib/Uuid.Lib
LIBLIST+=/c/boost_1_47/lib/libboost_thread-vc100-mt-1_47.lib
LIBLIST+=/c/boost_1_47/lib/libboost_date_time-vc100-mt-1_47.lib
LIBLIST+=/c/boost_1_47/lib/boost_python-vc100-mt-1_47.lib

LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/Lib/win32/PhysX3_x86.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/Lib/win32/PhysX3Common_x86.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/Lib/win32/PhysX3Extensions.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.2_PC_SDK_Core/Lib/win32/PxTask.lib

LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OgreMain.lib
LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OgreRTShaderSystem.lib
LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OIS.lib
LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreProceduralSDK_vs10_v0.2/lib/Release/OgreProcedural.lib

LIBFLAGS=
LIBFLAGS+=-NOLOGO
LIBFLAGS+=-NODEFAULTLIB:LIBCMT

.PHONY: clean test

show:
	echo $(CFLAGS)

dll:
	$(LINK) $(LIBFLAGS) -DLL -OUT:executable/EngineModule.pyd $(OBJ) $(LIBLIST)

all: executable/main.exe
	echo "main"

test: 
	$(CC) $(CFLAGS) -Fobuild/test.obj test.cpp 
	$(LINK) $(LIBFLAGS) -OUT:test.exe build/test.obj $(LIBLIST)

executable/main.exe: $(OBJ)
	echo "linking to:$@"
	$(LINK) $(LIBFLAGS) -OUT:$@ $(OBJ) $(LIBLIST)

build/%.obj: %.cpp %.h
	$(CC) $(CFLAGS) -Fo$@ $<

build/%.obj: %.cpp
	$(CC) $(CFLAGS) -Fo$@ $<

build/main.obj: main.cpp
	$(CC) $(CFLAGS) -Fo$@ $<



run: all
	(cd executable ; ./main.exe)

clean:
	rm build/*.obj
	rm executable/main.exe

