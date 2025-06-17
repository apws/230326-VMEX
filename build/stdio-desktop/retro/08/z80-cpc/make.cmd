
set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src

zcc +cpc -clib ansi -lndos -Cz--audio -lm -v %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app
pause


