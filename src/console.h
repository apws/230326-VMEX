/* Copyright (C) 2022, 2023 Petr Antos, AP-ware servis (mixworx.net) antos.petr@gmail.com - ALL RIGHTS RESERVED */

#ifdef CONSOLE

//#if defined(_WIN32) || defined(_WIN64) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)) || defined(__C64__) || defined(__C128__) || defined(__PLUS4__) || defined(__ATARI__) || defined(__APPLE2__) || defined(__SPECTRUM)
#ifdef DESKTOP  
   
    #include <stdio.h>
    
#endif


static TCHAR printbuffer[40];

//TODO problem with STDIO is that its input functions require HEAP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//TODO rewrite monitor for using this, use snprintf for arduino print/println
//     will be better to use printf output to real console on desktop / home computers(?) and snprintf on embedded serial

void input(TCHAR* line, TU8 size)
{
    #ifdef ARDUINO
        //Serial.read
    #else
        #ifdef DESKTOP
            fgets(line, size, stdin);
        #else
            //DEVICE UART INPUT
        #endif
    #endif
}

void print(const TCHAR* str)
{
    // implement console log output (serial uart)
    #ifdef ARDUINO
        Serial.print(str);
    #else
        #ifdef DESKTOP
            printf(str);
        #else
            //DEVICE UART PRINT
        #endif
    #endif
}

void println(const TCHAR* str)
{
    // implement console log output (serial uart)
    #ifdef ARDUINO
        Serial.println(str);
    #else
        #ifdef DESKTOP
            printf(str); printf("\n");
        #else
            //DEVICE UART PRINT
        #endif
    #endif
}

void println_num(TU32 num)
{
    // implement console log output (serial uart)
    #ifdef ARDUINO
        Serial.println(num);
    #else
        #ifdef DESKTOP
            printf("%d",num); printf("\n");
        #else
            //DEVICE UART PRINT
        #endif
    #endif
    
}


//TODO probably remove and use snprintf standard way
TCHAR* itoh(TU32 num, TU8 pos) 
{
    TU8 shift;
    TU8 hex_digit;
    TU8 i;
    for (i = 0; i < pos; i++) {
        shift = (pos*4-4) - (i * 4); // i << 2
        hex_digit = (num >> shift) & 0xF;
        printbuffer[i] = (hex_digit < 10) ? '0' + hex_digit : 'A' + (hex_digit - 10);
    }
    printbuffer[pos] = '\0';
    return printbuffer;
}

#endif
