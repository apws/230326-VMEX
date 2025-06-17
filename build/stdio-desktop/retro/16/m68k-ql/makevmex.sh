#!/bin/bash

cp /mnt/c/Users/petra/OneDrive/Documents/~prj/230326-GPT-assisted-VMEX-ISA-interpreter/src/*.c  /home/falken/_vmex/src
cp /mnt/c/Users/petra/OneDrive/Documents/~prj/230326-GPT-assisted-VMEX-ISA-interpreter/src/*.h  /home/falken/_vmex/src

docker run -v /home/falken/_vmex:/_vmex -w /_vmex -u root xora/qdos-devel qdos-gcc -o VMEX.bin src/VMEX.c

sudo chown -R falken:falken ~/_vmex

cp /home/falken/_vmex/VMEX.bin /mnt/c/Users/petra/OneDrive/Documents/~prj/230326-GPT-assisted-VMEX-ISA-interpreter/VMEX_M68k/sinclair-ql/

read -p "Press [Enter] to continue..."
