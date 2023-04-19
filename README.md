# VMEX

RV32EM assembly compatible embedded engine based on RISC-V.

This is experimental RISC-V inspired/mapped ISA optimized for software decoding even on 8bit machines.
VMEX follows RV32E, so 16 registers only but allows 16bit immediates (12bit planned as optional compat mode).
Encoding of branch and jump instructions uses also 16bit immediates, shifted by 2 to address only words.
All this more supports 8/16 bit target embeddeed MCUs to be coded directly in modified high level assembly.
It is intentionally NOT implementing compressed ISA, as decoder here is too complex for purpose and size.
To the contrary, implemented are mapped pseudo instructions and compound 32 bit "fusions" will be optimized too
(in total cca 80 instructions, half of which are optimized pseudos and fusions).
Currently it contains only single core but will allow more cores with separate adress spaces, messaging only
through single hub. Monitor features are still in design too, mostly related to multi-core.
Intended are specific builds for individual MCUs, providing UART and GPIO support inside.

Licensee is intentionally restrictive now, but this will change to something more open too.
Features are still subject to change, including ISA encoding and mnemonics tweaks.

Build is tested using latest Dev-Cpp, MPLAB X (XC8,XC16,XC32), Segger Embedded Studio for RISC-V, cc65, z88dk.
Engine itself has under 4kB for now, but planned full-featured size is 8kB max.
This is only reference implementation in portable C which will be adapted also to "unsafe" C#.
Planned high-level assembler targeting VMEX (but also native MCUs) is inteded to be used for reimplementing engine in it.

All implemented tests are now passing down to cc65. For z88dk (SDCC) there are still bugs in multiplier but it compiles. The same is true for qdos-gcc targeting Sinclair QL (M68000). Currently this template compiles and is running on windows
(Dev-Cpp), in RISC-V simulator (Segger), for 6502 (cc65) on AtariXL, C64, C128, Plus/4, for Z80 (z88dk/sdcc) on Sinclair ZX Spectrum, for M68000 on Sinclair QL (qdoc-gcc), or various MPLAB X supported MCUs (AVR, PIC16/18/24/C32, ARM Cortex M) in simulator and devkits, for MSP430 in simulator and devkits, and compiles(untested) for Z80/8085 (z88dk/sccz80) for CP/M, MSX, SordM5, Tandy100/Olivetti M10 (8085), Ondra, PMD-85 ... Simple windows build scripts will be provided here too soon.
Biggest challenge was till now docker/wsl2 powered build for Sinclair QL :-). Now is the time of fixing bugs found by tests and specification of multicore operation which will deffer from RISC-V. There will be no CSSRS, no shared memory, no locks. All is targeted to specify primitives for structured concurrency basics.

More docs to come here too, sure.
