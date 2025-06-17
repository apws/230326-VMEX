rem set PATH=%PATH%;"C:\Program Files\Microchip\xc8\v2.4\bin\"
set SRC=..\..\..\..\..\..\src

xc8-cc %SRC%\VMEX.c -mcpu=16F15244 -O1 --memorysummary -o build\vmex.hex

pause
