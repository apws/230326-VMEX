
set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src
zcc +cpm %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app
pause


