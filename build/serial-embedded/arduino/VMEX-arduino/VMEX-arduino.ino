//#define RUN_TESTS
//#define CONSOLE

//microchip XC8 license monthly �41
//https://www.microchip.com/en-us/development-tool/SW006021-SUB#


#include "VMEX.h"

#ifndef ARDUINO
int main()
{
    #ifndef RUN_TESTS
    TU8 testprog[] =
    {

        0x11,0x10,0x00,0x00, //addi r1 r0 0 //reorder registers in binary encoding "I" as first target !!!
        0x11,0x10,0x05,0x00, //addi r1 r0 5
        0x11,0x11,0x04,0x00, //addi r1 r1 4
        0x11,0x20,0x03,0x00, //addi r2 r0 3
        0xF1,0x10,0x00,0x00, //wb r1 0(r0)  //let stay registers as first SOURCE, second INDEX, (third is immediate offset)
        0xF1,0x20,0x01,0x00, //wb r2 1(r0)
        0x32,0x10,0x10,0x20, //sub r1 r1 r2 //reorder registers in binary encoding "R" as first target !!!
        0x11,0x22,0x04,0x00, //addi r2 r2 4
        0x32,0x10,0x10,0x20, //sub r1 r1 r2
        //0x11,0x30,0xFF,0x00, //addi r3 r0 $FF
        //0x34,0x10,0x10,0x30,  //and r1 r1 r3
        //0x11,0x40,0x00,0x30, //addi r4 r0 $3000
        //0x35,0x10,0x10,0x40,  //or r1 r1 r4
        //0x33,0x10,0x10,0x30,  //xor r1 r1 r3
        //0x16,0x11,0x10,0x00, //slli r1 r1 16
        //0x17,0x11,0x18,0x00, //slri r1 r1 24
        //0xF1,0x10,0x02,0x00, //wb r1 2(r0)  //let stay registers as first SOURCE, second INDEX, (third is immediate offset)
        //0xF1,0x10,0x03,0x00, //wb r1 3(r0)
        //
        //0xA1,0x80,0x00,0x00, //lb r8 0(r0)  //let stay registers as first SOURCE, second INDEX, (third is immediate offset)
        //0xA1,0x90,0x01,0x00, //lb r9 1(r0)
        //0x32,0x80,0x80,0x90, //sub r8 r8 r9
        //0x11,0x22,0x01,0x00, //addi r2 r2 1
        //0x32,0x80,0x80,0x20, //sub r8 r8 r2
        //0x32,0x90,0x90,0x20, //sub r9 r9 r2
        //0xF1,0x80,0x02,0x00, //wb r8 2(r0)  //let stay registers as first SOURCE, second INDEX, (third is immediate offset)
        //0xF1,0x90,0x03,0x00, //wb r9 3(r0)
        //0xAB,0xA0,0x02,0x00, //lbu rA 2(r0)  //let stay registers as first SOURCE, second INDEX, (third is immediate offset)
        //0xAB,0xB0,0x03,0x00, //lbu rB 3(r0)
        //0xA1,0xC0,0x02,0x00, //lb rC 2(r0)  //let stay registers as first SOURCE, second INDEX, (third is immediate offset)
        //0xA1,0xD0,0x03,0x00, //lb rD 3(r0)
        
    };
    
    return vmex(testprog, sizeof(testprog));

    #else
    return runtests();
    #endif

} //main
#endif




#include "arduino.h"
#include "console.h"


#define PAGE_SIZE (32)
#define PROG_SIZE (PAGE_SIZE * 1)
#define DATA_SIZE (PAGE_SIZE * 1)


// Define core struct
typedef struct
{
    REGS_TYPE regs[16];
    TU8 rsvd[42*4]; //reserved (msg in/out buffers, breakpoints)
    PC_TYPE pc;
    TU8 data[DATA_SIZE];
    TU8 prog[PROG_SIZE];
} __attribute__((aligned(4))) Core;

Core core = {
    {0}, // initialize regs to all zeroes
    {0}, // initialize rsvd to all zeroes
    0,   // initialize pc to zero
    {0}, // initialize data to all zeroes
    {0}  // initialize prog to all zeroes
};




//main
int vmex(const TU8 testprog[], int progsize)
{
    TU8 opcode = 0;
    TU8 rs1 = 0;
    TU8 rs2 = 0;
    TU8 rd = 0;
    IMMS_TYPE imm = 0;
    
    //temp debug
    TS32 r10i = 0;
//    TU32 r10u;
//    TS32 r11i;
//    TU32 r11u;
    
    //fill program
    memcpy(core.prog, testprog, progsize);
    core.pc = 0;
    
    while (core.pc < progsize)
    {
        
        //parameters parsing
        TU8 *_op_ = &core.prog[core.pc];
        opcode = *_op_;                       //opcode = core.prog[core.pc];
        switch (opcode & 0xF0)
        {
            case R3_TYPE:
            case R2_TYPE:
            case RC_TYPE:
            case RD_TYPE:
            {
                rd  = _op_[1] >> 4;
                rs1 = _op_[2] >> 4;
                rs2 = _op_[3] >> 4;
                break;
            }
            
            case I1_TYPE:
            case IA_TYPE:
            case I4_TYPE:
            case IE_TYPE:
            {
                rd  = _op_[1] >> 4;
                rs1 = _op_[1] & 0xF;
                imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly
                break;
            }
            
            case SF_TYPE:
            case SB_TYPE:
            case S8_TYPE:
            {
                rs1 = _op_[1] >> 4;
                rs2 = _op_[1] & 0xF;
                imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly
                break;
            }
            
            case U7_TYPE:
            case U6_TYPE:
            {
                rd  = _op_[1] >> 4;
                imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly
                break;
            }
            
            case UNKNOWN_TYPE:
            default:
            println("Unknown opcode type");
            break;
        }



        //instruction execution
        REGS_TYPE *_reg_ = core.regs;
        switch (opcode)
        {
            //R-TYPE ----------------------------------------------------------------------------
            case OPR31_ADD:
            _reg_[rd] = (REGS_TYPE) _reg_[rs1] + (REGS_TYPE) _reg_[rs2];
            break;

            case OPR32_SUB:
            _reg_[rd] = (REGS_TYPE) _reg_[rs1] - (REGS_TYPE) _reg_[rs2];
            break;

            case OPR33_XOR:
            _reg_[rd] = _reg_[rs1] ^ _reg_[rs2];
            break;

            case OPR34_AND:
            _reg_[rd] = _reg_[rs1] & _reg_[rs2];
            break;

            case OPR35_OR:
            _reg_[rd] = _reg_[rs1] | _reg_[rs2];
            break;

            case OPR36_SLL:
            _reg_[rd] = _reg_[rs1] << (_reg_[rs2] & 0x1F);
            break;

            case OPR37_SRL:
            _reg_[rd] = (REGU_TYPE) _reg_[rs1] >> (_reg_[rs2] & 0x1F);
            break;

            case OPR38_SRA:
            _reg_[rd] = (REGS_TYPE)	 _reg_[rs1] >> (_reg_[rs2] & 0x1F);
            break;

            case OPR3A_CLT: //SLT
            _reg_[rd] = (REGS_TYPE)	 _reg_[rs1] < (REGS_TYPE) _reg_[rs2];
            break;

            case OPR3B_CLTU: //SLTU
            _reg_[rd] = (REGU_TYPE) _reg_[rs1] < (REGU_TYPE) _reg_[rs2];
            break;


            //I-TYPE ----------------------------------------------------------------------------
            case OPI11_ADDI:
            _reg_[rd] = (REGS_TYPE) _reg_[rs1] + (IMMS_TYPE) imm;
            break;

            case OPI12_SUBI: //pseudo
            _reg_[rd] = (REGS_TYPE) _reg_[rs1] - (IMMS_TYPE) imm;
            break;

            case OPI13_XORI:
            _reg_[rd] = _reg_[rs1] ^ ((IMMS_TYPE) imm & 0xFFFF);
            break;

            case OPI14_ANDI:
            _reg_[rd] = _reg_[rs1] & ((IMMS_TYPE) imm & 0xFFFF);
            break;

            case OPI15_ORI:
            _reg_[rd] = _reg_[rs1] | ((IMMS_TYPE) imm & 0xFFFF);
            break;

            case OPI16_SLLI:
            _reg_[rd] = _reg_[rs1] << ((IMMS_TYPE) imm & 0x1F);
            break;

            case OPI17_SRLI:
            _reg_[rd] = _reg_[rs1] >> ((IMMS_TYPE) imm & 0x1F);
            break;

            case OPI18_SRAI:
            _reg_[rd] = (REGS_TYPE) _reg_[rs1] >> ((IMMS_TYPE) imm & 0x1F);
            break;

            case OPI1A_CLTI: //SLTI
            _reg_[rd] = (REGS_TYPE) _reg_[rs1] < (IMMS_TYPE) imm;
            break;

            case OPI1B_CLTIU: //SLTIU
            _reg_[rd] = (REGU_TYPE) _reg_[rs1] < (REGU_TYPE) imm;
            break;

            //DATA MEMORY ACCESS ---------------------------------------------------------------
            case OPIA1_LB:
            {
                TU8 *ptr = &core.data[_reg_[rs1] + imm];
                _reg_[rd] = *(TS8 *)ptr;
                break;
            }

            //TEST
            case OPIA2_LH:
            {
                TU8 *ptr = &core.data[_reg_[rs1] + imm];
                _reg_[rd] = *(TS16 *)ptr;
                break;
            }
            //TEST
            case OPIA4_LW:
            {
                TU8 *ptr = &core.data[_reg_[rs1] + imm];
                _reg_[rd] = *(TS32 *)ptr;
                break;
            }

            case OPIAB_LBU:
            {
                TU8 *mem_ptr = &core.data[_reg_[rs1] + imm];
                _reg_[rd] = *(TU8 *)mem_ptr;
                break;
            }
            
            //TEST
            case OPIAD_LHU:
            {
                TU8 *mem_ptr = &core.data[_reg_[rs1] + imm];
                _reg_[rd] = *(TU16 *)mem_ptr;
                break;
            }


            //TEST JALR, ECALL, BREAK -----------------------------------------------------------
            case OPI4F_JALR:
            _reg_[rd] = core.pc + 4;
            core.pc = (_reg_[rs1] + imm) & ~0x1;
            break;

            //TEST
            case OPI42_ECALL:
            case OPI48_EBREAK:
            if (imm == 0) {
                // Execute the system call
                println("System call!");
                } else if (imm == 1) {
                // Execute the break instruction
                println("Breakpoint!");
                } else {
                println("Unknown instruction");
            }
            break;


            //DATA MEMORY FLUSH ---------------------------------------------------------------
            case OPSF1_WB: //SB
            {
                TU8 *ptr = &core.data[_reg_[rs2] + imm];
                *(TU8 *)ptr = (TU8)(_reg_[rs1] & 0xFF);
                break;
            }

            //TEST
            case OPSF2_WH: //SH
            {
                TU8 *ptr = &core.data[_reg_[rs2] + imm];
                *(TU16 *)ptr = (TU16)(_reg_[rs1] & 0xFFFF);
                break;
            }

            //TEST
            case OPSF4_WW: //SW
            {
                TU8 *ptr = &core.data[_reg_[rs2] + imm];
                *(TU32 *)ptr = _reg_[rs1];
                break;
            }

            //BRANCHES ---------------------------------------------------------------------
            case OPSB1_BLT:
            if ((REGS_TYPE)	 _reg_[rs1] < (REGS_TYPE) _reg_[rs2]) {
                core.pc += imm;
            }
            break;
            
            case OPSB2_BLE:
            break;
            
            case OPSB3_BNE:
            if (_reg_[rs1] != _reg_[rs2]) {
                core.pc += imm;
            }
            break;
            
            case OPSB4_BEQ:
            if (_reg_[rs1] == _reg_[rs2]) {
                core.pc += imm;
            }
            break;

            case OPSB5_BGE:
            if ((REGS_TYPE) _reg_[rs1] >= (REGS_TYPE) _reg_[rs2]) {
                core.pc += imm;
            }
            break;

            case OPSB6_BGT:
            break;

            case OPSBA_BLTU:
            if ((REGU_TYPE) _reg_[rs1] < (REGU_TYPE) _reg_[rs2]) {
                core.pc += imm;
            }
            break;
            
            case OPSBB_BLEU:
            break;
            
            case OPSBC_BGEU:
            if ((REGU_TYPE) _reg_[rs1] >= (REGU_TYPE) _reg_[rs2]) {
                core.pc += imm;
            }
            break;

            case OPSBD_BGTU:
            break;

            
            // LUI? AUIPC, JAL ---------------------------------------------------------------
            case OPU71_LUI:
            _reg_[rd] = (REGU_TYPE) (imm << IMM_BITS);
            break;

            case OPU7A_AUIPC:
            _reg_[rd] = ((REGU_TYPE) (imm << IMM_BITS)) + core.pc;
            break;

            case OPU7F_JAL:
            _reg_[rd] = core.pc + 4;
            core.pc += imm;
            break;


            default:
            print("Unknown opcode: "); println(itoh(opcode));
            break;
        }

        r10i = _reg_[10];
//        r10u = _reg_[10];
//        r11i = _reg_[11];
//        r11u = _reg_[11];
        
        core.pc+=4; // Increment the PC

        print("PC: "); println(itoh(core.pc)); //TODO DEBUG
    }

    return r10i;
}


#include "tests.h"
