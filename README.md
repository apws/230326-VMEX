# VMEX

RV32EM assembly compatible embedded engine.

This is experimental RISC-V inspired/mapped ISA optimized for software decoding even on 8bit machines.
VMEX follows RV32E, so 16 registers only but allows 16bit immediates (12bit planned as optional compat mode).
Encoding of branch and jump instructions uses also 16bit immediates, shifted by 2 to address only words.
All this more supports 8/16 bit target embeddeed MCUs to be coded directly in modified high level assembly.
It is intentionally NOT implementing compressed ISA, as decoder here is too complex for purpose and size.
To the contrary, implemented are mapped pseudo instructions and composed 32 bit "fusions" will be optimized too
(in total cca 80 instructions, half of which are optimized pseudos and compounds will use fusion).
Currently it contains only single core but will allow more cores with separate adress spaces, messaging only
through single hub. Monitor features are still in design too, mostly realted to multi-core.

Licensee is intentionally restrictive now, but this will change to something more open too.
Features are still subject to change, including ISA encoding and mnemonics tweaks.

Build is tested using latest Dev-Cpp, MPLAB X (XC8,XC16,XC32), Segger Embedded Studio for RISC-V, cc65m z88dk.
Engine itself has under 4kB for now, but planned full-featured size is 8kB max.
Planned high-level assembler targeting VMEX (but also native targets) is inteded to be used for reimplementing engine in it.

Some tests are failing now in 8bit environment, mostly multiply routines - things related to typecasting/sign-extensions.
Build was ensured on cc65/z88dk during last days and tests granulated to be debuggable in MCU hardware using mostly Microchip/Atmel Studio.

More docs to come here too, sure.
