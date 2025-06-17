#!/bin/bash

cp /mnt/d/_vmex-tmp/src/* /home/falken/_vmex/src

docker run -v /home/falken/_vmex:/_vmex -w /_vmex -u root xora/qdos-devel qdos-gcc -o VMEX src/VMEX.c

sudo chown -R falken:falken ~/_vmex

cp /home/falken/_vmex/VMEX /mnt/d/_vmex-tmp/VMEX

read -p "Press [Enter] to continue..."
