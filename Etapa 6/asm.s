	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11


	.globl	_main
	.align	4, 0x90
_main:
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
	movsbl	_b(%rip), %ecx
	movsbl	_c(%rip), %edx
	addl	%edx, %ecx
	movb	%cl, %sil
	movb	%sil, _TempVAR0(%rip)
	popq	%rbp
	retq
	.cfi_endproc


	.section	__DATA,__data
	.globl	_a
	.align	2
_a:
	.long	0

	.globl	_b
	.align	2
_b:
	.byte	5

	.globl	_c
	.align	2
_c:
	.byte	7

	.globl	_d
	.align	2
_d:
	.long	7
