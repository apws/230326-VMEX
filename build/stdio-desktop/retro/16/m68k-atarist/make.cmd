set PATH=%PATH%;c:\~sdk\vbcc\bin
set VBCC=c:\~sdk\vbcc
set SRC_DIR=..\..\..\..\..\src

vc -I%VBCC%\targets\m68k-atari -c99 -O2 -+ -config=tos %SRC_DIR%\vmex.c -o vmex_atari_st

pause


