[BITS 32]
global _inc_value

SECTION .code
_inc_value:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	inc eax
	mov esp, ebp
	pop ebp
	ret

