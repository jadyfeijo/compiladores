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
	movl	$0,	-4(%rbp)
	cmpl	$0,	_TempVAR0(%rip)
	je	LBB0_0
## BB#1
	movsbl	_b(%rip), %ecx
	movsbl	_c(%rip), %edx
	addl	%edx, %ecx
	movb	%cl, %sil
	movb	%sil, _TempVAR1(%rip)
LBB0_0
	movsbl	_b(%rip), %ecx
	movsbl	_b(%rip), %edx
	addl	%edx, %ecx
	movb	%cl, %sil
	movb	%sil, _TempVAR2(%rip)
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
	movl	$0,	-4(%rbp)
	cmpl	$0,	_Label0(%rip)
	je	LBB0_0
## BB#1
LBB0_0
	movsbl	_b(%rip), %ecx
	movsbl	_c(%rip), %edx
	addl	%edx, %ecx
	movb	%cl, %sil
	movb	%sil, _TempVAR1(%rip)
LBB0_1
	movsbl	_b(%rip), %ecx
	movsbl	_b(%rip), %edx
	addl	%edx, %ecx
	movb	%cl, %sil
	movb	%sil, _TempVAR2(%rip)
LBB0_2
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
