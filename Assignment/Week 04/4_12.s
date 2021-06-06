	.file	"4-1.c"
	.text
	.globl	inc
	.type	inc, @function
inc:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movl	%edi, -12(%rbp)
	movl	%esi, -16(%rbp)
	movl	$0, %ebx
	jmp	.L2
.L5:
	movl	-12(%rbp), %eax
	movl	%ebx, %ecx
	addl	$2, %ebx
	addl	$1, %ecx		
	andl	$1, %eax
	testl	%eax, %eax
	cmovne	 %ecx, %ebx
	addl	$1, -12(%rbp)
.L2:
	movl	-12(%rbp), %eax
	imull	-12(%rbp), %eax
	cmpl	%eax, -16(%rbp)
	jg	.L5
	movl	%ebx, %eax
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	inc, .-inc
	.section	.rodata
.LC0:
	.string	"%d\n\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$100, %esi
	movl	$1, %edi
	call	inc
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
