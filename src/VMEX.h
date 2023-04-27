/* Copyright (C) 2022, 2023 Petr Antos, AP-ware servis (mixworx.net) antos.petr@gmail.com - ALL RIGHTS RESERVED */

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
//          (particulary R2 will be used for "M" extension, others are RESERVED)
//          possible also regrouping ABI registers to have "upper" 8 gp regs as 0-7 and "lower" as 8-F (8=zero,9=ra,A=sp,B=gp) ??? SPIS NE
//230403  - current state of ASLIX is defined mostly be VMEX engine written it itself, we will follow this syntax
//          most important: 
//          1) single instruciton per line 2)
//          2) C-like operators 
//          3) C-like control (having loop(if)/again(if) instead of while/do)
//          4) Python-like space-defined structure, no semicolons


//vmex
#define PC_TYPE       TU32  // RV32=TU32
#define IMM_BITS        16  // VMEX=16 //RV32=12
#define IMM_MASK    0xFFFF
#define IMMS_TYPE     TS16  // RV32=
#define IMMU_TYPE     TU16  // RV32=
#define REGS_TYPE     TS32  // RV32=TS32
#define REGU_TYPE     TU32  //
#define LSHIFT           2  // VMEX=2 RV32E=1 (Bxx only - JAL JALR use masking of bit 0 to 0)
//#define IMM_SIGMAG          // signed-magnitude immediates (16bit = flag, 15:0 = abs value)



#include <stdbool.h>
#include <string.h>

//mixworx types
#ifdef TYPES_STDINT
#include <stdint.h>
typedef uint32_t  TU32;
typedef int32_t   TS32;
typedef uint16_t  TU16;
typedef int16_t   TS16;
typedef uint8_t   TU8;
typedef int8_t    TS8;
#endif

#ifdef TYPES_8
typedef unsigned long   TU32;
typedef signed long     TS32;
typedef unsigned short  TU16;
typedef signed short    TS16;
typedef unsigned char   TU8;
typedef signed char     TS8;
#endif

#ifdef TYPES_32
typedef unsigned int    TU32;
typedef signed int      TS32;
typedef unsigned short  TU16;
typedef signed short    TS16;
typedef unsigned char   TU8;
typedef signed char     TS8;
#endif


//typedef bool      TBOOL;
typedef char      TCHAR; //??


int vmex(const TU8 testprog[], int progsize);



// ==============
//   RV32E/VMEX - YES we will implement ONLY RV32E 32bit instructions, NOT compressed ones (too difficult, costly)
// ==============

// SEGGER IDE described along with complete RISC-V ISA description - especially DEBUGGER / ASSEMBLY operation !!!!!!
// https://www.udemy.com/course/riscv-isa/learn/lecture/27222084#overview

// !!! for commercial usage of VMEX, consider subscription to mixworx VMEX paid support !!!
// licensing? what exactly, how to do it? ask GPT4 ...



// R3-TYPE
// R2-TYPE
//   = ADD=31, SUB=32, XOR=33, AND=34, OR=35, SLL=36, SRL=37, SRA=38,
//   = MUL=21, MULH=22, MULHU=23, MULHSU=24, DIV=25, DIVU=26, REM=27, REMU=28, - is "M" extension
//   = CLT=3A, CLTU=3B
// 31                              0
//  -------+-------+-------+-------+
//  rs2|000|rs1|000|-rd|000|ttttcccc
//  -------+-------+-------+-------+


// I1-TYPE
// IA-TYPE
// IC-TYPE ?? only 16 or more registers to encode ?? R-TYPE ??
// ID-TYPE ?? only 16 or more registers to encode ?? R-TYPE ??
// I4-TYPE
// IE-TYPE
//   = ADDI=11, (SUBI=12) XORI=13, ANDI=14, ORI=15, SLLI=16, SRLI=17, SRAI=18
//   = CLTI=1A, CLTIU=1B
//   = LB=A1, LH=A2, LW=A4, LBU=AB, LHU=AD
//   = JALR=4F (imm < 1) ???
//   = ESYS=42 (ECALL, EBREAK)  //42 48
//   = FENCE=40 (NOP, ignored)
// 31                              0
//  -------+-------+-------+-------+
//  -L-immediate-H-|-rd|rs1|ttttcccc
//  -------+-------+-------+-------+


// S5-TYPE
// SF-TYPE
// SB-TYPE
// S8-TYPE
//   = SB=F1, SH=F2, SW=F4
//   = BEQ=B1, BNE=B2, BLT=B3, BGE=B4, BLTU=B5, BGEU=B6 (13 bits encoded as SRRed 12 bits !!!) ... +/- 4kB
// 31                              0
//  -------+-------+-------+-------+
//  -L-immediate-H-|rs1|rs2|ttttcccc
//  -------+-------+-------+-------+


// U7-TYPE
// U6-TYPE
//   = LUI=71, AUIPC=7A, JAL=7F (both wraps around 24bit, JAL x0 +/-2kB) !!!! IMMEDIATE HERE POSSIBLY 20 BITS !!!!
// 31                              0
//  -------+-------+-------+-------+
//  -L-immediate-H-|-rd|___|ttttcccc
//  -------+-------+-------+-------+



// Define RV32E instruction format types
typedef enum {
    R3_TYPE = 0x30,
    R2_TYPE = 0x20,
    
    I1_TYPE = 0x10,
    IC_TYPE = 0xC0, //?? only 16 or more registers to encode ?? R-TYPE ??
    ID_TYPE = 0xD0, //?? only 16 or more registers to encode ?? R-TYPE ??
    IA_TYPE = 0xA0,
    I4_TYPE = 0x40,
    IE_TYPE = 0xE0,

    S5_TYPE = 0x50,
    SF_TYPE = 0xF0, //$FF for invalid instruction (empty flash)
    SB_TYPE = 0xB0,
    S8_TYPE = 0x80,

    U7_TYPE = 0x70,
    U6_TYPE = 0x60,

    X9_TYPE = 0x90, //reserved
    X0_TYPE = 0x00 //reserved (NOP)

} InstructionFormatType;


//!!! in total 80 ( incl. "M") instructions IMPLEMENTED in optimized VMEX/RV32E runitme, incl. optimized "pseudos" !!!

//OP 00-NOP
#define OP00_NOP      0x00


//OP R3-TYPE
#define OPR31_ADD     0x31                                                 // -- registers
#define OPR32_SUB     0x32
#define OPR33_XOR     0x33
#define OPR34_AND     0x34
#define OPR35_OR      0x35
#define OPR36_SLL     0x36
#define OPR37_SRL     0x37
#define OPR38_SRA     0x38
#define OPR3A_CLT     0x3A //SLT
#define OPR3B_CLTU    0x3B //SLTU

//OP R2-TYPE // "M" extension = multiply/divide
#define OPR21_MUL     0x21                                                 // -- "M" multiply / divide
#define OPR22_MULH    0x22
#define OPR23_MULHU   0x23
#define OPR24_MULHSU  0x24
#define OPR25_DIV     0x25
#define OPR26_DIVU    0x26
#define OPR27_REM     0x27
#define OPR28_REMU    0x28

//OP I3-TYPE
#define OPI11_ADDI    0x11                                                 // -- immediates
#define OPI12_SUBI    0x12 //pseudo
#define OPI13_XORI    0x13
#define OPI14_ANDI    0x14
#define OPI15_ORI     0x15
#define OPI16_SLLI    0x16
#define OPI17_SRLI    0x17
#define OPI18_SRAI    0x18
#define OPI1A_CLTI    0x1A //SLTI
#define OPI1B_CLTIU   0x1B //SLTIU

#define OPI1E_LI      0x1E //pseudo //16bit
#define OPI1F_LI      0x1F //TODO //pseudo //LUI+ORI combined (fusion)???

//OP IC-TYPE
#define OPIC1_CLTZ    0xC1 //pseudo                                        // -- compare to 0 (optimized)
//#define OPIC2_CLEZ    0xC2 //pseudo //aslix?
#define OPIC3_CNEZ    0xC3 //pseudo
#define OPIC4_CEQZ    0xC4 //pseudo
//#define OPIC5_CGEZ    0xC5 //pseudo //aslix?
#define OPIC6_CGTZ    0xC6 //pseudo

//OP ID-TYPE
#define OPIDD_MOV     0xDD //pseudo //MV                                   // -- moves, inits, unary
#define OPID0_INI     0xD0 //pseudo //MV (optimized 0)
#define OPIDE_NEG     0xDE //pseudo    
#define OPIDF_NOT     0xDF //pseudo    

//#define OPRD1_MV1     0cD1 //pseudo //aslix    //DB  //D1 //move byte 
//#define OPRD2_MV2     0cD2 //pseudo //aslix    //DD  //D2 //move dual byte (H)
//#define OPRD3_MV3     0cD3 //pseudo //aslix //move third byte ??? aslix??
//#define OPRD4_MV4     0cD4 //pseudo //aslix //move fourth byte ??? aslix??

//OP IA-TYPE
#define OPIA1_LB      0xA1                                                 // -- MEM loads/access
#define OPIA2_LH      0xA2
#define OPIA4_LW      0xA4
#define OPIAB_LBU     0xAB
#define OPIAD_LHU     0xAD

//OP I4-TYPE
#define OPI4F_JALR    0x4F                                                 // -- indirects, system
#define OPI42_ECALL   0x42
#define OPI48_EBREAK  0x48
#define OPI40_FENCE   0x40 //NOP=ignored //0
#define OPI46_IGOTO   0x46 //pseudo //JALR //JR      //96 ???
#define OPI4C_ICALL   0x4C //pseudo //JALR           //9C ???
#define OPI44_RET     0x44 //pseudo

//OP IE-TYPE
#define OPIEC_FCALL   0xEC //pseudo //CALL //AUIPC+JALR                    // -- FAR MEM loads, symbols, calls
#define OPIEE_FTAIL   0xEE //pseudo //TAIL //AUIPC+JALR  //E6 ??

#define OPIEA_LA      0xEA //TODO pseudo 16 bit (defacto dtto k LI 16bit)
#define OPIEF_LA      0xEF //TODO pseudo //auipc combined (fusion)???

#define OPIE1_LB      0xE1 //TODO pseudo //auipc combined (fusion)???  
#define OPIE2_LH      0xE2 //TODO pseudo //auipc combined (fusion)???
#define OPIE4_LW      0xE4 //TODO pseudo //auipc combined (fusion)???



//OP S5-TYPE
#define OPS51_WB      0x51 //SB                                            // -- MEM writes/saves
#define OPS52_WH      0x52 //SH
#define OPS54_WW      0x54 //SW

//OP SF-TYPE
#define OPSF1_WB      0xF1 //TODO pseudo //auipc combined (fusion)???      // -- FAR MEM writes/flushes
#define OPSF2_WH      0xF2 //TODO pseudo //auipc combined (fusion)???
#define OPSF4_WW      0xF4 //TODO pseudo //auipc combined (fusion)???
#define OPSFF_INVALID 0xFF //TODO invalid instruction in empty flash ??? or NOP ???

//OP SB-TYPE
#define OPSB1_BLT     0xB1                                                 // -- branches
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
#define OPS81_BLTZ    0x81 //pseudo                                        // -- branches by 0
#define OPS82_BLEZ    0x82 //pseudo
#define OPS83_BNEZ    0x83 //pseudo
#define OPS84_BEQZ    0x84 //pseudo
#define OPS85_BGEZ    0x85 //pseudo
#define OPS86_BGTZ    0x86 //pseudo



//OP U7-TYPE                          - in fact 20bit immediate ???
#define OPU71_LUI     0x71                                                 // -- FAR fusions, jumps, calls
#define OPU7A_AUIPC   0x7A
#define OPU7F_JAL     0x7F

//OP U6-TYPE
#define OPU66_GOTO    0x66 //pseudo //JAL //J
#define OPU6C_CALL    0x6C //pseudo //JAL



// MORE PRACTICAL PSEUDO/FUSIONS (=optimized)

// PHB PHH PHW //stack //pseudo fusions? = addi sp, sp, -N; wN rx, 0(sp);
// PLB PLH PLW //stack //pseudo fusions? = lN rx, 0(sp); addi sp, sp, N;
// or support arbitrary PH/PL of number of bytes !!!