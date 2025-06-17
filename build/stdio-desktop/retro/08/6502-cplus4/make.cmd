set PATH=%PATH%;c:\~sdk\cc65\bin
set SRC=..\..\..\..\..\src

cc65.exe %SRC%\VMEX.c -o VMEX.s
cl65 -t plus4  %SRC%\VMEX.c -o VMEX.bin

pause


