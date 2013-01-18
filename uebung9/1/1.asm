SECTION .data
 a dq 1_000_000_000 ; result 111999999187
;a dq           588 ; result         4675

b dd 112
c dd 24
d dd 12
e dd 815

SECTION .bss

SECTION .text

global _start
_start:
	mov eax, [a]
	mov edx, [a + 4]
	mul DWORD[b]
	add eax, [c]
	adc edx, 0
divide:
	cmp edx, [d]
	jge on_overflow
	div DWORD[d]
	jmp after_divide
on_overflow:
	mov eax, -1
after_divide:
	sub eax, [e]
	sbb edx, 0

succeed:
	mov eax, 1
	mov ebx, 0
	int 80h
