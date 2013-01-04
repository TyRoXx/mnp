SECTION .data
a	dd 0xfff                    ; static uint32_t a = 0xfff;
b	dd 0x111                    ; static uint32_t b = 0x111;

SECTION .bss
c	resw 1                      ; static uint16_t c;
                                ; C fehlt die Syntax für uninitialisierte globale Variablen
d	resw 1

SECTION .text
global _start

_start: nop                     ; int main(void) {
	mov eax, [a]                ;     uint32_t i = a;
	add eax, [b]                ;     i += b;
	shl eax, 1                  ;     i <<= 1;
	shl eax, 1                  ;     i <<= 1;
	mov ebx, 5                  ;     uint32_t j = 5;
	sub edx, edx
	div ebx                     ;     i /= j;
	mov word[d], -1
	mov [c], eax                ;     c = (uint16_t)i;
	                            ; d wird mit der oberen Hälfte von eax überschrieben

end:
	mov rax, 1
	mov rbx, 0
	int 80h                     ;     exit(0);

	mov rax, 1
	ret                         ;     return 1;
	                            ; }
