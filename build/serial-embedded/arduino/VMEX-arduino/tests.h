
#ifdef RUN_TESTS

int runtests()
{

    int fails = 0;
      
    fails+= test(OPI11_ADDI,   "addi 16");
    //fails+= test(OPI12_SUBI,   "addi 16"); //pseudo
    fails+= test(OPI13_XORI,   "xori 16");
    fails+= test(OPI14_ANDI,   "andi 16");
    fails+= test(OPI15_ORI,    "ori 16");
    fails+= test(OPI16_SLLI,   "slli srli");
    fails+= test(OPI18_SRAI,   "srai");
    fails+= test(OPI1A_CLTI,   "clti 16");
    fails+= test(OPI1B_CLTIU,  "cltiu 16");
      
    fails+= test(OPU71_LUI,    "lui 32");
    fails+= test(OPU7A_AUIPC,  "auipc 32");

    fails+= test(OPR31_ADD,    "add 16");
    fails+= test(OPR32_SUB,    "sub 16");
    fails+= test(OPR33_XOR,    "xor 16");
    fails+= test(OPR34_AND,    "and 16");
    fails+= test(OPR35_OR,     "or 16");    
    fails+= test(OPR36_SLL,    "sll srl");
    fails+= test(OPR38_SRA,    "sra");
    fails+= test(OPR3A_CLT,    "clt 16");
    fails+= test(OPR3B_CLTU,   "cltu 16");
            
    printf("\nTest fails: %d\n", fails);
    
    return fails;
    
}


int test(TU8 opcode, const char* testname)
{
    int testresult;

    switch(opcode)
    {
        case OPI11_ADDI:
        {
            TU8 testprog[] =
            {
                0x11,0xAA,0x08,0x00, //addi r10 r10 $8
                0x11,0xAA,0x02,0x00, //addi r10 r10 $2
                0x11,0xAA,0xF4,0xFF, //addi r10 r10 -12
                0x11,0xAA,0x02,0x00, //addi r10 r10 2

                0x11,0xAA,0x00,0xF0, //addi r10 r10 $F000 (61440) = -4096
                0x11,0xAA,0x40,0x9C, //addi r10 r10 40000 ($9C40) = -25536
                0x11,0xAA,0xC0,0x73, //addi r10 r10 29632 ($73C0) = 29632

                0x11,0xAA,0x00,0x30, //addi r10 r10 $3000 (12288)
                0x11,0xAA,0x00,0x30, //addi r10 r10 $3000 (12288)
                0x11,0xAA,0x00,0x90, //addi r10 r10 -$7000 (= $9000 = -28672)
                0x11,0xAA,0x00,0x10, //addi r10 r10 $1000 (4096)
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPI13_XORI:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x78,0x56, //addi r10 r10 0x5678
                0x13,0xAA,0x0F,0x0F, //xori r10 r10 0x0F0F0
                0x13,0xAA,0x77,0x59, //xori r10 r10 0x05977
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPI14_ANDI:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x78,0x56, //addi r10 r10 0x5678
                0x14,0xAA,0x0F,0x0F, //andi r10 r10 0x0F0F0
                0x11,0xAA,0xF8,0xF9, //addi r10 r10 0xF9F8
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPI15_ORI:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x78,0x56, //addi r10 r10 0x5678
                0x15,0xAA,0x0F,0x0F, //ori r10 r10 0x0F0F0
                0x11,0xAA,0x81,0xA0, //addi r10 r10 0xA081
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPI16_SLLI:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x78,0x56, //addi r10 r10 0x5678
                0x16,0xAA,0x08,0x00, //slli r10 r10 8
                0x17,0xAA,0x08,0x00, //srli r10 r10 8
                0x11,0xAA,0x88,0xA9, //addi r10 r10 0xA988
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPI18_SRAI:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x88,0x88, //addi r10 r10 0x8888
                0x16,0xAA,0x10,0x00, //slli r10 r10 16
                0x18,0xAA,0x10,0x00, //srai r10 r10 16
                0x11,0xAA,0x78,0x77, //addi r10 r10 0x7778
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPI1A_CLTI:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x88,0x88, //addi r10 r10 0x8888
                0x1A,0xAA,0x99,0x99, //clti r10 r10 0x9999   //r10 < $9999
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF

                0x11,0xAA,0x88,0x00, //addi r10 r10 0x0088
                0x1A,0xAA,0x99,0x00, //clti r10 r10 0x0099   //r10 < $99
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF

                0x11,0xAA,0xE7,0xFF, //addi r10 r10 0xFFE7
                0x1A,0xAA,0xF0,0xFF, //clti r10 r10 0xFFF0   //r10 < $FFF0
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF

            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPI1B_CLTIU:
        {
            TU8 testprog[] = {
                0x11,0xA0,0x66,0x66, //addi r10 r0 0x6666
                0x1B,0xA0,0x99,0x99, //cltiu r10 r0 0x9999    //r10 <+ $9999
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPU71_LUI:
        {
            TU8 testprog[] = {
                0x71,0xAA,0x66,0x66, //lui r10 0x6666
                0x17,0xAA,0x10,0x00, //srli r10 r10 16
                0x11,0xAA,0x9A,0x99, //addi r10 r10 0x999A
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPU7A_AUIPC:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x00,0x00, //addi r10 r10 0
                0x11,0xAA,0x00,0x00, //addi r10 r10 0
                0x11,0xAA,0x00,0x00, //addi r10 r10 0
                0x11,0xAA,0x00,0x00, //addi r10 r10 0

                0x7A,0xAA,0x66,0x66, //auipc r10 0x6666
                0x14,0xAA,0xFF,0xFF, //andi r10 r10 0x0FFFF
                0x11,0xAA,0xF0,0xFF, //addi r10 r10 -16
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPR31_ADD:
        {
            TU8 testprog[] =
            {
                0x11,0xA0,0xFF,0xFF, //addi r10 r0 -1
                0x11,0xB0,0x03,0x00, //addi r11 r0 3
                0x31,0xA0,0xA0,0xB0, //add r10 r10 r11

                0x71,0xB0,0x00,0x00, //lui r11 0x0000
                0x11,0xB0,0x10,0x27, //addi r11 r0 10000
                0x31,0xA0,0xA0,0xB0, //add r10 r10 r11

                0x71,0xB0,0x00,0x00, //lui r11 0x0000
                0x11,0xBB,0xEE,0xD8, //addi r11 r11 -10002
                0x31,0xA0,0xA0,0xB0, //add r10 r10 r11
               
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPR32_SUB:
        {
            TU8 testprog[] =
            {
                0x11,0xA0,0x10,0x27, //addi r10 r0 10000
                0x11,0xB0,0x70,0x17, //addi r11 r0 6000
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 11
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 11
                0x11,0xAA,0xD0,0x07, //addi r10 r10 2000
               
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;
        
        case OPR33_XOR:
        {
            TU8 testprog[] = {
                0x11,0xA0,0x78,0x56, //addi r10 r0 0x5678  //r10=  $5678
                0x11,0xB0,0xF0,0x0F, //addi r11 r0 0x0FF0  //r11=  $0FF0
                0x33,0xA0,0xA0,0xB0, //xor r10 r10 r11     //r10^= r11
                0x11,0xB0,0x88,0x59, //addi r11 r0 0x5FF8  //r11=  $5988
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-= r11  
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;
            
        case OPR34_AND:
        {
            TU8 testprog[] = {
                0x11,0xA0,0x78,0x56, //addi r10 r0 0x5678  //r10=  $5678
                0x11,0xB0,0xF0,0x0F, //addi r11 r0 0x0FF0  //r11=  $0FF0
                0x34,0xA0,0xA0,0xB0, //and r10 r10 r11     //r10&= r11
                0x11,0xB0,0x70,0x06, //addi r11 r0 0x0670  //r11=  $0670
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-= r11  
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPR35_OR:
        {
            TU8 testprog[] = {
                0x11,0xA0,0x78,0x56, //addi r10 r0 0x5678  //r10=  $5678
                0x11,0xB0,0xF0,0x0F, //addi r11 r0 0x0FF0  //r11=  $0FF0
                0x35,0xA0,0xA0,0xB0, //or r10 r10 r11      //r10!= r11
                0x11,0xB0,0xF8,0x5F, //addi r11 r0 0x5FF8  //r11=  $5FF8
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-= r11  
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPR36_SLL:
        {
            TU8 testprog[] = {
                0x11,0xA0,0x78,0x56, //addi r10 r0 0x5678
                0x11,0xB0,0x08,0x00, //addi r11 r0 0x8
                0x36,0xA0,0xA0,0xB0, //sll r10 r10 r11    //r0<<=  r11
                0x37,0xA0,0xA0,0xB0, //srl r10 r10 r11    //r0>>=  r11
                0x11,0xB0,0x78,0x56, //addi r11 r0 0x5678
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-=  r11  
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPR38_SRA:
        {
            TU8 testprog[] = {
                0x11,0xAA,0x88,0x88, //addi r10 r10 0x8888
                0x11,0xB0,0x10,0x00, //addi r11 r0 0x10
                0x36,0xA0,0xA0,0xB0, //sll r10 r10 r11     //r0<<=  r11
                0x38,0xA0,0xA0,0xB0, //sra r10 r10 r11     //r0>>>= r11
                0x11,0xAA,0x78,0x77, //addi r10 r10 30584  //r0+= 30584 
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

        case OPR3A_CLT:
        {
            TU8 testprog[] = {
                0x11,0xA0,0x88,0x88, //addi r10 r0 0x8888
                0x11,0xB0,0x99,0x99, //clti r10 r0 0x9999
                0x3A,0xA0,0xA0,0xB0, //clt r10 r10 r11
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1

                0x11,0xA0,0x88,0x00, //addi r10 r0 0x0088
                0x11,0xB0,0x88,0x00, //addi r11 r0 0x0088
                0x3A,0xA0,0xA0,0xB0, //clt r10 r10 r11
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1

                0x11,0xA0,0xE7,0xFF, //addi r10 r0 0xFFE7
                0x11,0xB0,0xF0,0xFF, //addi r11 r0 0xFFF0
                0x3A,0xA0,0xA0,0xB0, //clt r10 r10 r11
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;
        
        case OPR3B_CLTU:
        {
            TU8 testprog[] = {
                0x11,0xA0,0x66,0x66, //addi r10 r0 0x6666
                0x11,0xB0,0x99,0x99, //addi r11 r0 0x9999
                0x3B,0xA0,0xA0,0xB0, //cltu r10 r10 r11
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF
            };
            testresult = vmex(testprog, sizeof(testprog));
            printf("%s: %d\n", testname, testresult); if (testresult!=0) return 1;
        }
        break;

    }


    return 0;
}

#endif

