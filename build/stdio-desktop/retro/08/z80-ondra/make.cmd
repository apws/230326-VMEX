set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src

zcc +ondra %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app

pause


