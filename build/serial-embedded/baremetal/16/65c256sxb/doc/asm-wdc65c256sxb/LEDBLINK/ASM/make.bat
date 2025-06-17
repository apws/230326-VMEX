REM LEDBLINK Demo for the W65C265SXB
REM 2022-10-24

del *.bin
del *.obj
del *.lst

WDC816AS -g -l -DUSING_816 LEDBLINK.asm
WDCLN -g -sz -t -HI LEDBLINK
WDCLN -g -sz -t -HM28 LEDBLINK
WDCLN -g -sz -t -HZ LEDBLINK
pause
