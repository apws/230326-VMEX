set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src
zcc +msx %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app

pause


