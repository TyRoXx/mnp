WRITE EQU 4
STDOUT EQU 1
EXIT EQU 1

SECTION .data

SECTION .bss

SECTION .text

putc:
	push eax
	mov eax, WRITE
	mov ebx, STDOUT
	mov ecx, esp
	mov edx, 1
	int 80h
	add esp, 4
	ret

exit:
	mov ebx, eax
	mov eax, EXIT
	int 80h

;          4       5       6       7       8
table_1 dd case_1, case_2, case_1, case_3, case_5
;          85      86      87      88      89
table_2 dd case_4, case_2, case_2, case_1, case_5

jump_table_demo: ; i = eax
	cmp eax, 4
	jl default_case

	cmp eax, 8
	jg not_table_1

	lea eax, [eax * 4 - 4 * 4]
	jmp DWORD [table_1 + eax]

not_table_1:
	cmp eax, 85
	jl default_case

	cmp eax, 89
	jg default_case

	lea eax, [eax * 4 - 85 * 4]
	jmp DWORD [table_2 + eax]

case_1: ; 4, 6, 88
	mov eax, 1
	jmp after_switch

case_2: ; 5, 86, 87
	mov eax, 2
	jmp after_switch

case_3: ; 7
	mov eax, 3
	jmp after_switch

case_4: ; 85
	mov eax, 4
	jmp after_switch

case_5: ; 8, 89
	mov eax, 5
	jmp after_switch

default_case:
	mov eax, 0

after_switch:
	ret

test_begin dd \
	0, 0, \
	4, 1, \
	5, 2, \
	6, 1, \
	7, 3, \
	8, 5, \
	9, 0, \
	10, 0, \
	50, 0, \
	86, 2, \
	87, 2, \
	88, 1, \
	89, 5, \
	90, 0, \
	99, 0, \
	-1, 0
test_end:

global _start
_start:
	mov edi, test_begin
	mov esi, test_end
test_loop:
	cmp edi, esi
	je test_finish

	mov eax, [edi]
	call jump_table_demo

	cmp eax, [edi + 4]
	jne fail

	add eax, '0'
	call putc

	add edi, 8
	jmp test_loop
test_finish:
	mov eax, 10
	call putc

	mov eax, 0
	call exit

fail:
	mov eax, '!'
	call putc

	mov eax, 10
	call putc

	mov eax, 1
	call exit
