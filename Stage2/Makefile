
all: main.o functions.o
	gcc -m32 -Wall -Wextra -o main main.o functions.o -lm

main.o: main.c 
	gcc -m32 -c main.c

functions.o: functions.asm
	nasm -f elf32 functions.asm 

clear:
	rm main.o functions.o main

#all:
	#gcc -Wall -Wextra -m32  -o main main.c -lm
#clear:
	#rm main