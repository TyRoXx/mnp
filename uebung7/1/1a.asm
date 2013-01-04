SECTION .data
SECTION .bss
SECTION .text
global _start

_start: nop             ; int main(void) {
	mov eax, 5
	mov ebx, 7
	sub eax, ebx        ; a = a - b;

end:
	mov eax, 1
	mov ebx, 0
	int 80h             ; exit(0);

	mov eax, 1
	ret                 ; return 1; }
