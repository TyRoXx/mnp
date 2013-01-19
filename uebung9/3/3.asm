EXIT EQU 1
WRITE EQU 4
STDOUT EQU 1

SECTION .data
a dd 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
a_end:
b dd 16, 5, 18, 12, 11, 66, 62, 1, 9, 33
b_end:

SECTION .bss

SECTION .text
sort_range:
	; a = eax, a + LENGTH = ebx
	; a + i = ecx, a + j = edx
	lea ecx, [ebx - 4]        ; for (i = LENGTH - 1;

sort_range_outer:
	lea edi, [eax + 4]
	cmp ecx, edi              ; i > 1;
	jl sort_range_outer_end   ; sollte wohl i >= 1 heissen
	mov edx, eax              ; for (j = 0;

sort_range_inner:
	lea edi, [ecx - 4]
	cmp edx, edi              ; j <= i - 1;
	jg sort_range_inner_end

	; if (a[j] > a[j + 1]) {
	mov edi, [edx]
	mov esi, [edx + 4]
	cmp edi, esi
	jle sort_range_no_swap

	; swap
	mov [edx], esi
	mov [edx + 4], edi

	; }
sort_range_no_swap:
	add edx, 4                ; j++)
	jmp sort_range_inner

sort_range_inner_end:
	sub ecx, 4                ; i--)
	jmp sort_range_outer

sort_range_outer_end:
	ret

print_decimal:
	mov edx, eax
	cmp eax, 10
	jl print_decimal_write
	xor edx, edx
	mov ebx, 10
	div ebx
	push edx
	call print_decimal
	pop edx
print_decimal_write:
	add edx, '0'
	push edx
	mov eax, WRITE
	mov ebx, STDOUT
	mov ecx, esp
	mov edx, 1
	int 80h
	add esp, 4
	ret

print_line_feed:
	push DWORD 10
	mov eax, WRITE
	mov ebx, STDOUT
	mov ecx, esp
	mov edx, 1
	int 80h
	add esp, 4
	ret

print_range:
	cmp eax, ebx
	je print_range_end
	push eax
	push ebx
	mov eax, [eax]
	call print_decimal
	call print_line_feed
	pop ebx
	pop eax
	add eax, 4
	jmp print_range
print_range_end:
	ret

sort_and_print_range:
	push eax
	push ebx
	call sort_range
	pop ebx
	pop eax
	call print_range
	ret

global _start
_start:
	; test with empty array
	mov eax, 0
	mov ebx, 0
	call sort_and_print_range

	; sort a single element
	mov eax, a
	lea ebx, [a + 4]
	call sort_range

	; first array
	mov eax, a
	mov ebx, a_end
	call sort_and_print_range

	; second array
	mov eax, b
	mov ebx, b_end
	call sort_and_print_range

succeed:
	mov eax, EXIT
	mov ebx, 0
	int 80h
