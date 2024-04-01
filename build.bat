@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

if not exist build (mkdir build)
pushd build

set code_path=..\

:: GENERAL COMPILER FLAGS
set compiler=               -nologo &:: Suppress Startup Banner
set compiler=%compiler%     -Oi     &:: Use assembly intrinsics where possible
set compiler=%compiler%     -MT     &:: Include CRT library in the executable (static link)
set compiler=%compiler%     -Gm-    &:: Disable minimal rebuild
set  compiler=%compiler%     -GR-    &:: Disable runtime type info (C++)
set compiler=%compiler%     -EHa-   &:: Disable exception handling (C++)
set compiler=%compiler%     -W4     &:: Display warnings up to level 4
set compiler=%compiler%     -WX     &:: Treat all warnings as errors

:: IGNORE WARNINGS
set compiler=%compiler%     -wd4201 &:: Nameless struct/union
set compiler=%compiler%     -wd4100 &:: Unused function parameter
set compiler=%compiler%     -wd4189 &:: Local variable not referenced
set compiler=%compiler%     -wd4505 &:: Unreferenced local function has been removed
set compiler=%compiler% 	-wd4700 &:: Not initialized local variable was used
set compiler=%compiler% 	-wd4701 &::
set compiler=%compiler% 	-wd4244 &::
set compiler=%compiler% 	-wd4267 &::
set compiler=%compiler% 	-wd4996 &::
set compiler=%compiler% 	-wd4717 &::

:: DEBUG VARIABLES
set debug=        -FC &:: Produce the full path of the source code file
set debug=%debug% -Z7 &:: Produce debug information

cl -Od %compiler% %debug% %code_path%parser.cpp