log: log.asm
	nasm -f elf -g -F dwarf log.asm
	ld -o log log.o -m elf_i386
