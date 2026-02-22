@echo off
setlocal enabledelayedexpansion

:: ----------------------------------------
:: Argument parsing
:: ----------------------------------------
for %%a in (%*) do set "%%a=1"

if not "%msvc%"=="1" set msvc=1
if not "%release%"=="1" set debug=1

if "%debug%"=="1" (
    set release=0
    echo [debug mode]
)

if "%release%"=="1" (
    set debug=0
    echo [release mode]
)

if "%msvc%"=="1" echo [msvc compile]

:: ----------------------------------------
 :: Compiler flags (C, not C++)
:: ----------------------------------------
set cl_warnings=/WX /W4 /wd4201 /wd4267 /wd4244 /wd4245 /wd4310 /wd4100 /wd4018 /wd4189 /wd4996 /wd4146 /wd4505 /wd4702 /wd4013 /wd4028 /wd4133 /wd4047 /wd4101 /wd4005 /wd4307 /wd4459

set cl_common=/nologo /FC /Z7 /Oi /TC /D_CRT_SECURE_NO_WARNINGS ^
               /I "%~dp0code" ^
               /I "%~dp0code\include" ^
               %cl_warnings%

set cl_debug=call cl /Od /Ob1 /MDd /DBUILD_DEBUG=1 %cl_common%
set cl_release=call cl /O2 /MD  /DBUILD_DEBUG=0 %cl_common%

:: ----------------------------------------
:: Linker
:: ----------------------------------------
set cl_link=/link /SUBSYSTEM:console /incremental:no /LIBPATH:"%~dp0%code\raylib" raylib.lib user32.lib gdi32.lib opengl32.lib winmm.lib shell32.lib
set cl_out=/out:

:: ----------------------------------------
:: Choose config
:: ----------------------------------------
if "%debug%"=="1"   set compile=%cl_debug%
if "%release%"=="1" set compile=%cl_release%

:: ----------------------------------------
:: Go to project root
:: ----------------------------------------
cd /D "%~dp0"

:: ----------------------------------------
:: Build directory
:: ----------------------------------------
set BUILD_DIR=build
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

:: ----------------------------------------
:: Compile
:: ----------------------------------------
pushd "%BUILD_DIR%"
del *.pdb *.obj >nul 2>&1

%compile% ^
    "%~dp0code\main\main.c" ^
    %cl_link% %cl_out%main.exe || exit /b 1

popd

:: ----------------------------------------
:: Cleanup
:: ----------------------------------------
endlocal
