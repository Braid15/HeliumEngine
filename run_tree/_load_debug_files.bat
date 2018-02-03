@ECHO OFF

set platform=%1
set platform_64=x64
set platform_86=x86

cd run_tree

del dbghelp.dll
del microsoft.dtfw.dhl.manifest

if %platform% == %platform_64% (
    del vld_x86.dll
    del vld_x86.pdb
)

if %platform% == %platform_86% (
    del vld_x64.dll
    del vld_x64.pdb
)

copy _%platform%_debug_files\dbghelp.dll .
copy _%platform%_debug_files\microsoft.dtfw.dhl.manifest .
copy _%platform%_debug_files\vld_%platform%.dll .
copy _%platform%_debug_files\vld_%platform%.pdb .

set "platform="
set "platform_64="
set "platform_86="
@ECHO ON
