	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11


	.section	__DATA,__data
	.globl	_a
	.align	2
_a:
	.long	0

	.globl	_c
	.align	2
_c:
	.byte	0

	.globl	_voidfunc
	.align	4, 0x90
_voidfunc:
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
