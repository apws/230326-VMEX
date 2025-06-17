set PATH=%PATH%;c:\z88dk_bug\bin\
set SRC=..\..\..\..\..\src

zcc +zx -startup=0 -clib=sdcc_iy -v -zorg=24800 %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app

pause


