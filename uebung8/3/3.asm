SECTION .data
a dd 1
b dd 1
c dd 1
d dd 1
e dd 1
f dd 2
g dd 0
h dd 1

SECTION .bss

SECTION .text

global _start
_start:
	; c push
	push DWORD[c]
	; a b *
	mov eax, [a]
	mul DWORD[b]
	; pop -
	pop ebx
	sub eax, ebx
	; push d push
	push eax
	push DWORD[d]
	; e f %
	mov eax, [e]
	xor edx, edx
	div DWORD[f]
	mov eax, edx
	; g -
	sub eax, [g]
	; pop /
	pop ebx
	xchg eax, ebx
	xor edx, edx
	div ebx
	; h /
	xor edx, edx
	div DWORD[h]
	; pop +
	pop ebx
	add eax, ebx

succeed:
	mov eax, 1
	mov ebx, 0
	int 80h
