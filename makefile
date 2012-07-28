
LINK=/c/Procs/MicrosoftVisualStudio10.0/VC/bin/link.exe

CFLAGS=
CFLAGS+=-I /c/Procs/MicrosoftVisualStudio10.0/VC/include
CFLAGS+=-I /c/Procs/MicrosoftSDKs/Windows/v7.0A/Include
CFLAGS+=-I /c/Procs/MicrosoftPlatformSDK/Include
CFLAGS+=-I /c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/
CFLAGS+=-I /c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/OGRE/
CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PhysXAPI
CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PhysXAPI/extensions
CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PxFoundation
CFLAGS+=-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PxTask/include
CFLAGS+=-I /c/Python27/include
CFLAGS+=-I /c/boost_1_47/
CFLAGS+=-I ./common
CFLAGS+=-I ./engine_graphics
CFLAGS+=-I ./engine_physics
CFLAGS+=-I ./engine
CFLAGS+=-c -MD -EHsc -D "NDEBUG" -nologo

CC=cl.exe

LIBLIST=
LIBLIST+=/c/Python27/libs/python27.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/msvcprt.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/msvcrt.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/oldnames.lib
LIBLIST+=/c/Procs/MicrosoftVisualStudio10.0/VC/lib/libcpmt.lib
LIBLIST+=/c/Procs/MicrosoftSDKs/Windows/v7.0A/Lib/Kernel32.Lib
LIBLIST+=/c/Procs/MicrosoftSDKs/Windows/v7.0A/Lib/Uuid.Lib
LIBLIST+=/c/boost_1_47/lib/libboost_thread-vc100-mt-1_47.lib
LIBLIST+=/c/boost_1_47/lib/libboost_date_time-vc100-mt-1_47.lib
LIBLIST+=/c/boost_1_47/lib/boost_python-vc100-mt-1_47.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PhysX3_x86.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PhysX3Common.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PhysX3Extensions.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/Foundation.lib
LIBLIST+=/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PxTask.lib
LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OgreMain.lib
LIBLIST+=/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OIS.lib

LIBFLAGS=
LIBFLAGS+=-NOLOGO
LIBFLAGS+=-NODEFAULTLIB:LIBCMT

VPATH=engine_physics:engine_graphics:common:engine
ALLPATHES=$(subst :, ,$(VPATH))

OBJ=build/main.obj
OBJ+=$(foreach dir,$(ALLPATHES), $(patsubst $(dir)/%.cpp,build/%.obj,$(wildcard $(dir)/*.cpp)) )

dll:
	$(LINK) $(LIBFLAGS) -DLL -OUT:release/EngineModule.pyd $(OBJ) $(LIBLIST)
show:
	echo $(OBJ)

all: release/main.exe
	echo "main"

release/main.exe: $(OBJ)
	echo "linking to:$@"
	$(LINK) $(LIBFLAGS) -OUT:$@ $(OBJ) $(LIBLIST)

build/%.obj: %.cpp %.h
	$(CC) $(CFLAGS) -Fo$@ $<

build/%.obj: %.cpp
	$(CC) $(CFLAGS) -Fo$@ $<

build/main.obj: main.cpp
	$(CC) $(CFLAGS) -Fo$@ $<

.PHONY: clean

run: all
	(cd release ; ./main.exe)

clean:
	rm build/*.obj
	rm release/main.exe

