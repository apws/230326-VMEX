/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2014 - 2021 SEGGER Microcontroller GmbH             *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* - Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File      : SEGGER_RISCV_crt0.s
Purpose   : Generic runtime init startup code for RISC-V CPUs.
            Designed to work with the SEGGER linker to produce 
            smallest possible executables.
            
            This file does not normally require any customization.

Additional information:
  Preprocessor Definitions
    FULL_LIBRARY
      If defined then 
        - argc, argv are set up by calling SEGGER_SEMIHOST_GetArgs().
        - the exit symbol is defined and executes on return from main.
        - the exit symbol calls destructors, atexit functions and then
          calls SEGGER_SEMIHOST_Exit().
    
      If not defined then
        - argc and argv are not valid (main is assumed to not take parameters)
        - the exit symbol is defined, executes on return from main and
          halts in a loop.
*/

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
#ifndef   APP_ENTRY_POINT
  #define APP_ENTRY_POINT main
#endif

#ifndef   ARGSSPACE
  #define ARGSSPACE 128
#endif

/*********************************************************************
*
*       Macros
*
**********************************************************************
*/
//
// Declare a label as function symbol (without switching sections)
//
.macro MARK_FUNC Name
        .global \Name
        .type \Name, function
\Name:
.endm

//
// Declare a regular function.
// Functions from the startup are placed in the init section.
//
.macro START_FUNC Name
        .section .init.\Name, "ax"
        .global \Name
#if __riscv_compressed
        .balign 2
#else
        .balign 4
#endif
        .type \Name, function
\Name:
.endm

//
// Declare a weak function
//
.macro WEAK_FUNC Name
        .section .init.\Name, "ax", %progbits
        .global \Name
        .weak \Name
#if __riscv_compressed
        .balign 2
#else
        .balign 4
#endif
        .type \Name, function
\Name:
.endm

//
// Mark the end of a function and calculate its size
//
.macro END_FUNC name
        .size \name,.-\name
.endm

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/
        .extern APP_ENTRY_POINT     // typically main

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _start
*
*  Function description
*    Entry point for the startup code. 
*    Usually called by the reset handler.
*    Performs all initialisation, based on the entries in the 
*    linker-generated init table, then calls main().
*    It is device independent, so there should not be any need for an 
*    end-user to modify it.
*
*  Additional information
*    At this point, the stack pointer should already have been 
*    initialized 
*      - by hardware (such as on Cortex-M),
*      - by the device-specific reset handler,
*      - or by the debugger (such as for RAM Code).
*/
#undef L
#define L(label) .L_start_##label

START_FUNC _start
        .option push
        .option norelax
        lui     gp,     %hi(__global_pointer$)
        addi    gp, gp, %lo(__global_pointer$)
        lui     tp,     %hi(__thread_pointer$)
        addi    tp, tp, %lo(__thread_pointer$)
        lui     t0,     %hi(__stack_end__)
        addi    sp, t0, %lo(__stack_end__)
        .option pop        
        la      a0, trap_entry
        csrw    mtvec, a0
        csrw    mcause, zero

#ifndef __NO_SYSTEM_INIT
        //
        // Call _init
        //
        call    _init
#endif
        //
        // Call linker init functions which in turn performs the following:
        // * Perform segment init
        // * Perform heap init (if used)
        // * Call constructors of global Objects (if any exist)
        //
        la      s0, __SEGGER_init_table__       // Set table pointer to start of initialization table
L(RunInit): 
        lw      a0, (s0)                        // Get next initialization function from table
        add     s0, s0, 4                       // Increment table pointer to point to function arguments
        jalr    a0                              // Call initialization function
        j       L(RunInit)
        //
MARK_FUNC __SEGGER_init_done
        //
        // Time to call main(), the application entry point.
        //
#ifndef FULL_LIBRARY
        //
        // In a real embedded application ("Free-standing environment"), 
        // main() does not get any arguments,
        // which means it is not necessary to init a0 and a1.
        //
        call    APP_ENTRY_POINT
        tail    exit

END_FUNC _start
        //
        // end of _start
        // Fall-through to exit if main ever returns.
        //
MARK_FUNC exit
        //
        // In a free-standing environment, if returned from application:
        // Loop forever.
        //
        j       .
        .size exit,.-exit
#else
        //
        // In a hosted environment, 
        // we need to load a0 and a1 with argc and argv, in order to handle 
        // the command line arguments.
        // This is required for some programs running under control of a 
        // debugger, such as automated tests.
        //
        li      a0, ARGSSPACE
        la      a1, args
        call    SEGGER_SEMIHOST_GetArgs
        la      a1, args

        call    APP_ENTRY_POINT                 // Call to application entry point (usually main())
        call    exit                            // Call exit function
        j       .                               // If we unexpectedly return from exit, hang.
END_FUNC _start
#endif

        // 
#ifdef FULL_LIBRARY
/*********************************************************************
*
*       exit
*
*  Function description
*    Exit of the system.
*    Called on return from application entry point or explicit call 
*    to exit.
*
*  Additional information
*    In a hosted environment exit gracefully, by
*    saving the return value,
*    calling destructurs of global objects, 
*    calling registered atexit functions, 
*    and notifying the host/debugger.
*/
#undef L
#define L(label) .L_exit_##label

WEAK_FUNC exit
        mv      s1, a0                          // Save the exit parameter/return result
        //
        // Call destructors
        //
        la      s0, __dtors_start__
L(Loop):
        la      t0, __dtors_end__
        beq     s0, t0, L(End)
        lw      t1, 0(s0)
        addi    s0, s0, 4  
        jalr    t1  
        j       L(Loop)
L(End):
        //
        // Call atexit functions
        //
        call    __SEGGER_RTL_execute_at_exit_fns
        //
        // Call debug_exit with return result/exit parameter
        //
        mv      a0, s1
        call    SEGGER_SEMIHOST_Exit
        //
        // If execution is not terminated, loop forever
        //
L(ExitLoop):
        j       L(ExitLoop)                     // Loop forever.
END_FUNC exit
#endif

#ifdef FULL_LIBRARY
        .bss
args:
        .space ARGSSPACE
        .size args, .-args
        .type args, %object
#endif
  
/*************************** End of file ****************************/
