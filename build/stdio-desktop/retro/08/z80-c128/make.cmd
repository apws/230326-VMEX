
set PATH=%PATH%;c:\z88dk\bin\
set SRC=..\..\..\..\..\src
zcc +c128 %SRC%\VMEX.c -I%SRC% -o VMEX.bin -create-app
  rem zcc +cpm -lc128cpm -lndos %SRC%\VMEX.c -I%SRC% -o VMEX.com -create-app
pause


