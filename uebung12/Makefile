
all: a1 a2 a3

a1: a1.asm
	nasm -f elf -g -F dwarf a1.asm
	ld -o a1 a1.o -m elf_i386

a2: a2.asm
	nasm -f elf -g -F dwarf a2.asm
	ld -o a2 a2.o -m elf_i386

a3: a3.asm
	nasm -f elf -g -F dwarf a3.asm
	ld -o a3 a3.o -m elf_i386
