	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
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
	movl	$5, -4(%rbp)
	movl	$6, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	-8(%rbp), %ecx
	addl	-4(%rbp), %ecx
	movl	%ecx, -12(%rbp)
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols