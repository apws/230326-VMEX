
set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src

zcc +m5 %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app
pause


