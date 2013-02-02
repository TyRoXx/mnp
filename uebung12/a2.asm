EXIT EQU 1

SECTION .data

SECTION .bss
node_a resb tnode_sizeof
node_b resb tnode_sizeof
node_c resb tnode_sizeof

SECTION .text

exit:
	mov ebx, eax
	mov eax, EXIT
	int 80h

NULL EQU 0
tnode_key EQU 0
tnode_left EQU 4
tnode_right EQU 8
tnode_sizeof EQU 12

test_4: ; eax = node
	cmp eax, NULL
	je test_4_finish                ; if (node != NULL) {
	mov DWORD [eax + tnode_key], 0  ;   node->key = 0;
	mov ebx, [eax + tnode_left]     ;   help = node->left;
	mov ecx, [eax + tnode_right]
	mov [eax + tnode_left], ecx     ;   node->left = node->right;
	mov [eax + tnode_right], ebx    ;   node->right = help;
	push eax
	mov eax, [eax + tnode_left]
	call test_4                     ;   test_4(node->left);
	pop eax
	mov eax, [eax + tnode_right]
	call test_4                     ;   test_4(node->right);
test_4_finish:                      ; }
	ret

global _start
_start:
	mov DWORD [node_a + tnode_key], 1
	mov DWORD [node_a + tnode_left], node_b
	mov DWORD [node_a + tnode_right], node_c

	mov DWORD [node_b + tnode_key], 0
	mov DWORD [node_b + tnode_left], NULL
	mov DWORD [node_b + tnode_right], NULL

	mov DWORD [node_c + tnode_key], 2
	mov DWORD [node_c + tnode_left], NULL
	mov DWORD [node_c + tnode_right], NULL

	mov eax, node_a
	call test_4

	cmp DWORD [node_a + tnode_left], node_c
	jne fail

	cmp DWORD [node_a + tnode_right], node_b
	jne fail

success:
	mov eax, 0
	call exit

fail:
	mov eax, 1
	call exit
