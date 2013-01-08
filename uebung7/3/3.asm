LINUX_EXIT EQU 1

SECTION .data

SECTION .bss

SECTION .text
global _start

_start: nop
;	mov edx, 1
	mov eax, 65536
	mov ebx, -65536
	imul ebx

	jge one

zero:
	mov ebx, 0
	jmp end

one:
	mov ebx, 1

end: nop
	mov eax, LINUX_EXIT
	int 80h
