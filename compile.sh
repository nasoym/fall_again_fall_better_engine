#!/bin/bash

#PATH=$PATH:/c/Procs/MicrosoftVisualStudio10.0/VC/bin
#PATH=$PATH:/c/Procs/MicrosoftVisualStudio10.0/Common7/IDE

PATH="$PATH:/c/Procs/MicrosoftVisualStudio10.0/VC/bin"
PATH="$PATH:/c/Procs/MicrosoftVisualStudio10.0/Common7/IDE"

LINKEXE=/c/Procs/MicrosoftVisualStudio10.0/VC/bin/link.exe


include="" 
include="$include:/c/Procs/MicrosoftVisualStudio10.0/VC/include"
include="$include:/c/Procs/MicrosoftSDKs/Windows/v7.0A/Include"
include="$include:/c/Procs/MicrosoftPlatformSDK/Include"
include="$include:/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/"
include="$include:/c/Users/Sinan/Downloads/ogre/OgreSDK_vc10_v1-8-0/include/OGRE/"
include="$include:/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PhysXAPI"
include="$include:/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PhysXAPI/extensions"
include="$include:/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PxFoundation"
include="$include:/c/Users/Sinan/Downloads/physx/PhysX-3.1.2_PC_VC10_SDK_Core/SDKs/PxTask/include"
include="$include:/c/Python27/include"
include="$include:/c/boost_1_47/"
include="$include:common"
include="$include:engine_graphics"
include="$include:engine_physics"
include="$include:engine"


cl \
-c -MD -EHsc -D "NDEBUG" -nologo \
main.cpp

