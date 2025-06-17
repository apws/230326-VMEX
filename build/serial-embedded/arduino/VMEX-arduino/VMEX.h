
//changes
//230326a - ordered any code related to instructions by James Zho refcard, renumbered opcodes !!!
//          James Zho refcard contains all instruction descriptions related to "C", also all pseudoinstructions
//          we also have noted our syntax for SLT SLTU SLTUI as CLT CLTU CLTUI (Compare, not confused with Shift)
//          we will also propose our syntax for branches (probably J instead of B) and jumps/call (GOTO RGOTO and CALL RCALL)
//          the J instead of B because probably we instroduce BIT manipulation pseudoinstruction BIS BIC BIT set/clear/toggle,test !!!
//          we will also similar way provide our syntax tweaks to pseudoinstructions
//          according to ASLIX draft code, we can also introduce some table load/save and branch auto pre/post inc/dec pseudoinstructions
//          and we can also introduce some HLA looping pseudoinstruciton sets: repeat loop while until and if then
//230326b - reordered opcode defines and code, renamed defines to include full opcode, extended TYPES to R1,R2,I1,I2,S1,S2,U1,U2
//(particulary R2 will be used for "M" extension, others are RESERVED)
//possible also regrouping ABI registers to have "upper" 8 gp regs as 0-7 and "lower" as 8-F (8=zero,9=ra,A=sp,B=gp) ??? SPIS NE

#define PC_TYPE       TU32  //RV32=TU32

#define IMM_BITS        16  //VMEX=16 //RV32=12
#define IMM_MASK    0xFFFF
#define IMMS_TYPE     TS16  //RV32=
#define IMMU_TYPE     TU16  //RV32=

#define REGS_TYPE     TS32  //RV32=TS32
#define REGU_TYPE     TU32  //







#include <stdint.h>
#include <string.h>

#ifdef RUN_TESTS
    #include <stdio.h>
#endif


//mixworx types
typedef uint64_t  TU64;
typedef int64_t   TS64;
typedef uint32_t  TU32;
typedef int32_t   TS32;
typedef uint16_t  TU16;
typedef int16_t   TS16;
typedef uint8_t   TU8;
typedef int8_t    TS8;
//typedef bool      TBOOL;
typedef char      TCHAR; //??




// ==============
//   RV32E/VMEX - YES we will implement RV32E 32bit instructions
// ==============

// SEGGER IDE described along with complete RISC-V ISA description - especially DEBUGGER / ASSEMBLY operation !!!!!!
// https://www.udemy.com/course/riscv-isa/learn/lecture/27222084#overview

// !!! for commercial usage of VMEX, consider subscription to mixworx VMEX paid support !!!

// (pseudo/fusions T=5689CDE)


// R3-TYPE (16)
// R2-TYPE (16)
// RC-TYPE (16)
//   = ADD=31, SUB=32, XOR=33, AND=34, OR=35, SLL=36, SRL=37, SRA=38,
//   ( = MUL=21, MULH=22, MULHU=23, DIV=24, DIVU=25, REM=26, REMU=27, - is "M" extension)
//   = CLT=3A, CLTU=3B
// 31                              0
//  -------+-------+-------+-------+
//  rs2|000|rs1|000|-rd|000|0010cccc
//  -------+-------+-------+-------+

// I1-TYPE (16)
// IA-TYPE (16)
// ID-TYPE (16)
// I4-TYPE (16)
// IE-TYPE (16)
//   = ADDI=11, (SUBI=12) XORI=13, ANDI=14, ORI=15, SLLI=16, SRLI=17, SRAI=18
//   = CLTI=1A, CLTIU=1B
//   = LB=A1, LH=A2, LW=A4, LBU=AB, LHU=AD
//   = JALR=4F (imm < 1) ???
//   = ESYS=42 (ECALL, EBREAK)  //42 48
//   = FENCE=40 (NOP, ignored)
// 31                              0
//  -------+-------+-------+-------+
//  -sx|--immediate|-rd|rs1|0011cccc
//  -------+-------+-------+-------+

// SF-TYPE (16)
// SB-TYPE (16)
// S8-TYPE (16)
//   = SB=F1, SH=F2, SW=F4
//   = BEQ=B1, BNE=B2, BLT=B3, BGE=B4, BLTU=B5, BGEU=B6 (13 bits encoded as SRRed 12 bits !!!) ... +/- 4kB
// 31                              0
//  -------+-------+-------+-------+
//  -sx|--immediate|rs1|rs2|0101cccc
//  -------+-------+-------+-------+

// U7-TYPE (16)
// U6-TYPE (16)
//   = LUI=71, AUIPC=7A, JAL=7F (both wraps around 24bit, JAL x0 +/-2kB)
// 31                              0
//  -------+-------+-------+-------+
//  -sx|--immediate|-rd|___|0111cccc
//  -------+-------+-------+-------+


// Define RV32E instruction format types
typedef enum {
    UNKNOWN_TYPE,

    R3_TYPE = 0x30,
    R2_TYPE = 0x20,
    RC_TYPE = 0xC0,
    RD_TYPE = 0xD0,
    
    I1_TYPE = 0x10,
    IA_TYPE = 0xA0,
    I4_TYPE = 0x40,
    IE_TYPE = 0xE0,

    SF_TYPE = 0xF0,
    SB_TYPE = 0xB0,
    S8_TYPE = 0x80,

    U7_TYPE = 0x70,
    U6_TYPE = 0x60,

    R9_TYPE = 0x90, //reserved
    R0_TYPE = 0x00, //reserved (NOP)

} InstructionFormatType;


//OP 00-NOP
#define OP00_NOP      0x00

//OP R3-TYPE
#define OPR31_ADD     0x31
#define OPR32_SUB     0x32
#define OPR33_XOR     0x33
#define OPR34_AND     0x34
#define OPR35_OR      0x35
#define OPR36_SLL     0x36
#define OPR37_SRL     0x37
#define OPR38_SRA     0x38
#define OPR3A_CLT     0x3A //SLT
#define OPR3B_CLTU    0x3B //SLTU
#define OPR3F_NOT     0x3F //pseudo
#define OPR3E_NEG     0x3E //pseudo

//OP R2-TYPE // "M" extension = multiply/divide

//OP RC-TYPE
#define OPRC1_CLTZ    0xC1 //pseudo
#define OPRC3_CNEZ    0cC3 //pseudo
#define OPRC4_CEQZ    0cC4 //pseudo
#define OPRC6_CGTZ    0cC6 //pseudo

//OP RD-TYPE
#define OPRDD_MV      0cDD //pseudo            //DF  //D4
#define OPRD1_MV1     0cD1 //pseudo //aslix    //DB  //D1
#define OPRD2_MV2     0cD2 //pseudo //aslix    //DD  //D2
//#define OPRD3_MV3     0cD3 //pseudo //aslix
//#define OPRD4_MV4     0cD4 //pseudo //aslix

//OP I3-TYPE
#define OPI11_ADDI    0x11
#define OPI12_SUBI    0x12 //pseudo
#define OPI13_XORI    0x13
#define OPI14_ANDI    0x14
#define OPI15_ORI     0x15
#define OPI16_SLLI    0x16
#define OPI17_SRLI    0x17
#define OPI18_SRAI    0x18
#define OPI1A_CLTI    0x1A //SLTI
#define OPI1B_CLTIU   0x1B //SLTIU
#define OPI1F_LI      0x1F //pseudo

//OP IA-TYPE
#define OPIA1_LB      0xA1
#define OPIA2_LH      0xA2
#define OPIA4_LW      0xA4
#define OPIAB_LBU     0xAB
#define OPIAD_LHU     0xAD

//OP I4-TYPE
#define OPI4F_JALR    0x4F
#define OPI42_ECALL   0x42
#define OPI48_EBREAK  0x48
#define OPI40_FENCE   0x40 //NOP=ignored
#define OPI46_XGOTO   0x46 //JR   //pseudo
#define OPI4C_XCALL   0x4C //JALR //pseudo
#define OPI44_RET     0x44 //pseudo

//OP IE-TYPE
#define OPIEC_FCALL   0xEC //CALL //pseudo
#define OPIE4_FTAIL   0xE4 //TAIL //pseudo
#define OPIEA_LA      0xEA //pseudo
#define OPIE1_LB      0xE1 //pseudo
#define OPIE2_LH      0xE2 //pseudo
#define OPIE4_LW      0xE4 //pseudo

//OP SF-TYPE
#define OPSF1_WB      0xF1 //SB
#define OPSF2_WH      0xF2 //SH
#define OPSF4_WW      0xF4 //SW

//OP SB-TYPE
#define OPSB1_BLT     0xB1
#define OPSB2_BLE     0xB2 //pseudo
#define OPSB3_BNE     0xB3
#define OPSB4_BEQ     0xB4
#define OPSB5_BGE     0xB5
#define OPSB6_BGT     0xB6 //pseudo
#define OPSBA_BLTU    0xBA
#define OPSBB_BLEU    0xBB //pseudo
#define OPSBC_BGEU    0xBC
#define OPSBD_BGTU    0xBD //pseudo

//OP S8-TYPE
#define OPS81_BLTZ    0x81 //pseudo
#define OPS82_BLEZ    0x82 //pseudo
#define OPS83_BNEZ    0x83 //pseudo
#define OPS84_BEQZ    0x84 //pseudo
#define OPS85_BGEZ    0x85 //pseudo
#define OPS86_BGTZ    0x86 //pseudo


//OP U7-TYPE
#define OPU71_LUI     0x71
#define OPU7A_AUIPC   0x7A
#define OPU7F_JAL     0x7F

//OP U6-TYPE
#define OPU66_GOTO    0x66 //J  //pseudo
#define OPU6C_CALL    0x6C //JL //pseudo




int vmex(const TU8 testprog[], int progsize);
int test(TU8 opcode, const char* testname);
int runtests();
