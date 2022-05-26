	.file	"SumaVectoresC.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\302\272 componentes del vector"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Tama\303\261o Vectores:%u (%lu B)\n"
	.section	.rodata.str1.8
	.align 8
.LC2:
	.string	"No hay suficiente espacio para los vectores "
	.align 8
.LC4:
	.string	"/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC5:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC6:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%u\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L27
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movl	$4, %ecx
	movl	$1, %edi
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rbx
	movl	%eax, %edx
	movl	%eax, %r13d
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	%ebx, %r15d
	leaq	0(,%r15,8), %r14
	movq	%r14, %rdi
	call	malloc@PLT
	movq	%r14, %rdi
	movq	%rax, %rbp
	call	malloc@PLT
	movq	%r14, %rdi
	movq	%rax, %r12
	call	malloc@PLT
	movq	%rax, %r14
	testq	%rbp, %rbp
	je	.L3
	testq	%r12, %r12
	je	.L3
	testl	%ebx, %ebx
	je	.L28
	pxor	%xmm1, %xmm1
	movsd	.LC3(%rip), %xmm3
	xorl	%eax, %eax
	cvtsi2sdq	%r15, %xmm1
	leal	-1(%rbx), %r15d
	movq	%r15, %rcx
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L8:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	movapd	%xmm1, %xmm7
	movq	%rax, %rdx
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	subsd	%xmm0, %xmm7
	movsd	%xmm2, 0(%rbp,%rax,8)
	movsd	%xmm7, (%r12,%rax,8)
	addq	$1, %rax
	cmpq	%rdx, %r15
	jne	.L8
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	movl	%ecx, 12(%rsp)
	call	clock_gettime@PLT
	movl	12(%rsp), %ecx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L10:
	movsd	0(%rbp,%rax,8), %xmm0
	addsd	(%r12,%rax,8), %xmm0
	movq	%rax, %rdx
	movsd	%xmm0, (%r14,%rax,8)
	addq	$1, %rax
	cmpq	%rdx, %r15
	jne	.L10
	xorl	%edi, %edi
	leaq	32(%rsp), %rsi
	movl	%ecx, 12(%rsp)
	call	clock_gettime@PLT
	movq	40(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	24(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	cmpl	$9, %ebx
	divsd	.LC7(%rip), %xmm0
	movl	12(%rsp), %ecx
	addsd	%xmm1, %xmm0
	jbe	.L29
	movsd	(%r14,%r15,8), %xmm6
	movsd	(%r14), %xmm3
	movl	%ecx, %r9d
	movl	%ebx, %edx
	movsd	(%r12,%r15,8), %xmm5
	movsd	0(%rbp,%r15,8), %xmm4
	movl	%ecx, %r8d
	movl	$1, %edi
	movsd	(%r12), %xmm2
	movsd	0(%rbp), %xmm1
	movl	$7, %eax
	leaq	.LC5(%rip), %rsi
	call	__printf_chk@PLT
.L13:
	movq	%rbp, %rdi
	call	free@PLT
	movq	%r12, %rdi
	call	free@PLT
	movq	%r14, %rdi
	call	free@PLT
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L30
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L29:
	.cfi_restore_state
	movl	%ebx, %edx
	leaq	.LC6(%rip), %rsi
	xorl	%ebx, %ebx
	movl	$1, %edi
	movl	$1, %eax
	leaq	.LC4(%rip), %r15
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L12:
	movsd	0(%rbp,%rbx,8), %xmm0
	movsd	(%r14,%rbx,8), %xmm2
	movl	%ebx, %ecx
	movl	%ebx, %edx
	movl	%ebx, %r8d
	movq	%r15, %rsi
	movl	$1, %edi
	movl	$3, %eax
	movsd	(%r12,%rbx,8), %xmm1
	addq	$1, %rbx
	call	__printf_chk@PLT
	cmpl	%ebx, %r13d
	ja	.L12
	jmp	.L13
.L28:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	40(%rsp), %rax
	pxor	%xmm0, %xmm0
	xorl	%edx, %edx
	subq	24(%rsp), %rax
	pxor	%xmm1, %xmm1
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	divsd	.LC7(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	leaq	.LC6(%rip), %rsi
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	jmp	.L13
.L30:
	call	__stack_chk_fail@PLT
.L3:
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movl	$-2, %edi
	call	exit@PLT
.L27:
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	orl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC3:
	.long	2576980378
	.long	1069128089
	.align 8
.LC7:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
