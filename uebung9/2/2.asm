SECTION .data
x dd 0
y dd 7
z dd 7
result dd 0

SECTION .bss

SECTION .text

;if ((x == 5 && y != 6) || (z < 7) || (x == y && (y <= 6 || z > x)))
;	result = 10;
;else
;	result = 20;

global _start
_start:
	cmp DWORD [x], 5
	jne A
	cmp DWORD [y], 6
	jne True
A:
	cmp DWORD [z], 7
	jl True

	mov eax, [y]
	cmp DWORD [x], eax
	jne False
	cmp DWORD [y], 6
	jle True
	mov eax, [x]
	cmp DWORD [z], eax
	jle False

True:
	mov DWORD [result], 10
	jmp succeed

False:
	mov DWORD [result], 20

succeed:
	mov eax, 1
	mov ebx, 0
	int 80h
