#!/bin/bash

PATH="$PATH:/c/Procs/MicrosoftVisualStudio10.0/VC/bin"
PATH="$PATH:/c/Procs/MicrosoftVisualStudio10.0/Common7/IDE"

LINKEXE=/c/Procs/MicrosoftVisualStudio10.0/VC/bin/link.exe

#cl \
#-I /c/Procs/MicrosoftVisualStudio10.0/VC/include \
#-I /c/Procs/MicrosoftSDKs/Windows/v7.0A/Include \
#-I /c/Procs/MicrosoftPlatformSDK/Include \
#-I /c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/ \
#-I /c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/OGRE/ \
#-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PhysXAPI \
#-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PhysXAPI/extensions \
#-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PxFoundation \
#-I /c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PxTask/include \
#-I /c/Python27/include \
#-I /c/boost_1_47/ \
#-I ./common \
#-I ./engine_graphics \
#-I ./engine_physics \
#-I ./engine \
#-c -MD -EHsc -D "NDEBUG" -nologo \
#-Fobuild/main2.obj \
#main.cpp

$LINKEXE \
-NOLOGO \
-NODEFAULTLIB:LIBCMT \
-OUT:release/main2.exe \
build/*.obj \
/c/Python27/libs/python27.lib \
/c/Procs/MicrosoftVisualStudio10.0/VC/lib/msvcprt.lib \
/c/Procs/MicrosoftVisualStudio10.0/VC/lib/msvcrt.lib \
/c/Procs/MicrosoftVisualStudio10.0/VC/lib/oldnames.lib \
/c/Procs/MicrosoftVisualStudio10.0/VC/lib/libcpmt.lib \
/c/Procs/MicrosoftSDKs/Windows/v7.0A/Lib/Kernel32.Lib \
/c/Procs/MicrosoftSDKs/Windows/v7.0A/Lib/Uuid.Lib \
/c/boost_1_47/lib/libboost_thread-vc100-mt-1_47.lib \
/c/boost_1_47/lib/libboost_date_time-vc100-mt-1_47.lib \
/c/boost_1_47/lib/boost_python-vc100-mt-1_47.lib \
/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PhysX3_x86.lib \
/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PhysX3Common.lib \
/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PhysX3Extensions.lib \
/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/Foundation.lib \
/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/lib/win32/PxTask.lib \
/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OgreMain.lib \
/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/lib/release/OIS.lib

