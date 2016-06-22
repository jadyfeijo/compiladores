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
	movb	$53, -1(%rbp)
	movb	$54, -2(%rbp)
	movb	$48, -3(%rbp)
	movsbl	-2(%rbp), %ecx
	movsbl	-1(%rbp), %edx
	addl	%edx, %ecx
	movb	%cl, %sil
	movb	%sil, -3(%rbp)
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
