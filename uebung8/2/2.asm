SECTION .data

SECTION .bss

SECTION .text
global _start
_start:

exit:
	mov eax, 1
	mov ebx, 0
	int 80h