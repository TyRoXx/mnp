SECTION .data
TEST_NUMBERS: dd \
	11, 5, 55, \
	-99, 99, -9801, \
	13, -50, -650, \
	-72, -32, 2304, \
	0, 56, 0
TEST_NUMBERS_END:

SECTION .bss

SECTION .text

egypt_mul: ; eax * ebx -> eax
	push ecx
	xor ecx, ecx

egypt_mul_round:
	sub ebx, 0
	jz egypt_mul_end

	test ebx, 1
	jz egypt_mul_half

	add ecx, eax

egypt_mul_half:
	shr ebx, 1
	shl eax, 1

	jmp egypt_mul_round

egypt_mul_end:
	mov eax, ecx
	pop ecx
	ret

global _start
_start:
	mov ecx, TEST_NUMBERS
test_loop:
	cmp ecx, TEST_NUMBERS_END
	je succeed

	mov eax, [ecx]
	mov ebx, [ecx + 4]
	call egypt_mul

	cmp eax, [ecx + 8]
	jne fail

	add ecx, 12
	jmp test_loop

fail:
	mov eax, 1
	mov ebx, 1
	int 80h

succeed:
	mov eax, 1
	mov ebx, 0
	int 80h
