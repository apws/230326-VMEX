set PATH=%PATH%;c:\~sdk\cc65\bin
set SRC_DIR=..\..\..\..\..\src

cc65.exe %SRC_DIR%\VMEX.c -o VMEX.s
cl65 -t apple2 %SRC_DIR%\VMEX.c -o VMEX.bin

pause


