EXIT EQU 1

S_a EQU 0
S_b EQU 4
S_sizeof EQU 8

SECTION .data
new times S_sizeof db 0                     ; static S new;

SECTION .bss

SECTION .text

exit:
	mov ebx, eax
	mov eax, EXIT
	int 80h

makeStruct: ; eax = result, ebx = na, ecx = nb
	mov [eax + S_a], ebx
	mov [eax + S_b], ecx
	ret

global _start
_start:
	sub esp, S_sizeof
	mov eax, esp
	mov ebx, 7331
	mov ecx, 21
	call makeStruct
	add esp, S_sizeof

	mov eax, new
	mov ebx, 1337
	mov ecx, 127
	call makeStruct

	mov eax, [new + S_a]
	cdq
	movsx ecx, BYTE [new + S_b]
	idiv ecx

	mov eax, edx
	call exit
