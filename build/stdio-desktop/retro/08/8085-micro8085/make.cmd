set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src

zcc +micro8085 %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app

pause


