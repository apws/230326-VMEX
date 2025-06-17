
SINCLAIR QL - QDOS-DEVEL DOCKER IMAGE
======================================

(doc/Sinclair QL - howto (EN - Bard).docx)

run WSL

/home/falken/_vmex
 - here run:
   mc
   makevmex.sh

(copies sources from src, compiles into VMEX.bin, and copies VMEX.bin back to windows folder)

resulting VMEX.bin must be:
- copied into c:\~app\~emu\_data\qpc2\
- run QPC2 emulator
- load dos1_vmex_bas
- e (converts VMEX.bin na VMEX.exe)
- v (runs VMEX.exe)

