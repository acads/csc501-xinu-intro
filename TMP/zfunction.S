.globl zfunction

zfunction:
	push %ebp
	mov %esp, %ebp
	movl $0x03fe000, -0x4(%ebp)
   	mov -0x4(%ebp), %eax
	not %eax
	and %eax, 0x8(%ebp)
	shll $0x4, 0x8(%ebp)
	mov 0x8(%ebp), %eax
	leave
	ret
