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
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_a                      ## @a
.zerofill __DATA,__common,_a,1,0

.subsections_via_symbols
case TAC_ADD: 
		{
			if(node->operand1->type == 2) //2=LIT_INTEGER
			{
				fprintf(output, "\tmovl	$%s, %%eax\n", node->operand1->key);
				if(node->operand2->type == 2)
					fprintf(output, "\taddl	$%s, %%eax\n", node->operand2->key);
				else
					fprintf(output, "\taddl	_%s(%%rip), %%eax\n", node->operand2->key);
			}
			else
			{
				fprintf(output, "\tmovl	_%s(%%rip), %%eax\n", node->operand1->key);
				if(node->operand2->type == 2)
					fprintf(output, "\taddl	$%s, %%eax\n", node->operand2->key);
				else
					fprintf(output, "\taddl	_%s(%%rip), %%eax\n", node->operand2->key);
			}
			fprintf(output, "\tmovl	%%eax, _%s(%%rip)\n", node->result->key);