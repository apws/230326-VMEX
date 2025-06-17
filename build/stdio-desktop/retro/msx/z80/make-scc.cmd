set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src

rem zcc +msx -subtype=rom %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app
zcc +msx -compiler=sccz80 -subtype=rom %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app

pause


