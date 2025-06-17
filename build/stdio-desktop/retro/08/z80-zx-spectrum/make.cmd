set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src

rem SDCC - SLOW compile time and issues when ALL tests are enabled !!!
rem -startup=4
rem zcc +zx -v -startup=0 -clib=sdcc_iy -zorg=24800 %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app

rem SCCZ80 - FAST compile time and no issues with ALL tests !!!
zcc +zx -vn -clib=new -O3 -startup=1 %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app

pause


