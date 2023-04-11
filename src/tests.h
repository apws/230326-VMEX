/* Copyright (C) 2022, 2023 Petr Antos, AP-ware servis (mixworx.net) antos.petr@gmail.com - ALL RIGHTS RESERVED */

#define TEST_IMMEDIATE          //!!!
#define TEST_LUI_AUIPC_JAL      //!!!
#define TEST_REGISTERS
#define TEST_MULDIV             //!!!
#define TEST_COMPARE_MOV_UNARY
#define TEST_MEMORY_16
#define TEST_BRANCHES
#define TEST_BRANCHES_ZERO
#define TEST_SYS_JR_JALR
#define TEST_MEMORY_32


#ifdef RUN_TESTS

//here we USE stdio, /test arg is valid for "DESKTOP"
#include <stdio.h>    // printf, sprintf - without heap, no fgets, no scanf, simply NO imputs !!!


int runtests();
int test(TU8 opcode, const char* testname);

int runtests()
{

    int fails = 0;

    fails+= test(OP00_NOP,     "nop");

#ifdef TEST_IMMEDIATE
    fails+= test(OPI11_ADDI,   "addi 16");
    fails+= test(OPI12_SUBI,   "subi 16"); //pseudo
    fails+= test(OPI13_XORI,   "xori 16");
    fails+= test(OPI14_ANDI,   "andi 16");
    fails+= test(OPI15_ORI,    "ori 16");
    fails+= test(OPI16_SLLI,   "slli srli");
    fails+= test(OPI18_SRAI,   "srai");
    fails+= test(OPI1A_CLTI,   "clti 16");
    fails+= test(OPI1B_CLTIU,  "cltiu 16");

    fails+= test(OPI1E_LI,     "li 16"); //pseudo

    fails+= test(OPI1F_LI,     "li - fusion"); //TODO //pseudo fusion
#endif

#ifdef TEST_LUI_AUIPC_JAL
    fails+= test(OPU71_LUI,    "lui 32");
    fails+= test(OPU7A_AUIPC,  "auipc 32");

    fails+= test(OPU7F_JAL,    "jal jl jalr (ret)");
    fails+= test(OPU66_GOTO,   "goto=66 call=6C ret=44"); //pseudo //J //JL
#endif

#ifdef TEST_REGISTERS
    fails+= test(OPR31_ADD,    "add 16");
    fails+= test(OPR32_SUB,    "sub 16");
    fails+= test(OPR33_XOR,    "xor 16");
    fails+= test(OPR34_AND,    "and 16");
    fails+= test(OPR35_OR,     "or 16");
    fails+= test(OPR36_SLL,    "sll srl");
    fails+= test(OPR38_SRA,    "sra");
    fails+= test(OPR3A_CLT,    "clt 16");
    fails+= test(OPR3B_CLTU,   "cltu 16");
#endif

#ifdef TEST_MULDIV
    fails+= test(OPR21_MUL,    "mul mulh");
    fails+= test(OPR23_MULHU,  "mulhu");
    fails+= test(OPR24_MULHSU, "mulshu");
    fails+= test(OPR25_DIV,    "div");
    fails+= test(OPR26_DIVU,   "divu");
    fails+= test(OPR27_REM,    "rem");
    fails+= test(OPR28_REMU,   "remu");
#endif

#ifdef TEST_COMPARE_MOV_UNARY
    fails+= test(OPIC1_CLTZ,   "cltz 16"); //pseudo
    fails+= test(OPIC3_CNEZ,   "cnez 16"); //pseudo
    fails+= test(OPIC4_CEQZ,   "ceqz 16"); //pseudo
    fails+= test(OPIC6_CGTZ,   "cgtz 16"); //pseudo

    fails+= test(OPIDD_MOV,    "mov 16"); //pseudo
    fails+= test(OPID0_INI,    "ini 16"); //pseudo //??????????????????
    fails+= test(OPIDE_NEG,    "neg 16"); //pseudo
    fails+= test(OPIDF_NOT,    "not 16"); //pseudo
#endif

#ifdef TEST_MEMORY_16
    fails+= test(OPS51_WB,     "wb lb");
    fails+= test(OPS52_WH,     "wh lh");
    fails+= test(OPS54_WW,     "ww lw");
    fails+= test(OPIAB_LBU,    "lbu");
    fails+= test(OPIAD_LHU,    "lhu");
#endif

#ifdef TEST_BRANCHES
    fails+= test(OPSB1_BLT,    "blt");
    fails+= test(OPSB2_BLE,    "ble"); //pseudo
    fails+= test(OPSB3_BNE,    "bne");
    fails+= test(OPSB4_BEQ,    "beq");
    fails+= test(OPSB5_BGE,    "bge");
    fails+= test(OPSB6_BGT,    "bgt"); //pseudo

    fails+= test(OPSBA_BLTU,   "bltu");
    fails+= test(OPSBB_BLEU,   "bleu"); //pseudo
    fails+= test(OPSBC_BGEU,   "bgeu");
    fails+= test(OPSBD_BGTU,   "bgtu"); //pseudo
#endif

#ifdef TEST_BRANCHES_ZERO
    fails+= test(OPS81_BLTZ,   "bltz"); //pseudo
    fails+= test(OPS82_BLEZ,   "blez"); //pseudo
    fails+= test(OPS83_BNEZ,   "bnez"); //pseudo
    fails+= test(OPS84_BEQZ,   "beqz"); //pseudo
    fails+= test(OPS85_BGEZ,   "bgez"); //pseudo
    fails+= test(OPS86_BGTZ,   "bgtz"); //pseudo
#endif

#ifdef TEST_SYS_JR_JALR
    fails+= test(OPI42_ECALL,  "ecall");  //TODO
    fails+= test(OPI48_EBREAK, "ebreak"); //TODO

    fails+= test(OPI40_FENCE,  "fence");

    fails+= test(OPI46_IGOTO,  "igoto"); //TODO  //pseudo //JR
    fails+= test(OPI4C_ICALL,  "icall"); //TODO  //pseudo //JALR

    fails+= test(OPIEC_FCALL,  "fcall 32");  //TODO //pseudo //CALL
    fails+= test(OPIEE_FTAIL,  "ftail 32");  //TODO //pseudo //TAIL
#endif

#ifdef TEST_MEMORY_32
//TODO #define OPIEA_LA      0xEA //pseudo

    fails+= test(OPIEA_LA,    "la 16 (li)");
    fails+= test(OPIEA_LA,    "la - fusion");

//TODO #define OPIE1_LB      0xE1 //pseudo
//TODO #define OPIE2_LH      0xE2 //pseudo
//TODO #define OPIE4_LW      0xE4 //pseudo

//TODO #define OPSF1_WB      0xF1 //pseudo
//TODO #define OPSF2_WH      0xF2 //pseudo
//TODO #define OPSF4_WW      0xF4 //pseudo

    fails+= test(OPSF1_WB,     "wb lb - fusion");
    fails+= test(OPSF2_WH,     "wh lh - fusion");
    fails+= test(OPSF4_WW,     "ww lw - fusion");
#endif

    printf("\nTest fails: %d\n", fails);

    return fails;

}


int test(TU8 opcode, const char* testname)
{
    int testresult;

    switch(opcode)
    {

        case OP00_NOP:
        {
            const TU8 tpOP00_NOP[] =
            {
                0x00,0x00,0x00,0x00, //nop
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOP00_NOP, sizeof(tpOP00_NOP));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;

#ifdef TEST_IMMEDIATE
        case OPI11_ADDI:
        {
            const TU8 tpOPI11_ADDI[] =
            {
                0x11,0xAA,0x00,0x08, //addi r10 r10 $8
                0x11,0xAA,0x00,0x02, //addi r10 r10 $2
                0x11,0xAA,0xFF,0xF4, //addi r10 r10 -12
                0x11,0xAA,0x00,0x02, //addi r10 r10 2

                0x11,0xAA,0xF0,0x00, //addi r10 r10 $F000 (61440) = -4096
                0x11,0xAA,0x9c,0x40, //addi r10 r10 40000 ($9C40) = -25536
                0x11,0xAA,0x73,0xC0, //addi r10 r10 29632 ($73C0) = 29632

                0x11,0xAA,0x30,0x00, //addi r10 r10 $3000 (12288)
                0x11,0xAA,0x30,0x00, //addi r10 r10 $3000 (12288)
                0x11,0xAA,0x90,0x00, //addi r10 r10 -$7000 (= $9000 = -28672)
                0x11,0xAA,0x10,0x00, //addi r10 r10 $1000 (4096)
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI11_ADDI, sizeof(tpOPI11_ADDI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI12_SUBI:
        {
            const TU8 tpOPI12_SUBI[] =
            {
                0x11,0xA0,0x00,0x08, //addi r10 r0 $8
                0x11,0xAA,0x00,0x02, //addi r10 r10 $2
                0x12,0xAA,0x00,0x0C, //subi r10 r10 12
                0x11,0xAA,0x00,0x02, //addi r10 r10 2

                0x12,0xAA,0xFF,0xE8, //subi r10 r10 -24
                0x12,0xAA,0x00,0x30, //subi r10 r10 48
                0x12,0xAA,0xFF,0xE8, //subi r10 r10 -24
                
                0x11,0xAA,0x30,0x00, //addi r10 r10 $3000 (12288)
                0x11,0xAA,0x30,0x00, //addi r10 r10 $3000 (12288)
                0x12,0xAA,0x70,0x00, //subi r10 r10 $7000 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x10,0x00, //addi r10 r10 $1000 (4096)
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI12_SUBI, sizeof(tpOPI12_SUBI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI13_XORI:
        {
            const TU8 tpOPI13_XORI[] = {
                0x11,0xAA,0x56,0x78, //addi r10 r10 0x5678
                0x13,0xAA,0x0F,0x0F, //xori r10 r10 0x0F0F0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x13,0xAA,0x59,0x77, //xori r10 r10 0x05977 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI13_XORI, sizeof(tpOPI13_XORI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI14_ANDI:
        {
            const TU8 tpOPI14_ANDI[] = {
                0x11,0xAA,0x56,0x78, //addi r10 r10 0x5678
                0x14,0xAA,0x0F,0x0F, //andi r10 r10 0x0F0F0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xF9,0xF8, //addi r10 r10 0xF9F8
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI14_ANDI, sizeof(tpOPI14_ANDI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI15_ORI:
        {
            const TU8 tpOPI15_ORI[] = {
                0x11,0xAA,0x56,0x78, //addi r10 r10 0x5678
                0x15,0xAA,0x0F,0x0F, //ori r10 r10 0x0F0F0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xA0,0x81, //addi r10 r10 0xA081
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI15_ORI, sizeof(tpOPI15_ORI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI16_SLLI: // + SRLI
        {
            const TU8 tpOPI16_SLLI[] = {
                0x11,0xAA,0x56,0x78, //addi r10 r10 0x5678
                0x16,0xAA,0x00,0x08, //slli r10 r10 8 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x17,0xAA,0x00,0x08, //srli r10 r10 8 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xA9,0x88, //addi r10 r10 0xA988
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI16_SLLI, sizeof(tpOPI16_SLLI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI18_SRAI:
        {
            const TU8 tpOPI18_SRAI[] = {
                0x11,0xAA,0x88,0x88, //addi r10 r10 0x8888
                0x16,0xAA,0x00,0x10, //slli r10 r10 16
                0x18,0xAA,0x00,0x10, //srai r10 r10 16 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x77,0x78, //addi r10 r10 0x7778
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI18_SRAI, sizeof(tpOPI18_SRAI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI1A_CLTI:
        {
            const TU8 tpOPI1A_CLTI[] = {
                0x11,0xAA,0x88,0x88, //addi r10 r10 0x8888
                0x1A,0xAA,0x99,0x99, //clti r10 r10 0x9999   //r10 < $9999 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x12,0xAA,0x00,0x01, //subi r10 r10 0x0001

                0x11,0xAA,0x00,0x88, //addi r10 r10 0x0088
                0x1A,0xAA,0x00,0x99, //clti r10 r10 0x0099   //r10 < $99 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF

                0x11,0xAA,0xFF,0xE7, //addi r10 r10 0xFFE7
                0x1A,0xAA,0xFF,0xF0, //clti r10 r10 0xFFF0   //r10 < $FFF0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF

            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI1A_CLTI, sizeof(tpOPI1A_CLTI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI1B_CLTIU:
        {
            const TU8 tpOPI1B_CLTIU[] = {
                0x11,0xA0,0x66,0x66, //addi r10 r0 0x6666
                0x1B,0xA0,0x99,0x99, //cltiu r10 r0 0x9999    //r10 <+ $9999 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI1B_CLTIU, sizeof(tpOPI1B_CLTIU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPI1E_LI:
        {
            const TU8 tpOPI1E_LI[] =
            {
                0x1E,0xA0,0x00,0x08, //li r10 $8
                0x11,0xAA,0x00,0x02, //addi r10 r10 $2
                0x11,0xAA,0xFF,0xF4, //addi r10 r10 -12
                0x11,0xAA,0x00,0x02, //addi r10 r10 2

                0x1E,0xA0,0xF0,0x00, //li r10 $F000 (61440) = -4096
                0x11,0xAA,0x9c,0x40, //addi r10 r10 40000 ($9C40) = -25536
                0x11,0xAA,0x73,0xC0, //addi r10 r10 29632 ($73C0) = 29632

                0x1E,0xA0,0x30,0x00, //li r10 $3000 (12288)
                0x11,0xAA,0x30,0x00, //addi r10 r10 $3000 (12288)
                0x11,0xAA,0x90,0x00, //addi r10 r10 -$7000 (= $9000 = -28672)
                0x11,0xAA,0x10,0x00, //addi r10 r10 $1000 (4096)
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI1E_LI, sizeof(tpOPI1E_LI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;

        //TODO
        //LI 32 bit- probably LI fused with ORI !!!
#endif

#ifdef TEST_LUI_AUIPC_JAL
        case OPU71_LUI:
        {
            const TU8 tpOPU71_LUI[] = {
                0x71,0xA0,0x66,0x66, //lui r10 0x6666 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x17,0xAA,0x00,0x10, //srli r10 r10 16
                0x11,0xAA,0x99,0x9A, //addi r10 r10 0x999A
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPU71_LUI, sizeof(tpOPU71_LUI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPU7A_AUIPC:
        {
            const TU8 tpOPU7A_AUIPC[] = {
                0x11,0xAA,0x00,0x00, //addi r10 r10 0
                0x11,0xAA,0x00,0x00, //addi r10 r10 0
                0x11,0xAA,0x00,0x00, //addi r10 r10 0
                0x11,0xAA,0x00,0x00, //addi r10 r10 0

                0x7A,0xAA,0x66,0x66, //auipc r10 0x6666 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xAA,0xFF,0xFF, //andi r10 r10 0x0FFFF
                0x11,0xAA,0xFF,0xF0, //addi r10 r10 -16
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPU7A_AUIPC, sizeof(tpOPU7A_AUIPC));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPU7F_JAL: //JALR
        {
            const TU8 tpOPU7F_JAL[] = {
                0x11,0xAA,0x11,0x11, //00  //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //04  //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x20,0x00, //08  //addi r12 r0 0x2000   //  r12     = $2000
                0x7F,0x00,0x00,0x01, //0C  //jal r0, +1           //  jal r0 +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //10  //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xD0,0x00,0x04, //14  //addi r13 r0 4        //  r13     = 4
                0x11,0xE0,0x00,0x07, //18  //addi r17 r0 7        //  r14     = 7
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //1C  //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //20  //addi r13 r13 1       //  r10    += 1
                0xB5,0xDE,0x00,0x01, //24  //bge r13 r14 +1       // if (r13 >= r14) then +1
                0x7F,0x00,0xFF,0xFC, //28  //jal r0, -4           // (until) jal r0 -4 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //call sub
                0x7F,0x10,0x00,0x01, //30 //jal r1, +1            //  jal r1 +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //skip sub
                0x7F,0x00,0x00,0x02, //34  //jal r0, +2           //  jal r0 +2 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //sub
                0x11,0xAA,0x22,0x22, //38  //addi r10 r10 0x2222  //  r10    += $2222
                0x4F,0x01,0x00,0x00, //3C  //jalr r0 r1 0         //  ret //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //end
                0x12,0xAA,0x66,0x66, //40  //subi r10 r10 $6666   //  r10    -= $6666
                0x00,0x00,0x00,0x00, //44  //nop                  //  nop

            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPU7F_JAL, sizeof(tpOPU7F_JAL));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPU66_GOTO: //CALL //RET
        {
            const TU8 tpOPU66_GOTO[] = {
                0x11,0xAA,0x11,0x11, //00  //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //04  //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x20,0x00, //08  //addi r12 r0 0x2000   //  r12     = $2000
                0x66,0x00,0x00,0x01, //0C  //goto +1              //  goto +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //10  //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xD0,0x00,0x04, //14  //addi r13 r0 4        //  r13     = 4
                0x11,0xE0,0x00,0x07, //18  //addi r17 r0 7        //  r14     = 7
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //1C  //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //20  //addi r13 r13 1       //  r10    += 1
                0xB5,0xDE,0x00,0x01, //24  //bge r13 r14 +1       // if (r13 >= r14) then +1
                0x66,0x00,0xFF,0xFC, //28  //goto -4              // (until) goto -4 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //call sub
                0x6C,0x10,0x00,0x01, //30 //call +1               //  call +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //skip sub
                0x66,0x00,0x00,0x02, //34  //goto +2              //  goto +2 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //sub
                0x11,0xAA,0x22,0x22, //38  //addi r10 r10 0x2222  //  r10    += $2222
                0x44,0x00,0x00,0x00, //3C  //ret                  //  ret //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                //end
                0x12,0xAA,0x66,0x66, //40  //subi r10 r10 $6666   //  r10    -= $6666
                0x00,0x00,0x00,0x00, //44  //nop                  //  nop

            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPU66_GOTO, sizeof(tpOPU66_GOTO));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;
#endif

#ifdef TEST_REGISTERS
        case OPR31_ADD:
        {
            const TU8 tpOPR31_ADD[] =
            {
                0x11,0xA0,0xFF,0xFF, //addi r10 r0 -1
                0x11,0xB0,0x00,0x03, //addi r11 r0 3
                0x31,0xA0,0xA0,0xB0, //add r10 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                0x71,0xB0,0x00,0x00, //lui r11 0x0000
                0x11,0xB0,0x27,0x10, //addi r11 r0 10000
                0x31,0xA0,0xA0,0xB0, //add r10 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                0x71,0xB0,0x00,0x00, //lui r11 0x0000
                0x11,0xBB,0xD8,0xEE, //addi r11 r11 -10002
                0x31,0xA0,0xA0,0xB0, //add r10 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR31_ADD, sizeof(tpOPR31_ADD));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR32_SUB:
        {
            const TU8 tpOPR32_SUB[] =
            {
                0x11,0xA0,0x27,0x10, //addi r10 r0 10000
                0x11,0xB0,0x17,0x70, //addi r11 r0 6000
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x07,0xD0, //addi r10 r10 2000

            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR32_SUB, sizeof(tpOPR32_SUB));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR33_XOR:
        {
            const TU8 tpOPR33_XOR[] = {
                0x11,0xA0,0x56,0x78, //addi r10 r0 0x5678  //r10=  $5678
                0x11,0xB0,0x0F,0xF0, //addi r11 r0 0x0FF0  //r11=  $0FF0
                0x33,0xA0,0xA0,0xB0, //xor r10 r10 r11     //r10^= r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xB0,0x59,0x88, //addi r11 r0 0x5988  //r11=  $5988
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-= r11
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR33_XOR, sizeof(tpOPR33_XOR));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR34_AND:
        {
            const TU8 tpOPR34_AND[] = {
                0x11,0xA0,0x56,0x78, //addi r10 r0 0x5678  //r10=  $5678
                0x11,0xB0,0x0F,0xF0, //addi r11 r0 0x0FF0  //r11=  $0FF0
                0x34,0xA0,0xA0,0xB0, //and r10 r10 r11     //r10&= r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xB0,0x06,0x70, //addi r11 r0 0x0670  //r11=  $0670
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-= r11
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR34_AND, sizeof(tpOPR34_AND));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR35_OR:
        {
            const TU8 tpOPR35_OR[] = {
                0x11,0xA0,0x56,0x78, //addi r10 r0 0x5678  //r10=  $5678
                0x11,0xB0,0x0F,0xF0, //addi r11 r0 0x0FF0  //r11=  $0FF0
                0x35,0xA0,0xA0,0xB0, //or r10 r10 r11      //r10!= r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xB0,0x5F,0xF8, //addi r11 r0 0x5FF8  //r11=  $5FF8
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-= r11
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR35_OR, sizeof(tpOPR35_OR));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR36_SLL: // + SRL
        {
            const TU8 tpOPR36_SLL[] = {
                0x11,0xA0,0x56,0x78, //addi r10 r0 0x5678
                0x11,0xB0,0x00,0x08, //addi r11 r0 0x8
                0x36,0xA0,0xA0,0xB0, //sll r10 r10 r11    //r0<<=  r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x37,0xA0,0xA0,0xB0, //srl r10 r10 r11    //r0>>>= r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xB0,0x56,0x78, //addi r11 r0 0x5678
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11     //r10-=  r11
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR36_SLL, sizeof(tpOPR36_SLL));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR38_SRA:
        {
            const TU8 tpOPR38_SRA[] = {
                0x11,0xAA,0x88,0x88, //addi r10 r10 0x8888
                0x11,0xB0,0x00,0x10, //addi r11 r0 0x10
                0x36,0xA0,0xA0,0xB0, //sll r10 r10 r11     //r0<<=  r11
                0x38,0xA0,0xA0,0xB0, //sra r10 r10 r11     //r0>>=  r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x77,0x78, //addi r10 r10 30584  //r0+= 30584
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR38_SRA, sizeof(tpOPR38_SRA));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR3A_CLT:
        {
            const TU8 tpOPR3A_CLT[] = {
                0x11,0xA0,0x88,0x88, //addi r10 r0 0x8888
                0x11,0xB0,0x99,0x99, //addi r10 r0 0x9999
                0x3A,0xA0,0xA0,0xB0, //clt r10 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1

                0x11,0xA0,0x00,0x88, //addi r10 r0 0x0088
                0x11,0xB0,0x00,0x88, //addi r11 r0 0x0088
                0x3A,0xA0,0xA0,0xB0, //clt r10 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1

                0x11,0xA0,0xFF,0xE7, //addi r10 r0 0xFFE7
                0x11,0xB0,0xFF,0xF0, //addi r11 r0 0xFFF0
                0x3A,0xA0,0xA0,0xB0, //clt r10 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR3A_CLT, sizeof(tpOPR3A_CLT));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR3B_CLTU:
        {
            const TU8 tpOPR3B_CLTU[] = {
                0x11,0xA0,0x66,0x66, //addi r10 r0 0x6666
                0x11,0xB0,0x99,0x99, //addi r11 r0 0x9999
                0x3B,0xA0,0xA0,0xB0, //cltu r10 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 0xFFFF
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR3B_CLTU, sizeof(tpOPR3B_CLTU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;
#endif

#ifdef TEST_MULDIV
        case OPR21_MUL: //MULH
        {
            const TU8 tpOPR21_MUL[] = {
                0x71,0xA0,0x77,0x77, //lui  r10  0x7777
                0x11,0xAA,0x77,0x77, //addi r10 r10 0x7777
                0x71,0xB0,0x66,0x66, //lui  r11  0x6666
                0x11,0xBB,0x66,0x66, //addi r11 r0 0x6666
                0x21,0xC0,0xA0,0xB0, //mul r12 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x22,0xD0,0xA0,0xB0, //mulh r13 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xCC,0xFF,0xFF, //andi r12 r12 0xFFFF
                0x14,0xDD,0xFF,0xFF, //andi r13 r13 0xFFFF
                0x32,0xA0,0xD0,0xC0, //sub r10 r13 r12
                0x12,0xAA,0x5F,0x92, //subi r10 r10 $5F92
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR21_MUL, sizeof(tpOPR21_MUL));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR23_MULHU:
        {
            const TU8 tpOPR23_MULHU[] = {
                0x71,0xA0,0x99,0x99, //lui  r10  0x9999
                0x13,0xAA,0x99,0x99, //ori r10 r10 0x9999 //ORI here used for clash free large unsigned init
                0x71,0xB0,0x88,0x88, //lui  r11  0x8888
                0x13,0xBB,0x88,0x88, //ori r11 r0 0x8888
                0x21,0xC0,0xA0,0xB0, //mul r12 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x23,0xD0,0xA0,0xB0, //mulhu r13 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xCC,0xFF,0xFF, //andi r12 r12 0xFFFF
                0x14,0xDD,0xFF,0xFF, //andi r13 r13 0xFFFF
                0x32,0xA0,0xC0,0xD0, //sub r10 r12 r13
                0x12,0xAA,0x5C,0x2A, //subi r10 r10 $5C2A
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR23_MULHU, sizeof(tpOPR23_MULHU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR24_MULHSU:
        {
            const TU8 tpOPR24_MULHSU[] = {
                0x71,0xA0,0x99,0x99, //lui  r10  0x9999
                0x13,0xAA,0x99,0x99, //ori r10 r10 0x9999 //ORI here used for clash free large unsigned init
                0x71,0xB0,0x88,0x88, //lui  r11  0x8888
                0x13,0xBB,0x88,0x88, //ori r11 r0 0x8888
                0x21,0xC0,0xA0,0xB0, //mul r12 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x24,0xD0,0xA0,0xB0, //mulhsu r13 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xCC,0xFF,0xFF, //andi r12 r12 0xFFFF
                0x14,0xDD,0xFF,0xFF, //andi r13 r13 0xFFFF
                0x32,0xA0,0xC0,0xD0, //sub r10 r12 r13
                0x12,0xAA,0x7E,0x4B, //subi r10 r10 $7E4B
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR24_MULHSU, sizeof(tpOPR24_MULHSU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR25_DIV:
        {
            const TU8 tpOPR25_DIV[] = {
                0x71,0xA0,0x77,0x77, //lui  r10  0x7777
                0x13,0xAA,0x77,0x77, //ori r10 r10 0x7777 //ORI here used for clash free large unsigned init
                0x71,0xB0,0x00,0x00, //lui  r11  0x0000
                0x13,0xBB,0x55,0x55, //ori r11 r0 0x5555
                0x25,0xC0,0xA0,0xB0, //div r12 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xCC,0xFF,0xFF, //andi r12 r12 0xFFFF
                0x12,0xAC,0x66,0x67, //subi r10 r12 $6667
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR25_DIV, sizeof(tpOPR25_DIV));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR26_DIVU:
        {
            const TU8 tpOPR26_DIVU[] = {
                0x71,0xA0,0xCC,0xCC, //lui  r10  0xCCCC
                0x13,0xAA,0xCC,0xCC, //ori r10 r10 0xCCCC //ORI here used for clash free large unsigned init
                0x71,0xB0,0x00,0x00, //lui  r11  0x0000
                0x13,0xBB,0x88,0x88, //ori r11 r0 0x8888
                0x26,0xC0,0xA0,0xB0, //div r12 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xCC,0xFF,0xFF, //andi r12 r12 0xFFFF
                0x12,0xCC,0x30,0x00, //subi r12 r12 0x3000
                0x12,0xAC,0x50,0x01, //subi r10 r12 $5001
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR26_DIVU, sizeof(tpOPR26_DIVU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR27_REM:
        {
            const TU8 tpOPR27_REM[] = {
                0x71,0xA0,0x77,0x77, //lui  r10  0x7777
                0x13,0xAA,0x77,0x77, //ori r10 r10 0x7777 //ORI here used for clash free large unsigned init
                0x71,0xB0,0x00,0x00, //lui  r11  0x0000
                0x13,0xBB,0x55,0x55, //ori r11 r0 0x5555
                0x27,0xC0,0xA0,0xB0, //rem r12 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xCC,0xFF,0xFF, //andi r12 r12 0xFFFF
                0x12,0xAC,0x44,0x44, //subi r10 r12 $4444
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR27_REM, sizeof(tpOPR27_REM));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPR28_REMU:
        {
            const TU8 tpOPR28_REMU[] = {
                0x71,0xA0,0xCC,0xCC, //lui  r10  0xCCCC
                0x13,0xAA,0xCC,0xCC, //ori r10 r10 0xCCCC //ORI here used for clash free large unsigned init
                0x71,0xB0,0x00,0x00, //lui  r11  0x0000
                0x13,0xBB,0x88,0x88, //ori r11 r0 0x8888
                0x28,0xC0,0xA0,0xB0, //remu r12 r10 r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x14,0xCC,0xFF,0xFF, //andi r12 r12 0xFFFF
                0x12,0xAC,0x44,0x44, //subi r10 r12 $4444
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPR28_REMU, sizeof(tpOPR28_REMU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;
#endif

#ifdef TEST_COMPARE_MOV_UNARY
        case OPIC1_CLTZ:
        {
            const TU8 tpOPIC1_CLTZ[] = {
                0x11,0xA0,0x88,0x88, //addi r10 r0 0x8888
                0xC1,0xAA,0x00,0x00, //cltz r10 r10        // r10 < 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1

                0x11,0xA0,0x00,0x88, //addi r10 r0 0x0088
                0xC1,0xAA,0x00,0x00, //cltz r10 r10        // r10 < 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIC1_CLTZ, sizeof(tpOPIC1_CLTZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIC3_CNEZ:
        {
            const TU8 tpOPIC3_CNEZ[] = {
                0x11,0xA0,0x88,0x88, //addi r10 r0 0x8888
                0xC3,0xAA,0x00,0x00, //cnez r10 r10        // r10 != 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1

                0x11,0xA0,0x00,0x88, //addi r10 r0 0x0088
                0xC3,0xAA,0x00,0x00, //cnez r10 r10        // r10 != 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIC3_CNEZ, sizeof(tpOPIC3_CNEZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIC4_CEQZ:
        {
            const TU8 tpOPIC4_CEQZ[] = {
                0x11,0xA0,0x00,0x00, //addi r10 r0 0x0
                0xC4,0xAA,0x00,0x00, //ceqz r10 r10        // r10 == 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1

                0x11,0xA0,0x00,0x88, //addi r10 r0 0x0088
                0xC4,0xAA,0x00,0x00, //ceqz r10 r10        // r10 == 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIC4_CEQZ, sizeof(tpOPIC4_CEQZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIC6_CGTZ:
        {
            const TU8 tpOPIC6_CGTZ[] = {
                0x11,0xA0,0x88,0x88, //addi r10 r0 0x8888
                0xC6,0xAA,0x00,0x00, //cgtz r10 r10        // r10 < 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                0x11,0xA0,0x00,0x88, //addi r10 r0 0x0088
                0xC6,0xAA,0x00,0x00, //cgtz r10 r10        // r10 < 0 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0xFF,0xFF, //addi r10 r10 -1
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIC6_CGTZ, sizeof(tpOPIC6_CGTZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIDD_MOV:
        {
            const TU8 tpOPIDD_MOV[] =
            {
                0x1E,0xA0,0x27,0x10, //li r10 10000
                0xDD,0xBA,0x00,0x00, //mov r11, r10      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11

            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIDD_MOV, sizeof(tpOPIDD_MOV));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPID0_INI:
        {
            const TU8 tpOPID0_INI[] =
            {
                0x1E,0xA0,0x27,0x10, //li r10 10000
                0xDD,0xBA,0x00,0x00, //mov r11, r10
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11
                0xD0,0xB0,0x00,0x00, //ini r11           //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x32,0xA0,0xA0,0xB0, //sub r10 r10 r11
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPID0_INI, sizeof(tpOPID0_INI));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIDE_NEG:
        {
            const TU8 tpOPIDE_NEG[] =
            {
                0x11,0xA0,0x27,0x10, //addi r10 r0 10000
                0xDE,0xAA,0x00,0x00, //neg r10 r10      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xDE,0xAA,0x00,0x00, //neg r10 r10      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x12,0xAA,0x27,0x10, //subi r10 r10 10000

            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIDE_NEG, sizeof(tpOPIDE_NEG));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIDF_NOT:
        {
            const TU8 tpOPIDF_NOT[] = {
                0x11,0xAA,0x56,0x78, //addi r10 r10 0x5678
                0xDF,0xAA,0x00,0x00, //not r10 r10       //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xDF,0xAA,0x00,0x00, //not r10 r10       //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x12,0xAA,0x56,0x78, //subi r10 r10 0x5678
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIDF_NOT, sizeof(tpOPIDF_NOT));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;
#endif

#ifdef TEST_MEMORY_16
        case OPS51_WB: // + LB
        {
            const TU8 tpOPS51_WB[] = {
                0x11,0xA0,0x00,0x66, //addi r10 r0 0x0066   //  r10     = $66
                0x51,0xA0,0x00,0x00, //wb r10 (r0+0)        //  [r0+0] b= r10  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xA1,0xB0,0x00,0x00, //lb r11 (r0+0)        //  r11    b= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xBA,0x00,0x22, //addi r11 r10 0x0022  //  r10     = r11 + $22
                0x11,0x11,0x00,0x01, //addi r1 r1 1         //  r1     ++
                0x51,0xB1,0x00,0x00, //wb r11 r1+0          //  [r1+0] b= r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                0xA1,0xA1,0x00,0x00, //lb r10 (r1+0)        //  r10    b= [r1+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xA1,0xB0,0x00,0x00, //lb r11 (r0+0)        //  r11    b= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x31,0xA0,0xA0,0xB0, //add r10 r10 11       //  r10    += r11

                0x11,0xAA,0x10,0x00, //addi r10 r0 0x1000   //  r10    += $1000
                0x12,0xAA,0x0F,0xEE, //subi r10 r10 $0FEE   //  r10    -= $0FEE
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS51_WB, sizeof(tpOPS51_WB));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPS52_WH: // + LH
        {
            const TU8 tpOPS52_WH[] = {
                0x11,0xA0,0x66,0x66, //addi r10 r0 0x6666   //  r10     = $6666
                0x52,0xA0,0x00,0x00, //wh r10 (r0+0)        //  [r0+0] h= r10 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xA2,0xB0,0x00,0x00, //lh r11 (r0+0)        //  r11    h= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xBA,0x22,0x22, //addi r11 r10 0x2222  //  r10     = r11 + $2222
                0x11,0x11,0x00,0x02, //addi r1 r1 2         //  r1     += 2
                0x52,0xB1,0x00,0x00, //wh r11 r1+0          //  [r1+0] h= r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                0xA2,0xA1,0x00,0x00, //lh r10 (r1+0)        //  r10    h= [r1+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xA2,0xB0,0x00,0x00, //lh r11 (r0+0)        //  r11    h= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x31,0xA0,0xA0,0xB0, //add r10 r10 11       //  r10    += r11

                0x11,0xAA,0x70,0x00, //addi r10 r0 0x7000   //  r10    += $7000
                0x12,0xAA,0x5E,0xEE, //subi r10 r10 $5EEE   //  r10    -= $5EEE
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS52_WH, sizeof(tpOPS52_WH));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPS54_WW: // + LW
        {
            const TU8 tpOPS54_WW[] = {
                0x11,0xA0,0x66,0x66, //addi r10 r0 0x6666   //  r10      = $6666
                0x16,0xAA,0x00,0x08, //slli r10 r10 8       //  r10    <<= 8
                0x54,0xA0,0x00,0x00, //ww r10 (r0+0)        //  [r0+0]   = r10 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xA4,0xB0,0x00,0x00, //lw r11 (r0+0)        //  r11      = [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xBA,0x22,0x22, //addi r11 r10 0x2222  //  r11      = r10 + $2222
                0x11,0x11,0x00,0x04, //addi r1 r1 4         //  r1      += 4
                0x54,0xB1,0x00,0x00, //ww r11 r1+0          //  [r1+0]   = r11 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                0xA4,0xA1,0x00,0x00, //lw r10 (r1+0)        //  r10      = [r1+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xA4,0xB0,0x00,0x00, //lw r11 (r0+0)        //  r11      = [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x31,0xA0,0xA0,0xB0, //add r10 r10 11       //  r10     += r11

                0x17,0xAA,0x00,0x08, //srli r0 r0 8         //  r10    >>= 8

                0x12,0xAA,0x70,0x00, //addi r10 r0 0x7000   //  r10 -= $7000
                0x12,0xAA,0x5C,0xEE, //subi r10 r10 $5CEE   //  r10 -= $5CEE
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS54_WW, sizeof(tpOPS54_WW));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIAB_LBU:
        {
            const TU8 tpOPIAB_LBU[] = {
                0x11,0xA0,0x00,0x66, //addi r10 r0 0x0066   //  r10      = $66
                0x51,0xA0,0x00,0x00, //wb r10 (r0+0)        //  [r0+0]  b= r10
                0xAB,0xB0,0x00,0x00, //lbu r11 (r0+0)       //  r11    ub= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xBA,0x00,0x22, //addi r11 r10 0x0022  //  r10      = r11 + $22
                0x11,0x11,0x00,0x01, //addi r1 r1 1         //  r1      ++
                0x51,0xB1,0x00,0x00, //wb r11 r1+0          //  [r1+0]  b= r11

                0xAB,0xA1,0x00,0x00, //lbu r10 (r1+0)       //  r10    ub= [r1+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xAB,0xB0,0x00,0x00, //lbu r11 (r0+0)       //  r11    ub= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x31,0xA0,0xA0,0xB0, //add r10 r10 11       //  r10     += r11

                0x11,0xAA,0x10,0x00, //addi r10 r0 0x1000   //  r10    += $1000
                0x12,0xAA,0x10,0xEE, //subi r10 r10 $10EE   //  r10    -= $10EE
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIAB_LBU, sizeof(tpOPIAB_LBU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPIAD_LHU:
        {
            const TU8 tpOPIAD_LHU[] = {
                0x11,0xA0,0x66,0x66, //addi r10 r0 0x6666   //  r10     = $6666
                0x52,0xA0,0x00,0x00, //wh r10 (r0+0)        //  [r0+0] h= r10
                0xAD,0xB0,0x00,0x00, //lhu r11 (r0+0)       //  r11   uh= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xBA,0x22,0x22, //addi r11 r10 0x2222  //  r10     = r11 + $2222
                0x11,0x11,0x00,0x02, //addi r1 r1 2         //  r1     += 2
                0x52,0xB1,0x00,0x00, //wh r11 r1+0          //  [r1+0] h= r11

                0xAD,0xA1,0x00,0x00, //lhu r10 (r1+0)       //  r10   uh= [r1+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0xAD,0xB0,0x00,0x00, //lhu r11 (r0+0)       //  r11   uh= [r0+0] //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x31,0xA0,0xA0,0xB0, //add r10 r10 11       //  r10    += r11

                0x12,0xAA,0x70,0x00, //subi r10 r10 $7000   //  r10    -= $7000
                0x12,0xAA,0x7E,0xEE, //subi r10 r10 $7EEE   //  r10    -= $7EEE
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPIAD_LHU, sizeof(tpOPIAD_LHU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;
#endif

#ifdef TEST_BRANCHES
        case OPSB1_BLT:
        {
            const TU8 tpOPSB1_BLT[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x2000   //  r12     = $2000
                0xB1,0xBC,0x00,0x01, //blt r11 r12 1        //  if (r11 < r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x11,0xC0,0x10,0x00, //addi r12 r0 0x1000   //  r12     = $1000
                0xB1,0xBC,0x00,0x01, //blt r11 r12 1        //  if (r11 < r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x00,0x04, //addi r13 r0 4        //  r13     = 4
                0x11,0xE0,0x00,0x07, //addi r17 r0 7        //  r14     = 7
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //addi r13 r13 1       //  r10    += 1
                0xB1,0xDE,0xFF,0xFD, //blt r13 r14 -3       // until (r13 < r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x66,0x66, //subi r10 r10 $6666   //  r10    -= $6666
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSB1_BLT, sizeof(tpOPSB1_BLT));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSB2_BLE:
        {
            const TU8 tpOPSB2_BLE[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x2000   //  r12     = $2000
                0xB2,0xBC,0x00,0x01, //ble r11 r12 1        //  if (r11 <= r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x1000   //  r12     = $2000
                0xB2,0xBC,0x00,0x01, //ble r11 r12 1        //  if (r11 <= r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x00,0x04, //addi r13 r0 4        //  r13     = 4
                0x11,0xE0,0x00,0x07, //addi r17 r0 7        //  r14     = 7
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //addi r13 r13 1       //  r10    += 1
                0xB2,0xDE,0xFF,0xFD, //ble r13 r14 -3       // until (r13 <= r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x55,0x55, //subi r10 r10 $5555   //  r10    -= $5555
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSB2_BLE, sizeof(tpOPSB2_BLE));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSB3_BNE:
        {
            const TU8 tpOPSB3_BNE[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x2000   //  r12     = $2000
                0xB3,0xBC,0x00,0x01, //bne r11 r12 1        //  if (r11 != r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xD0,0x00,0x04, //addi r13 r0 4        //  r13     = 4
                0x11,0xE0,0x00,0x07, //addi r17 r0 7        //  r14     = 7
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //addi r13 r13 1       //  r10    += 1
                0xB3,0xDE,0xFF,0xFD, //bne r13 r14 -3       // until (r13 != r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x44,0x44, //subi r10 r10 $4444   //  r10    -= $4444
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSB3_BNE, sizeof(tpOPSB3_BNE));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSB4_BEQ:
        {
            const TU8 tpOPSB4_BEQ[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x2000   //  r12     = $2000
                0xB4,0xBC,0x00,0x01, //beq r11 r12 1        //  if (r11 == r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x2000   //  r12     = $2000
                0xB4,0xBC,0x00,0x01, //beq r11 r12 1        //  if (r11 == r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x22,0x22, //addi r10 r0 0x2222   //  r10     = $2222

                0x12,0xAA,0x22,0x22, //subi r10 r10 $2222   //  r10    -= $2222
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSB4_BEQ, sizeof(tpOPSB4_BEQ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSB5_BGE:
        {
            const TU8 tpOPSB5_BGE[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x11,0xC0,0x10,0x00, //addi r12 r0 0x1000   //  r12     = $1000
                0xB5,0xBC,0x00,0x01, //bge r11 r12 1        //  if (r11 >= r12) then +1 ((!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x1000   //  r12     = $2000
                0xB5,0xBC,0x00,0x01, //bge r11 r12 1        //  if (r11 >= r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x00,0x07, //addi r13 r0 7        //  r13     = 7
                0x11,0xE0,0x00,0x04, //addi r17 r0 4        //  r14     = 4
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x12,0xDD,0x00,0x01, //subi r13 r13 1       //  r10    -= 1
                0xB5,0xDE,0xFF,0xFD, //bge r13 r14 -3       // until (r13 >= r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x55,0x55, //subi r10 r10 $5555   //  r10    -= $5555
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSB5_BGE, sizeof(tpOPSB5_BGE));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSB6_BGT:
        {
            const TU8 tpOPSB6_BGT[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x11,0xC0,0x10,0x00, //addi r12 r0 0x1000   //  r12     = $1000
                0xB6,0xBC,0x00,0x01, //bgt r11 r12 1        //  if (r11 > r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x11,0xC0,0x20,0x00, //addi r12 r0 0x1000   //  r12     = $2000
                0xB6,0xBC,0x00,0x01, //bgt r11 r12 1        //  if (r11 > r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x00,0x07, //addi r13 r0 7        //  r13     = 7
                0x11,0xE0,0x00,0x04, //addi r17 r0 4        //  r14     = 4
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x12,0xDD,0x00,0x01, //subi r13 r13 1       //  r10    -= 1
                0xB6,0xDE,0xFF,0xFD, //bgt r13 r14 -3       // until (r13 > r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x66,0x66, //subi r10 r10 $6666   //  r10    -= $6666
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSB6_BGT, sizeof(tpOPSB6_BGT));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSBA_BLTU:
        {
            const TU8 tpOPSBA_BLTU[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x90,0x00, //addi r12 r0 0x9000   //  r12     = $9000
                0xBA,0xBC,0x00,0x01, //bltu r11 r12 1       //  if (r11 U< r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x90,0x00, //addi r11 r0 0x9000   //  r11     = $9000
                0x11,0xC0,0x10,0x00, //addi r12 r0 0x1000   //  r12     = $1000
                0xBA,0xBC,0x00,0x01, //bltu r11 r12 1       //  if (r11 U< r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x90,0x04, //addi r13 r0 $9004    //  r13     = $9004
                0x11,0xE0,0x90,0x07, //addi r17 r0 $9007    //  r14     = $9007
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //addi r13 r13 1       //  r10    += 1
                0xBA,0xDE,0xFF,0xFD, //bltu r13 r14 -3      // until (r13 U< r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x66,0x66, //subi r10 r10 $6666   //  r10    -= $6666
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSBA_BLTU, sizeof(tpOPSBA_BLTU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSBB_BLEU:
        {
            const TU8 tpOPSBB_BLEU[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x90,0x00, //addi r12 r0 0x9000   //  r12     = $9000
                0xBB,0xBC,0x00,0x01, //bleu r11 r12 1       //  if (r11 U<= r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x90,0x00, //addi r11 r0 0x9000   //  r11     = $9000
                0x11,0xC0,0x10,0x00, //addi r12 r0 0x1000   //  r12     = $1000
                0xBB,0xBC,0x00,0x01, //bleu r11 r12 1       //  if (r11 U<= r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x90,0x04, //addi r13 r0 $9004    //  r13     = $9004
                0x11,0xE0,0x90,0x07, //addi r17 r0 $9007    //  r14     = $9007
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //addi r13 r13 1       //  r10    += 1
                0xBB,0xDE,0xFF,0xFD, //bleu r13 r14 -3      // until (r13 U<= r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x77,0x77, //subi r10 r10 $7777   //  r10    -= $7777
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSBB_BLEU, sizeof(tpOPSBB_BLEU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSBC_BGEU:
        {
            const TU8 tpOPSBC_BGEU[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x90,0x00, //addi r11 r0 0x2000   //  r11     = $9000
                0x11,0xC0,0x10,0x00, //addi r12 r0 0x1000   //  r12     = $1000
                0xBC,0xBC,0x00,0x01, //bgeu r11 r12 1        //  if (r11 U>= r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x90,0x00, //addi r12 r0 0x9000   //  r12     = $9000
                0xBC,0xBC,0x00,0x01, //bgeu r11 r12 1       //  if (r11 U>= r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x90,0x07, //addi r13 r0 $9007    //  r13     = $9007
                0x11,0xE0,0x90,0x04, //addi r17 r0 $9004    //  r14     = $9004
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x12,0xDD,0x00,0x01, //subi r13 r13 1       //  r10    -= 1
                0xBC,0xDE,0xFF,0xFD, //bgeu r13 r14 -3      // until (r13 U>= r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x77,0x77, //subi r10 r10 $7777   //  r10    -= $7777
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSBC_BGEU, sizeof(tpOPSBC_BGEU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPSBD_BGTU:
        {
            const TU8 tpOPSBD_BGTU[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x90,0x00, //addi r11 r0 0x2000   //  r11     = $9000
                0x11,0xC0,0x10,0x00, //addi r12 r0 0x1000   //  r12     = $1000
                0xBD,0xBC,0x00,0x01, //bgtu r11 r12 1        //  if (r11 U> r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xA0,0x11,0x11, //addi r10 r0 0x1111   //  r10     = $1111

                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x11,0xC0,0x90,0x00, //addi r12 r0 0x9000   //  r12     = $9000
                0xBD,0xBC,0x00,0x01, //bgtu r11 r12 1       //  if (r11 U> r12) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x90,0x07, //addi r13 r0 $9007    //  r13     = $9007
                0x11,0xE0,0x90,0x04, //addi r17 r0 $9004    //  r14     = $9004
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x12,0xDD,0x00,0x01, //subi r13 r13 1       //  r10    -= 1
                0xBD,0xDE,0xFF,0xFD, //bgtu r13 r14 -3      // until (r13 U> r14) then -3 //!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x66,0x66, //subi r10 r10 $6666   //  r10    -= $6666
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPSBD_BGTU, sizeof(tpOPSBD_BGTU));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;
#endif

#ifdef TEST_BRANCHES_ZERO
        case OPS81_BLTZ:
        {
            const TU8 tpOPS81_BLTZ[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x90,0x00, //addi r11 r0 0x9000   //  r11     = $9000
                0x81,0xB0,0x00,0x01, //bltz r11 +1          //  if (r11 < 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x11,0x11, //addi r10 r0 0x1111   //  r10    += $1111

                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x81,0xB0,0x00,0x01, //bltz r11 +1          //  if (r11 < 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x12,0xD0,0x00,0x04, //subi r13 r0 4        //  r13     = -4
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //addi r13 r13 1       //  r10    += 1
                0x81,0xD0,0xFF,0xFD, //bltz r13 -3          // until (r13 < 0) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x77,0x77, //subi r10 r10 $7777   //  r10    -= $7777
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS81_BLTZ, sizeof(tpOPS81_BLTZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPS82_BLEZ:
        {
            const TU8 tpOPS82_BLEZ[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x90,0x00, //addi r11 r0 0x9000   //  r11     = $9000
                0x82,0xB0,0x00,0x01, //blez r11 +1          //  if (r11 <= 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x11,0x11, //addi r10 r0 0x1111   //  r10    += $1111

                0x11,0xB0,0x00,0x00, //addi r11 r0 0x0      //  r11     = $0
                0x82,0xB0,0x00,0x01, //blez r11 +1          //  if (r11 <= 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x12,0xD0,0x00,0x04, //subi r13 r0 4        //  r13     = -4
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xDD,0x00,0x01, //addi r13 r13 1       //  r10    += 1
                0x82,0xD0,0xFF,0xFD, //blez r13 -3          // until (r13 <= 0) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x66,0x66, //subi r10 r10 $6666   //  r10    -= $6666
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS82_BLEZ, sizeof(tpOPS82_BLEZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPS83_BNEZ:
        {
            const TU8 tpOPS83_BNEZ[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x83,0xB0,0x00,0x01, //bnez r11 1           //  if (r11 != 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x11,0x11, //addi r10 r0 0x1111   //  r10    += $1111

                0x11,0xD0,0x00,0x04, //addi r13 r0 4        //  r13     = 4
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x12,0xDD,0x00,0x01, //subi r13 r13 1       //  r10    -= 1
                0x83,0xDE,0xFF,0xFD, //bnez r13 r14 -3      // until (r13 != 0) then -3 //!!!!!!!!!!!!!!!!!!!!!!!!!

                0x12,0xAA,0x55,0x55, //subi r10 r10 $5555   //  r10    -= $5555
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS83_BNEZ, sizeof(tpOPS83_BNEZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPS84_BEQZ:
        {
            const TU8 tpOPS84_BEQZ[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x00,0x00, //addi r11 r0 0x0      //  r11     = $0
                0x84,0xB0,0x00,0x01, //beqz r11 1           //  if (r11 == 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x11,0x11, //addi r10 r0 0x1111   //  r10    += $1111

                0x11,0xB0,0x10,0x00, //addi r11 r0 0x1000   //  r11     = $1000
                0x84,0xB0,0x00,0x01, //beqz r11 1        //  if (r11 == 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r0 0x2222   //  r10    += $2222

                0x12,0xAA,0x33,0x33, //subi r10 r10 $3333   //  r10    -= $3333
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS84_BEQZ, sizeof(tpOPS84_BEQZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPS85_BGEZ:
        {
            const TU8 tpOPS85_BGEZ[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x85,0xB0,0x00,0x01, //bgez r11 1           //  if (r11 >= 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111

                0x11,0xB0,0x00,0x00, //addi r11 r0 0x0      //  r11     = $0
                0x85,0xB0,0x00,0x01, //bgez r11 1           //  if (r11 >= 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x00,0x04, //addi r13 r0 4        //  r13     = 4
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x12,0xDD,0x00,0x01, //subi r13 r13 1       //  r10    -= 1
                0x85,0xD0,0xFF,0xFD, //bgez r13 -3          // until (r13 >= 0) then -3 (BACK 3 instructions)

                0x12,0xAA,0x66,0x66, //subi r10 r10 $6666   //  r10    -= $6666
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS85_BGEZ, sizeof(tpOPS85_BGEZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        case OPS86_BGTZ:
        {
            const TU8 tpOPS86_BGTZ[] = {
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x11,0xB0,0x20,0x00, //addi r11 r0 0x2000   //  r11     = $2000
                0x86,0xB0,0x00,0x01, //bgtz r11 1           //  if (r11 > 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111

                0x11,0xB0,0x20,0x00, //subi r11 r0 0x2000   //  r11     = -$2000
                0x86,0xB0,0x00,0x01, //bgtz r11 1           //  if (r11 > 0) then +1 //!!!!!!!!!!!!!!!!!!!!!!!!!!!
                0x11,0xAA,0x22,0x22, //addi r10 r10 0x2222  //  r10    += $2222

                0x11,0xD0,0x00,0x04, //addi r13 r0 4        //  r13     = 4
                // ??? some markup instruction ???          // repeat:
                0x11,0xAA,0x11,0x11, //addi r10 r10 0x1111  //  r10    += $1111
                0x12,0xDD,0x00,0x01, //subi r13 r13 1       //  r10    -= 1
                0x86,0xD0,0xFF,0xFD, //bgtz r13 -3          // until (r13 > 0) then -3 (BACK 3 instructions)

                0x12,0xAA,0x55,0x55, //subi r10 r10 $5555   //  r10    -= $5555
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPS86_BGTZ, sizeof(tpOPS86_BGTZ));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;
#endif

#ifdef TEST_SYS_JR_JALR
        //TODO
        //ecall


        //TODO
        //ebreak


        case OPI40_FENCE:
        {
            const TU8 tpOPI40_FENCE[] =
            {
                0x40,0x00,0x00,0x00, //fence = nop
            };
            memset(&core, 0, sizeof(core));
            testresult = vmex(tpOPI40_FENCE, sizeof(tpOPI40_FENCE));
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;
        }
        break;


        //TODO
        //xgoto


        //TODO
        //xcall


        //TODO
        //fcall


        //TODO
        //ftail
#endif

#ifdef TEST_MEMORY_32
#endif

        default:
            testresult = 1;
            printf("%d : %s\n", testresult, testname); if (testresult!=0) return 1;

    }

    return 0;
}

#endif

