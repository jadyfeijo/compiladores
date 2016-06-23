	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11


<<<<<<< HEAD
	.section	__DATA,__data
	.globl	_a
	.align	2
_a:
	.long	0

	.globl	_b
	.align	2
_b:
	.long	5

	.globl	_c
	.align	2
_c:
	.long	7

	.globl	_d
	.align	2
_d:
	.long	7

=======
>>>>>>> 7b50a09f2a4dae2846bd9d6b28b16671e0e87ad9
	.globl	_main
	.align	4, 0x90
_main:
	.cfi_startproc
## BB#0:
	pushq	rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset rbp, -16
	movq	rsp, rbp
Ltmp2:
	.cfi_def_cfa_register rbp
	xorl	%eax, %eax
<<<<<<< HEAD
	movl	_b(%rip), %ecx
	addl	_c(%rip), %ecx
	movl	%ecx, _TempVAR0(%rip)
	popq	rbp
=======
	movl	_a(%rip), %ecx
	addl	_2(%rip), %ecx
	movl	%ecx, _TempVAR0(%rip)
	popq	%rbp
>>>>>>> 7b50a09f2a4dae2846bd9d6b28b16671e0e87ad9
	retq
	.cfi_endproc


	.section	__DATA,__data
	.globl	_a
	.align	2
_a:
	.long	0

	.globl	_c
	.align	2
_c:
	.byte	0
