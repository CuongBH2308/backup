echo off
Rem set Path

set ANT_HOME=D:\Source\Tools\apache-ant-1.8.2
set JAVA_HOME=C:\Program Files\Java\jdk1.7.0

set PATH=%PATH%;D:\Source\Perforce\Workspace\Config
set PATH=%PATH%;C:\Program Files\Java\jdk1.7.0\bin
set PATH=%PATH%;C:\Program Files (x86)\Notepad++
set PATH=%PATH%;D:\Source\3p\sqlite
set PATH=%PATH%;%ANT_HOME%\bin
set PATH=%PATH%;D:\Source\3p\sqlite\sqlite-amalgamation-3070900
set PATH=%PATH%;C:\Program Files\SysinternalsSuite
set PATH=%PATH%;C:\cygwin\bin
set PATH=%PATH%;D:\Source\Tools\OllyDbg2.1
set PATH=%PATH%;D:\System\lua-5.2.1
set PATH=%PATH%;D:\Source\Tools\premake
set PATH=%PATH%;D:\System\Android\adt-bundle-windows-x86\sdk\platform-tools
set PATH=%PATH%;D:\System\Android\adt-bundle-windows-x86\sdk\tools
set PATH=%PATH%;D:\Source\3p\boost_1_49_0\stage\lib
set PATH=%PATH%;D:\Source\Tools\Apache-Subversion-1.7.7\bin



Rem For opencv
rem always use vc9 and x86
rem tbb runtime also required
call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\vsvars32.bat"
set OPENCV_SDK_DIR=D:\Source\3p\opencv
set PATH=%PATH%;%OPENCV_SDK_DIR%\build\x86\vc9\bin
set PATH=%PATH%;D:\Source\3p\tbb30_20101215oss_win\tbb30_20101215oss\bin\ia32\vc9
set ANDROID_NDK_DIR=D:\Source\3p\android-ndk-r8-windows\android-ndk-r8
set PATH=%PATH%;%ANDROID_NDK_DIR%
Rem set alias
doskey styletc=color 1F
doskey styledos=color 0F
doskey showdep=dumpbin /dependents $*
doskey cpuz="C:\Program Files\CPUID\CPU-Z\cpuz.exe"
doskey cmake="D:\System\CMake\CMake 2.8\bin\cmake.exe" $*
doskey puttyu=putty baiyanh@192.168.56.101

Rem EnvVar
set PROMPT=$P$_$$$S

Rem set p4 client
set P4CLIENT=baiyanh

Rem move to right dir
d:
cd D:\Source


REM keep the command windows stay!
cmd

cls





