SECTION .data

SECTION .bss

SECTION .text

global _start
_start:


fail:
	mov eax, 1
	mov ebx, 1
	int 80h

succeed:
	mov eax, 1
	mov ebx, 0
	int 80h
