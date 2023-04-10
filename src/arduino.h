/* Copyright (C) 2022, 2023 Petr Antos, AP-ware servis (mixworx.net) antos.petr@gmail.com - ALL RIGHTS RESERVED */

//#include <Arduino.h>
#ifdef ARDUINO

void setup()
{
    // Initialize the serial communication at 9600 baud rate
    Serial.begin(9600);
}

void loop()
{

    const TU8 testprog[] = {
        0x31,0xA0,0x08,0x00, //addi r10 r0 8
        0x31,0x10,0x05,0x00, //addi r1 r0 5
        0x31,0x11,0x04,0x00, //addi r1 r1 4
    };

    int result = vmex(testprog, sizeof(testprog));

    Serial.println("vmex restart");
}

#endif


