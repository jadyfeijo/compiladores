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
	movsbl	_b(%rip), %ecx
	movsbl	_c(%rip), %edx
	addl	%edx, %ecx
	movl	%ecx, _a(%rip)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_a                      ## @a
.zerofill __DATA,__common,_a,4,2
	.section	__DATA,__data
	.globl	_b                      ## @b
_b:
	.byte	5                       ## 0x5

	.globl	_c                      ## @c
_c:
	.byte	7                       ## 0x7

	.globl	_d                      ## @d
	.align	2
_d:
	.long	7                       ## 0x7


.subsections_via_symbols
