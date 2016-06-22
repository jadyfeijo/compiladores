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
	subq	$96, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -36(%rbp)
	movl	$5, -40(%rbp)
	movl	$6, -44(%rbp)
	movl	$0, -48(%rbp)
	movl	$0, -52(%rbp)
	movl	$0, -56(%rbp)
	movl	$0, -60(%rbp)
	movl	$0, -64(%rbp)
	movq	l_main.c(%rip), %rax
	movq	%rax, -32(%rbp)
	movq	l_main.c+8(%rip), %rax
	movq	%rax, -24(%rbp)
	movl	l_main.c+16(%rip), %ecx
	movl	%ecx, -16(%rbp)
	movl	-40(%rbp), %ecx
	addl	-44(%rbp), %ecx
	movl	%ecx, -48(%rbp)
	movl	-40(%rbp), %ecx
	imull	-44(%rbp), %ecx
	movl	%ecx, -56(%rbp)
	movl	-40(%rbp), %eax
	cltd
	idivl	-44(%rbp)
	movl	%eax, -60(%rbp)
	movl	-40(%rbp), %eax
	subl	-44(%rbp), %eax
	movl	%eax, -52(%rbp)
	movl	-40(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	LBB0_2
## BB#1:
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -68(%rbp)         ## 4-byte Spill
LBB0_2:
	movl	-40(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jle	LBB0_4
## BB#3:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -72(%rbp)         ## 4-byte Spill
LBB0_4:
	movl	-40(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jne	LBB0_6
## BB#5:
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -76(%rbp)         ## 4-byte Spill
LBB0_6:
	movl	-40(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jg	LBB0_8
## BB#7:
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -80(%rbp)         ## 4-byte Spill
LBB0_8:
	movl	-40(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jge	LBB0_10
## BB#9:
	leaq	L_.str.4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -84(%rbp)         ## 4-byte Spill
LBB0_10:
	movl	-40(%rbp), %eax
	cmpl	-44(%rbp), %eax
	je	LBB0_12
## BB#11:
	leaq	L_.str.5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	%eax, -88(%rbp)         ## 4-byte Spill
LBB0_12:
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movl	-36(%rbp), %ecx
	movq	(%rax), %rax
	cmpq	-8(%rbp), %rax
	movl	%ecx, -92(%rbp)         ## 4-byte Spill
	jne	LBB0_14
## BB#13:                               ## %SP_return
	movl	-92(%rbp), %eax         ## 4-byte Reload
	addq	$96, %rsp
	popq	%rbp
	retq
LBB0_14:                                ## %CallStackCheckFailBlk
	callq	___stack_chk_fail
	.cfi_endproc

	.globl	_voidfunc
	.align	4, 0x90
_voidfunc:                              ## @voidfunc
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
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__const
	.align	4                       ## @main.c
l_main.c:
	.long	1                       ## 0x1
	.long	2                       ## 0x2
	.long	3                       ## 0x3
	.long	4                       ## 0x4
	.long	5                       ## 0x5

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"a>=b"

L_.str.1:                               ## @.str.1
	.asciz	"a>b"

L_.str.2:                               ## @.str.2
	.asciz	"a==b"

L_.str.3:                               ## @.str.3
	.asciz	"a<=b"

L_.str.4:                               ## @.str.4
	.asciz	"a<b"

L_.str.5:                               ## @.str.5
	.asciz	"a!=b"


.subsections_via_symbols
