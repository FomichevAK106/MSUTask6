
all: main.o functions.o test.o root.o integral.o
	gcc -m32 -Wall -Wextra -o main main.o functions.o test.o root.o integral.o -lm

main.o: main.c test.h main_math.h
	gcc -m32 -c main.c

test.o: test.c
	gcc -m32 -c test.c

root.o: root.c
	gcc -m32 -c root.c

integral.o: integral.c
	gcc -m32 -c integral.c

functions.o: functions.asm
	nasm -f elf32 functions.asm

clean:
	rm main.o functions.o test.o root.o integral.o main

#all:
	#gcc -Wall -Wextra -m32  -o main main.c -lm
#clear:
	#rm main