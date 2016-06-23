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
	movl	$0, -4(%rbp)
	cmpl	$0, _a(%rip)
	je	LBB0_3
## BB#1:
	cmpl	$0, _b(%rip)
	je	LBB0_3
## BB#2:
	jmp	LBB0_3
LBB0_3:
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_a                      ## @a
	.align	2
_a:
	.long	7                       ## 0x7

	.globl	_b                      ## @b
	.align	2
_b:
	.long	8                       ## 0x8


.subsections_via_symbols
