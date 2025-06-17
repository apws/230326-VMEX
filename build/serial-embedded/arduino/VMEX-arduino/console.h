

TCHAR printbuffer[9];

void print(const TCHAR* str)
{
#ifdef CONSOLE    
    // implement console log output (serial uart)
    #ifdef ARDUINO
    Serial.print(str);
    #endif
#endif
}
void println(const TCHAR* str)
{
#ifdef CONSOLE    
    // implement console log output (serial uart)
    #ifdef ARDUINO
    Serial.println(str);
    #endif
#endif
}

TCHAR* itoh(TU32 num) 
{
#ifdef CONSOLE    
    TU8 shift;
    TU8 hex_digit;
    for (TU8 i = 0; i < 8; i++) {
        shift = 28 - (i * 4);
        hex_digit = (num >> shift) & 0xF;
        printbuffer[i] = (hex_digit < 10) ? '0' + hex_digit : 'A' + (hex_digit - 10);
    }
    printbuffer[8] = '\0';
    return printbuffer;
#endif
}
