rem set PATH=%PATH%;"C:\Program Files\Microchip\xc8\v2.4\bin\"
set SRC=..\..\..\..\..\..\src

xc16-gcc %SRC%\VMEX.c -mcpu=24FJ64GU205 -Wl,-Tp24FJ64GU205.gld -Wl,-Map=build\vmex.map -O1 -o build\vmex.hex

pause
