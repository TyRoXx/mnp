SECTION .data

SECTION .bss

SECTION .text
global _start
_start: nop

mov eax, 2
mov ebx, 3

;swap eax and ebx
xor eax, ebx
xor ebx, eax
xor eax, ebx

exit: mov eax, 1
mov ebx, 0
int 80h
