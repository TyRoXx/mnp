EXIT EQU 1

SECTION .data

SECTION .bss

SECTION .text

exit:
	mov ebx, eax
	mov eax, EXIT
	int 80h

fibo: ; n = eax
	cmp eax, 1
	jg fibo_recurse
	ret
fibo_recurse:
	sub eax, 2
	push eax
	call fibo
	push eax
	mov eax, [esp + 4]
	inc eax
	call fibo
	add eax, [esp]
	add esp, 8
	ret

test_begin dd \
	0, 0, \
	1, 1, \
	2, 1, \
	7, 13, \
	30, 832040
test_end:

global _start
_start:
	mov ecx, test_begin
check_next:
	cmp ecx, test_end
	je success

	mov eax, [ecx]
	call fibo
	cmp eax, [ecx + 4]
	jne fail

	add ecx, 8
	jmp check_next

success:
	mov eax, 0
	call exit

fail:
	mov eax, 1
	call exit
