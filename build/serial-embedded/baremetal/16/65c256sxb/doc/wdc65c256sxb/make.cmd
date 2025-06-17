set PATH=%PATH%;c:\~sdk\wdc\tools\bin
set SRC=..\..\src
SET WDC_LIB=c:\~sdk\wdc\Tools\lib

WDC816CC.exe -LT -LW -MS -QV -WQ -PA -PX -SOP -WU %SRC%\VMEX.c -I%SRC% -o VMEX.obj
WDCLN -O VMEX.HEX VMEX.OBJ -LCS -T -E -V
pause


