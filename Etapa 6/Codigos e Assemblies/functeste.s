	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_func
	.align	4, 0x90
_func:                                  ## @func
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
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	callq	_func
	xorl	%ecx, %ecx
	movl	%eax, _a(%rip)
	movl	%ecx, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_a                      ## @a
.zerofill __DATA,__common,_a,4,2

.subsections_via_symbols
