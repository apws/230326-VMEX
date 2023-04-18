/* Copyright (C) 2022, 2023 Petr Antos, AP-ware servis (mixworx.net) antos.petr@gmail.com - ALL RIGHTS RESERVED */

// !!! CHECK tests.h for list of errors !!!

#define RUN_TESTS     //compile and run tests in engine (/test arg or monitor t command)
//#define EMB_TESTS   //launch tests (selectivelly enabled by TEST_ #defines) immediatelly in main
//#define EMB_MAIN    //launch as vmexmain() from main.c/main() with MCU init - it is OK, no issues!!
#define DESKTOP       //instead od auto-detection, we explicitly define here compilation for desktops (QL)
#define PAGE_SIZE (4*32) //16 at least for tests (16 instructions test scripts)

//console
//#define LOADER      // absolute minimal loader part of monitor (load hex, flash, run, break, debug)
#define MONITOR       // complete monitor including diassebly, assembly
//#define ASLIX       // high level C-like/Python-like ASLIX assembler (symbols, C-operators, loop/again, comments)

#define CONSOLE       //not yet supported but will be part of the small/classic/aslix monitor
                      //goal is to support tiniest serial terminal but also allow larger ANSI/VT100-like
                      //(or at least CPlus/4-like PETSCII) terminal with control cursor commands (escape sequences).
                      //on embedded hardware the connection is GPIO powered SW UART by default
                      //on home computers its screen terminal module, linked to the VMEX (getch/putch only)
                      //bigger VMEX/ASLIX application can use full terminal interface, still the same way
                      //there will be NO spacial screen/keyboard access, only this unified terminal way
                      //so, effectivelly this means need to develop UNIFIED TERMINAL for all HC around...
                      //
                      //truth is, that OUR support will be probably 2 color/mono (fore/back, inverse) + cursor controls ONLY
                      //and standardized around basic ASCII subset, with probably custom loaded FONT to be exact everywhere
                      //
                      //will be good to follow operation of SALLY basic interpreter in relation to line terminal usage !!!
                      //llowing co copy/paste text outputs and to have them PASTEABLE back as inputs for simple save/load !!!
                      //
                      //in fact, minimal monitor will serve as bootloader too (Unlock,Lock,* set pc,Mem,Go)
                      //there will be built-in basic security - PIN to unlock monitor (10 tries counting down, then permanent lock)


//microchip XC8 license monthly ?41
//https://www.microchip.com/en-us/development-tool/SW006021-SUB#

//Mixworx SciTE configuration for syntax colored ASLIX
//https://uloz.to/file/hFgGAJbPd2sI/mixworx-scite-zip#!ZJZjAmR2A2LjMQN4ZJD5AQtkAwt3ZxymZzEGIJIwDKukEwx4ZD==


#include "VMEX.h"

#include "muldiv.h"
#include "console.h"
#include "arduino.h"

//try to follow things here... Modern C (as far as older compilers allow, ya)
//https://www.youtube.com/watch?v=QpAhX-gsHMs

// current core struct is only naive and not ready for multicore (but vmex code is transpaent by pointers)
// we need in core regs, pc and POINTERS to prog / data
// we need ability to allocate prog/data in RAM and map prog to flash
// cores in RAM (developemnt) and RAM/FLASH (deployment) 

#define PROG_SIZE (PAGE_SIZE * 1)
#define DATA_SIZE (PAGE_SIZE * 1)

// Define core struct
typedef struct
{
    REGS_TYPE regs[16];
    //TU8 rsvd[42 << 2]; //reserved (msg in/out buffers, breakpoints)
    PC_TYPE pc;
    TU8 data[DATA_SIZE];
    TU8 prog[PROG_SIZE];
} Core; //__attribute__((aligned(4))) Core; //dev-cpp fails on segfault !!!

Core core = {
    {0}, // initialize regs to all zeroes
    //{0}, // initialize rsvd to all zeroes //found bug here by z88dk +zx !!!
    0,   // initialize pc to zero
    {0}, // initialize data to all zeroes
    {0}  // initialize prog to all zeroes
};


#include "tests.h"
#include "monitor.h"


#ifndef ARDUINO

#ifdef EMB_MAIN
int vmexmain(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    char command[32];

    #ifdef EMB_TESTS

    int size_short = sizeof(short);
    int size_int   = sizeof(int);
    int size_long  = sizeof(long);
    
    printf("Size of short: %zu bytes\n", size_short);
    printf("Size of int: %zu bytes\n", size_int);
    printf("Size of long: %zu bytes\n", size_long);

    return runtests();
    #endif

    if (argc > 1 && strcmp(argv[1], "/test") == 0)
    {
        #ifdef RUN_TESTS
        return runtests();
        #else
        println("");
        println("  Tests are not compiled in this package.");
        #endif
    }
    else if (argc > 1 && strcmp(argv[1], "/?") == 0)
    {
        println("");
        cmd_version(&core);
        println("  /?    - help");
        println("  /test - tests");
        println("");
        println("  Without arguments is executed interactive VMEX monitor.");

    }
    else
    {
        #ifdef MONITOR

        println("");
        cmd_version(&core);
        println("  ? for help");

        while (1)
        {
            print("> ");
            input(command, sizeof(command));

            // Remove the newline character from the input
            command[strcspn(command, "\n")] = 0;


            if (strcmp(command, "t") == 0)
            {
                #ifdef RUN_TESTS
                runtests();
                #else
                println("");
                println("  Tests are not compiled in this package.");
                #endif
            }

            if (strcmp(command, "?") == 0)
            {
                cmd_help(&core);
            }

            if (strcmp(command, "q") == 0)
            {
                return 0;
            }

            if (strcmp(command, "v") == 0)
            {
                cmd_version(&core);
            }

            if (strcmp(command, "r") == 0)
            {
                cmd_registers(&core);
            }

            if (strcmp(command, "m") == 0)
            {
                cmd_memory(&core, 0, 14);
            }

            if (strcmp(command, "g") == 0)
            {
                cmd_go(&core);
            }

        }

        #else

        TU8 testprog[] =
        {
            0x11, 0xAA, 0x00, 0x01, // addi r10 r0 5
            0x11, 0xBB, 0x00, 0x0B, // addi r11 r0 5
            0x11, 0xCC, 0x00, 0x0C, // addi r12 r0 5
            0x11, 0xDD, 0x00, 0x0D, // addi r13 r0 5

            0x51, 0xD0, 0x00, 0x00, // wb r13 r0 0
            0x11, 0xDD, 0x00, 0x01, // addi r13 r13 1
            0x51, 0xD0, 0x00, 0x01, // wb r13 r0 1
            0x42, 0x00, 0x00, 0x00, // ecall
            0x48, 0x00, 0x00, 0x00, // ebreak
        };

        int result = vmex(testprog, sizeof(testprog));

        println("");
        print("  exit code: "); println(itoh(result,2));

        #endif

    }
}
#endif




//main
int vmex(const TU8 testprog[], int progsize)
{
    TU8 opcode = 0;
    TU8 rs1 = 0;
    TU8 rs2 = 0;
    TU8 rd = 0;
    IMMS_TYPE imm = 0;

    PC_TYPE pc = 0;

    //temp debug
    TS32 r10i = 0;


    Core* _core_ = &core;

    REGS_TYPE* _reg_ = _core_->regs;
    TU8* _prog_ = _core_->prog;
    TU8* _data_ = _core_->data;

    TU8* _op_;
    REGS_TYPE* _rd_;
    REGS_TYPE* _rs1_;
    REGS_TYPE* _rs2_;

    //fill program
    memcpy(_prog_, testprog, progsize);
    core.pc = 0;

    while (core.pc < progsize)
    {
        pc = core.pc;

        //parameters parsing
        _op_ = (TU8*)&_prog_[pc];
        opcode = *_op_;

        switch (opcode & 0xF0)
        {
            case R3_TYPE:
            case R2_TYPE:
            {
                rd  = _op_[1] >> 4;
                rs1 = _op_[2] >> 4;
                rs2 = _op_[3] >> 4;
                break;
            }

            case I1_TYPE:
            case IC_TYPE: //pseudo
            case ID_TYPE: //pseudo
            case IA_TYPE:
            case I4_TYPE:
            case IE_TYPE: //pseudo
            {
                rd  = _op_[1] >> 4;
                rs1 = _op_[1] & 0xF;
                imm = (_op_[2] << 8) | _op_[3];
                break;
            }

            case S5_TYPE:
            case SF_TYPE:
            case SB_TYPE:
            case S8_TYPE: //pseudo
            {
                rs1 = _op_[1] >> 4;
                rs2 = _op_[1] & 0xF;
                imm = (_op_[2] << 8) | _op_[3];
                break;
            }

            case U7_TYPE:
            case U6_TYPE: //pseudo
            {
                rd  = _op_[1] >> 4;
                imm = (_op_[2] << 8) | _op_[3];
                break;
            }

            case X9_TYPE:
            case X0_TYPE:
                //NOP + ASLIX HLL
                break;
        }


        _rd_ = &_reg_[rd];
        _rs1_ = &_reg_[rs1];
        _rs2_ = &_reg_[rs2];

        *_reg_ = 0; //r0 is always 0, may be changed by JAL by PC, or as a mistake r0 = something

        //instruction execution
        switch (opcode)
        {

            case OP00_NOP:
                break;



            //R-TYPE ----------------------------------------------------------------------------
            case OPR31_ADD:
                //_reg_[rd] = (REGS_TYPE) _reg_[rs1] + (REGS_TYPE) _reg_[rs2];
                *_rd_ = (REGS_TYPE) *_rs1_ + (REGS_TYPE) *_rs2_;
                break;

            case OPR32_SUB:
                *_rd_ = (REGS_TYPE) *_rs1_ - (REGS_TYPE) *_rs2_;
                break;

            case OPR33_XOR:
                *_rd_ = *_rs1_ ^ *_rs2_;
                break;

            case OPR34_AND:
                *_rd_ = *_rs1_ & *_rs2_;
                break;

            case OPR35_OR:
                *_rd_ = *_rs1_ | *_rs2_;
                break;

            case OPR36_SLL:
                *_rd_ = *_rs1_ << (*_rs2_ & 0x1F);
                break;

            case OPR37_SRL:
                *_rd_ = (REGU_TYPE) *_rs1_ >> (*_rs2_ & 0x1F);
                break;

            case OPR38_SRA:
                *_rd_ = (REGS_TYPE) *_rs1_ >> (*_rs2_ & 0x1F);
                break;

            case OPR3A_CLT: //SLT
                *_rd_ = (REGS_TYPE) *_rs1_ < (REGS_TYPE) *_rs2_;
                break;

            case OPR3B_CLTU: //SLTU
                *_rd_ = (REGU_TYPE) *_rs1_ < (REGU_TYPE) *_rs2_;
                break;


            #ifdef MULDIV
            //OP R2-TYPE // "M" extension = takes 20-40% (now combined, using TU64X, TS64X structs, 8bit C compatible)
            case OPR21_MUL:
                *_rd_ = mul(*_rs1_, *_rs2_);
                break;

            case OPR22_MULH:
                *_rd_ = mulh(*_rs1_, *_rs2_);
                break;

            case OPR23_MULHU:
                *_rd_ = mulhu(*_rs1_, *_rs2_);
                break;

            case OPR24_MULHSU:
                *_rd_ = mulhsu(*_rs1_, *_rs2_);
                break;

            case OPR25_DIV:
                *_rd_ = *_rs1_ / *_rs2_;
                break;

            case OPR26_DIVU:
                *_rd_ = (TU32)*_rs1_ / (TU32)*_rs2_;
                break;

            case OPR27_REM:
                *_rd_ = *_rs1_ % *_rs2_;
                break;

            case OPR28_REMU:
                *_rd_ = (TU32)*_rs1_ % (TU32)*_rs2_;
                break;
            #endif


            //I-TYPE ----------------------------------------------------------------------------
            case OPI11_ADDI:
                //*_rd_ = (REGS_TYPE) *_rs1_ + (IMMS_TYPE) imm;
                *_rd_ = (REGS_TYPE) (*_rs1_ + (REGS_TYPE) imm); //FIXED !!!
                break;

            case OPI12_SUBI: //pseudo
                //*_rd_ = (REGS_TYPE) *_rs1_ - (IMMS_TYPE) imm;
                *_rd_ = (REGS_TYPE) (*_rs1_ - (REGS_TYPE) imm); //POOR TEST?, FIXED !!!
                break;

            case OPI13_XORI:
                *_rd_ = *_rs1_ ^ ((IMMS_TYPE) imm & 0xFFFF);
                break;

            case OPI14_ANDI:
                *_rd_ = *_rs1_ & ((IMMS_TYPE) imm & 0xFFFF);
                break;

            case OPI15_ORI:
                *_rd_ = *_rs1_ | ((IMMS_TYPE) imm & 0xFFFF);
                break;

            case OPI16_SLLI:
                *_rd_ = *_rs1_ << ((IMMS_TYPE) imm & 0x1F);
                break;

            case OPI17_SRLI:
                *_rd_ = *_rs1_ >> ((IMMS_TYPE) imm & 0x1F);
                break;

            case OPI18_SRAI:
                *_rd_ = (REGS_TYPE) *_rs1_ >> ((IMMS_TYPE) imm & 0x1F);
                break;

            case OPI1A_CLTI: //SLTI
//                //TODO //DEBUG //CC65 //root cause => ADDI
//                x3 = (REGS_TYPE) *_rs1_; x4 = (IMMS_TYPE) imm;
//                printf("   rs1: %s ", itoh(x3,8)); printf("imm: %s", itoh(x4,8)); printf("\n");

                *_rd_ = (REGS_TYPE) *_rs1_ < (IMMS_TYPE) imm; //& 0xFFFF !! cc65 !! SOLVED???? IMMS_TYPE vs REGS_TYPE
                break;

            case OPI1B_CLTIU: //SLTIU
                *_rd_ = (REGU_TYPE) *_rs1_ < (REGU_TYPE) imm;
                break;


            //LOAD IMMEDIATE
            case OPI1E_LI: //pseudo //16bit //or 1F ??
                *_rd_ = (IMMS_TYPE) imm;
                break;

            case OPI1F_LI: //pseudo fusion
                //TODO LI 32bit LUI combined
                break;



            //COMPARE TO ZERO ---------------------------------------------------------------
            case OPIC1_CLTZ: //pseudo
                *_rd_ = (REGS_TYPE) *_rs1_ < 0;
                break;

            //case OPIC2_CLEZ: //pseudo

            case OPIC3_CNEZ: //pseudo
                *_rd_ = (REGS_TYPE) *_rs1_ != 0;
                break;

            case OPIC4_CEQZ: //pseudo
                *_rd_ = (REGS_TYPE) *_rs1_ == 0;
                break;

            //case OPIC5_CGEZ: //pseudo

            case OPIC6_CGTZ: //pseudo
                *_rd_ = (REGS_TYPE) *_rs1_ > 0;
                break;


            //MOV, INIT, UNARY ---------------------------------------------------------------
            case OPIDD_MOV: //pseudo //MV !!! vyjimecne, pseudo jako I-TYPE !!!
                *_rd_ = (REGS_TYPE) *_rs1_;
                break;

            case OPID0_INI: //pseudo //MV // ???????????????????? pouze rd !!! vyjimecne, pseudo jako I-TYPE !!!
                *_rd_ = 0;
                break;

            case OPIDE_NEG: //pseudo
                *_rd_ = 0 - (REGS_TYPE) *_rs1_; //rs1 !!! vyjimecne, pseudo jako I-TYPE!!!
                break;

            case OPIDF_NOT: //pseudo
                *_rd_ = *_rs1_ ^ 0xFFFFFFFF; //rs1 !!! standard, pseudo I-TYPE !!!
                break;


            //DATA MEMORY ACCESS ---------------------------------------------------------------
            case OPIA1_LB:
                { TU8* ptr = (TU8*)&_data_[*_rs1_ + imm]; *_rd_ = *(TS8*)ptr; }
                break;

            case OPIA2_LH:
                { TU8* ptr = (TU8*)&_data_[*_rs1_ + imm]; *_rd_ = *(TS16*)ptr; }
                break;

            case OPIA4_LW:
                { TU8* ptr = (TU8*)&_data_[*_rs1_ + imm]; *_rd_ = *(TS32*)ptr; }
                break;

            case OPIAB_LBU:
                { TU8* mem_ptr = (TU8*)&_data_[*_rs1_ + imm]; *_rd_ = *(TU8*)mem_ptr; }
                break;

            case OPIAD_LHU:
                { TU8* mem_ptr = (TU8*)&_data_[*_rs1_ + imm]; *_rd_ = *(TU16*)mem_ptr; }
                break;


            //INDIRECT JUMP, RETURN
            case OPI4F_JALR:
                *_rd_ = pc + 4; core.pc = (*_rs1_ + (imm << LSHIFT) - 4);  //& ~0x1; in RISCV !!!!!!!!!!!!!!!!!!!!
                break;


            //SYSTEM
            case OPI42_ECALL: //SYS imm = 0
                #ifdef CONSOLE
                println("  system call");
                #endif
                break;

            case OPI48_EBREAK: //SYS imm = 1
                #ifdef CONSOLE
                println("  breakpoint");
                #endif
                break;

            case OPI40_FENCE: //NOP, ignored
                  break;


            //96 ???
            case OPI46_IGOTO: //pseudo //JR
                core.pc = *_rs1_ - 4;                      //absolute register goto
                break;

            //9C ???
            case OPI4C_ICALL: //pseudo //JALR
                *_rd_ = pc + 4; core.pc = *_rs1_ - 4;      //absolute register call
                break;


            case OPI44_RET: //pseudo //RET
                core.pc = _reg_[1] - 4;                    //absolute register return (SP) - works for single level call only
                break;



            case OPIEC_FCALL: //pseudo //CALL
                //TODO
                break;

            case OPIEE_FTAIL: //pseudo //TAIL
                //TODO
                break;


            case OPIEA_LA: //pseudo (LI)
                //TODO
                break;

            case OPIEF_LA: //pseudo fusion
                //TODO
                break;

            case OPIE1_LB: //pseudo fusion
                //TODO
                break;

            case OPIE2_LH: //pseudo fusion
                //TODO
                break;

            case OPIE4_LW: //pseudo fusion
                //TODO
                break;

            case OPSF1_WB: //pseudo fusion
                //TODO
                break;

            case OPSF2_WH: //pseudo fusion
                //TODO
                break;

            case OPSF4_WW: //pseudo fusion
                //TODO
                break;


            //DATA MEMORY FLUSH ---------------------------------------------------------------
            case OPS51_WB: //SB
                { TU8* ptr = (TU8*)&_data_[*_rs2_ + imm]; *(TU8*)ptr = (TU8)(*_rs1_ & 0xFF); }
                break;

            case OPS52_WH: //SH
                { TU8* ptr = (TU8*)&_data_[*_rs2_ + imm]; *(TU16*)ptr = (TU16)(*_rs1_ & 0xFFFF); }
                break;

            case OPS54_WW: //SW
                { TU8* ptr = (TU8*)&_data_[*_rs2_ + imm]; *(TU32*)ptr = *_rs1_; }
                break;


            //BRANCHES ---------------------------------------------------------------------
            case OPSB1_BLT:
                if ((REGS_TYPE) *_rs1_ < (REGS_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSB2_BLE: //pseudo
                if ((REGS_TYPE) *_rs1_ <= (REGS_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSB3_BNE:
                if (*_rs1_ != *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSB4_BEQ:
                if (*_rs1_ == *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSB5_BGE:
                if ((REGS_TYPE) *_rs1_ >= (REGS_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSB6_BGT: //pseudo
                if ((REGS_TYPE) *_rs1_ > (REGS_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;


            case OPSBA_BLTU:
                if ((REGU_TYPE) *_rs1_ < (REGU_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSBB_BLEU: //pseudo
                if ((REGU_TYPE) *_rs1_ <= (REGU_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSBC_BGEU:
                if ((REGU_TYPE) *_rs1_ >= (REGU_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;

            case OPSBD_BGTU: //pseudo
                if ((REGU_TYPE) *_rs1_ > (REGU_TYPE) *_rs2_) { core.pc += imm << LSHIFT; }
                break;


            case OPS81_BLTZ: //pseudo
                if ((REGS_TYPE) *_rs1_ < 0) { core.pc += imm << LSHIFT; }
                break;

            case OPS82_BLEZ: //pseudo
                if ((REGS_TYPE) *_rs1_ <= 0) { core.pc += imm << LSHIFT; }
                break;

            case OPS83_BNEZ: //pseudo
                if ((REGS_TYPE) *_rs1_ != 0) { core.pc += imm << LSHIFT; }
                break;

            case OPS84_BEQZ: //pseudo
                if ((REGS_TYPE) *_rs1_ == 0) { core.pc += imm << LSHIFT; }
                break;

            case OPS85_BGEZ: //pseudo
                if ((REGS_TYPE) *_rs1_ >= 0) { core.pc += imm << LSHIFT; }
                break;

            case OPS86_BGTZ: //pseudo
                if ((REGS_TYPE) *_rs1_ > 0) { core.pc += imm << LSHIFT; }
                break;


            // LUI, AUIPC, JAL ---------------------------------------------------------------
            case OPU71_LUI:
                *_rd_ = ((REGU_TYPE)imm << IMM_BITS); //TODO //TEST
                break;

            case OPU7A_AUIPC:
                *_rd_ = ((REGU_TYPE)imm << IMM_BITS) + pc; //TODO //TEST
                break;

            case OPU7F_JAL: // !!!! IMMEDIATE HERE POSSIBLY 20 BITS, NOT NOW, WE USE STRICT 16bit FIELD !!!!
                *_rd_ = pc + 4; core.pc += imm << LSHIFT; //& ~0x1; in RISCV !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                break;


            //GOTO, CALL
            case OPU66_GOTO: //pseudo // !!!! IMMEDIATE HERE POSSIBLY 20 BITS, NOT NOW, WE USE STRICT 16bit FIELD !!!!
                core.pc += imm << LSHIFT; //& ~0x1; in RISCV !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                break;

            case OPU6C_CALL: //pseudo // !!!! IMMEDIATE HERE POSSIBLY 20 BITS, NOT NOW, WE USE STRICT 16bit FIELD !!!!
                _reg_[1] = pc + 4; core.pc += imm << LSHIFT; //& ~0x1; in RISCV !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                break;



            default:
                #ifdef CONSOLE
                print("Unknown opcode: "); println(itoh(opcode, 1));
                #endif
                break;
        }

        r10i = _reg_[10];

        core.pc+=4;   //in absolute register jumps its corrected by - 4

        #ifdef CONSOLE
        //print("PC: "); println(itoh(core.pc, 4)); //TODO DEBUG
        #endif
    }

    return r10i;
}

