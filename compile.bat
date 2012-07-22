cls
@echo off

set include= 
set include=%include%;C:\Procs\MicrosoftVisualStudio10.0\VC\include
set include=%include%;C:\Procs\MicrosoftSDKs\Windows\v7.0A\Include
set include=%include%;C:\Procs\MicrosoftPlatformSDK\Include

set include=%include%;C:\Users\Sinan\Downloads\ogre\OgreSDK_vc10_v1-8-0\include\OGRE\

set include=%include%;C:\Users\Sinan\Downloads\physx\PhysX-3.1.2_PC_VC10_SDK_Core\SDKs\PhysXAPI
set include=%include%;C:\Users\Sinan\Downloads\physx\PhysX-3.1.2_PC_VC10_SDK_Core\SDKs\PhysXAPI\extensions
set include=%include%;C:\Users\Sinan\Downloads\physx\PhysX-3.1.2_PC_VC10_SDK_Core\SDKs\PxFoundation
set include=%include%;C:\Users\Sinan\Downloads\physx\PhysX-3.1.2_PC_VC10_SDK_Core\SDKs\PxTask\include

set include=%include%;C:\Python27\include
set include=%include%;C:\boost_1_47\
set include=%include%;common
set include=%include%;engine_graphics
set include=%include%;engine_physics

set lib=
set lib=%lib%;C:\Procs\MicrosoftVisualStudio10.0\VC\lib
set lib=%lib%;C:\Procs\MicrosoftSDKs\Windows\v7.0A\Lib
set lib=%lib%;C:\Procs\MicrosoftPlatformSDK\Lib

set lib=%lib%;C:\Users\Sinan\Downloads\ogre\OgreSDK_vc10_v1-8-0\lib\release\

set lib=%lib%;C:\Users\Sinan\Downloads\physx\PhysX-3.1.2_PC_VC10_SDK_Core\SDKs\lib\win32

set lib=%lib%;C:\Python27\libs
set lib=%lib%;C:\boost_1_47\lib

set cl_setting=
set cl_setting=%cl_setting% /c
set cl_setting=%cl_setting% /MD
set cl_setting=%cl_setting% /EHsc
set cl_setting=%cl_setting% /D "NDEBUG"
set cl_setting=%cl_setting% /nologo

set lib_list=
set lib_list=%lib_list% OgreMain.lib

set lib_list=%lib_list% PhysX3_x86.lib
set lib_list=%lib_list% PhysX3Common.lib
set lib_list=%lib_list% PhysX3Extensions.lib
set lib_list=%lib_list% Foundation.lib
set lib_list=%lib_list% PxTask.lib

echo -------- compiling
cl.exe %cl_setting% /Fobuild\logger.obj common\logger.cpp

cl.exe %cl_setting% /Fobuild\engine_physic.obj engine_physics\engine_physic.cpp
cl.exe %cl_setting% /Fobuild\box_physic.obj engine_physics\box_physic.cpp

cl.exe %cl_setting% /Fobuild\engine_graphic.obj engine_graphics\engine_graphic.cpp
cl.exe %cl_setting% /Fobuild\box_graphic.obj engine_graphics\box_graphic.cpp

cl.exe %cl_setting% /Fobuild\main.obj main.cpp

echo ---------- linking
set link_settings=
set link_settings=%link_settings% /NOLOGO
rem set link_settings=%link_settings% /DLL
set link_settings=%link_settings% /NODEFAULTLIB:LIBCMT
link.exe %link_settings% /OUT:release\main.exe build\*.obj %lib_list%
rem link.exe %link_settings% /OUT:release\main.exe build\main.obj %lib_list%

