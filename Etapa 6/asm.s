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
LBB0_0:
	movl	$0, -4(%rbp)
	movl	_a(%rip), %eax
	cmpl	_b(%rip), %eax
	jge	LBB0_1
## BB#1
	callq	_TempVAR1
	movl	_TempVAR1(%rip), %ecx
	movl	%ecx, _a(%rip)
	subq	$16, %rsp
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -4(%rbp)          ## 4-byte Spill
	movl	%ecx, %eax
	addq	$16, %rsp
	jmp	LBB0_0
LBB0_1:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_func
	.align	4, 0x90
_func:
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
	xorl	%eax, %eax
	movl	_p(%rip), %ecx
	addl	$1, %ecx
	movl	%ecx, _TempVAR2(%rip)
	movl	_TempVAR2(%rip), %eax
	popq	%rbp
	retq
	.cfi_endproc


	.section	__DATA,__data
	.globl	_a
	.align	2
_a:
	.long	5

	.globl	_b
	.align	2
_b:
	.long	10

	.globl	_TempVAR2
	.align	2
_TempVAR2:
	.long	1
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"compiladores "


.subsections_via_symbols
