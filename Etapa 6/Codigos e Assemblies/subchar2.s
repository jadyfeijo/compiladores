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
	movl	_a(%rip), %ecx
	movsbl	_b(%rip), %edx
	subl	%edx, %ecx
	movl	%ecx, _c(%rip)
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_b                      ## @b
_b:
	.byte	53                      ## 0x35

	.globl	_a                      ## @a
	.align	2
_a:
	.long	54                      ## 0x36

	.globl	_c                      ## @c
	.align	2
_c:
	.long	48                      ## 0x30


.subsections_via_symbols
