WRITE EQU 4
STDOUT EQU 1
EXIT EQU 1

SECTION .data

SECTION .bss
test_function resd 1

SECTION .text

exit:
	mov ebx, eax
	mov eax, EXIT
	int 80h


naive:
	xor eax, eax
naive_m1:
	cmp ebx, 2
	jl naive_m2
	sar ebx, 1
	inc eax
	jmp naive_m1
naive_m2:
	ret


loop:
	xor eax, eax
loop_m1:
	sar ebx, 1
	loopz loop_m2
	inc eax
	jmp loop_m1
loop_m2:
	ret


single:
	bsr eax, ebx
	ret


test_data dd \
	56, 5, \
	1, 0, \
	2, 1, \
	3, 1, \
	4, 2, \
	8, 3, \
	9, 3
test_data_end:

run_test:
	mov esi, test_data
run_test_next:
	cmp esi, test_data_end
	je run_test_end

	mov ebx, DWORD [esi]
	call [test_function]
	cmp eax, DWORD [esi + 4]
	je run_test_inc
test_fail:
	mov eax, DWORD [esi]
	call exit
run_test_inc:
	add esi, 8
	jmp run_test_next
run_test_end:
	ret

global _start
_start:
	mov DWORD [test_function], naive
	call run_test

	mov DWORD [test_function], loop
	call run_test

	mov DWORD [test_function], single
	call run_test

	mov eax, 0
	call exit
