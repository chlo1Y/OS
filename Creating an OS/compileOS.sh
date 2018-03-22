#!/bin/sh
#/*CSSE332 FinalProject; 1/16/2018 by Donglai Guo Zesun Yang and Zhihong zhai*/
gcc -o loadFile loadFile.c

dd if=/dev/zero of=floppya.img bs=512 count=2880

nasm bootload.asm

dd if=bootload of=floppya.img bs=512 count=1 seek=0 conv=notrunc

dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc

dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc

./loadFile message.txt

bcc -ansi -c -o kernel.o kernel.c

as86 kernel.asm -o kernel_asm.o 

ld86 -o kernel -d kernel.o kernel_asm.o 

bcc -ansi -c -o shell.o shell.c

as86 lib.asm -o lib.o 

ld86 -o shell -d shell.o lib.o 

dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3

# dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc

./loadFile tstprg

./loadFile tstpr2

./loadFile shell

./loadFile phello

bcc -ansi -c -o snake.o snake.c

ld86 -o snake -d snake.o lib.o

./loadFile snake 

bochs -f opsys.bxrc
