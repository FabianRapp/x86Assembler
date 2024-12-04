	.file	"main.c"
	.text
	.globl	cleanup
	.type	cleanup, @function
cleanup:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	240(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-24(%rbp), %rax
	movq	248(%rax), %rdx
	movq	256(%rax), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	free_instruct_set@PLT
	movq	-24(%rbp), %rax
	movl	264(%rax), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movq	-24(%rbp), %rcx
	movl	-4(%rbp), %edx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, %rdi
	call	free_operand_set@PLT
	addl	$1, -4(%rbp)
.L2:
	cmpl	$5, -4(%rbp)
	jbe	.L3
	movl	$0, %edi
	call	exit@PLT
	.cfi_endproc
.LFE6:
	.size	cleanup, .-cleanup
	.type	sep, @function
sep:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movsbq	-4(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	setne	%al
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	sep, .-sep
	.section	.rodata
.LC0:
	.string	"src/main.c"
.LC1:
	.string	"0 && \"invalid instruction\""
	.text
	.globl	get_basic_instruct
	.type	get_basic_instruct, @function
get_basic_instruct:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	$0, -96(%rbp)
	jmp	.L7
.L10:
	movq	-112(%rbp), %rax
	movq	256(%rax), %rcx
	movq	-96(%rbp), %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -80(%rbp)
	movq	%rbx, -72(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -64(%rbp)
	movq	%rbx, -56(%rbp)
	movq	32(%rax), %rcx
	movq	40(%rax), %rbx
	movq	%rcx, -48(%rbp)
	movq	%rbx, -40(%rbp)
	movq	48(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rdx
	movq	-120(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L8
	movq	-104(%rbp), %rax
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-32(%rbp), %rdx
	movq	%rdx, 48(%rax)
	nop
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L11
	jmp	.L12
.L8:
	addq	$1, -96(%rbp)
.L7:
	movq	-112(%rbp), %rax
	movq	248(%rax), %rax
	cmpq	%rax, -96(%rbp)
	jb	.L10
	leaq	__PRETTY_FUNCTION__.5(%rip), %rax
	movq	%rax, %rcx
	movl	$35, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L12:
	call	__stack_chk_fail@PLT
.L11:
	movq	-104(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	get_basic_instruct, .-get_basic_instruct
	.section	.rodata
	.align 8
.LC2:
	.string	"bits == 6 && \"unsupported operand opcode size: larger than 1 byte\""
	.align 8
.LC3:
	.string	"write(data->output, &code, 1) != -1 && \"write fail\""
	.text
	.globl	output_2gp_regs
	.type	output_2gp_regs, @function
output_2gp_regs:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rax
	movq	40(%rax), %rax
	movl	%eax, %edx
	movq	-32(%rbp), %rax
	addq	$56, %rax
	movq	40(%rax), %rax
	addl	%edx, %eax
	movb	%al, -9(%rbp)
	cmpb	$6, -9(%rbp)
	je	.L14
	leaq	__PRETTY_FUNCTION__.4(%rip), %rax
	movq	%rax, %rcx
	movl	$44, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L14:
	movzbl	-9(%rbp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	negl	%eax
	movb	%al, -10(%rbp)
	movq	-32(%rbp), %rax
	movzbl	16(%rax), %eax
	movzbl	%al, %edx
	movq	-32(%rbp), %rax
	movq	40(%rax), %rax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movq	-32(%rbp), %rax
	addq	$56, %rax
	movzbl	16(%rax), %eax
	orl	%eax, %edx
	movzbl	-10(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -10(%rbp)
	movq	-24(%rbp), %rax
	movl	264(%rax), %eax
	leaq	-10(%rbp), %rcx
	movl	$1, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	cmpq	$-1, %rax
	jne	.L18
	leaq	__PRETTY_FUNCTION__.4(%rip), %rax
	movq	%rax, %rcx
	movl	$50, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L18:
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L17
	call	__stack_chk_fail@PLT
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	output_2gp_regs, .-output_2gp_regs
	.section	.rodata
.LC4:
	.string	"%s\n%s\n"
	.align 8
.LC5:
	.string	"0 && \"opernad 1 has not implemented type\""
	.align 8
.LC6:
	.string	"0 && \"opernad 0 has not implemented type\""
.LC7:
	.string	"oerpand_count: %d\n"
	.align 8
.LC8:
	.string	"0 && \"unsupported operand combination\""
	.text
	.globl	output_operands
	.type	output_operands, @function
output_operands:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	cmpl	$2, -20(%rbp)
	jne	.L20
	movq	-16(%rbp), %rax
	addq	$56, %rax
	movq	48(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	48(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	subl	$2, %eax
	cmpl	$3, %eax
	ja	.L26
	movq	-16(%rbp), %rax
	addq	$56, %rax
	movl	(%rax), %eax
	subl	$2, %eax
	cmpl	$3, %eax
	ja	.L27
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	output_2gp_regs
	nop
	nop
	jmp	.L28
.L27:
	leaq	__PRETTY_FUNCTION__.3(%rip), %rax
	movq	%rax, %rcx
	movl	$75, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L26:
	leaq	__PRETTY_FUNCTION__.3(%rip), %rax
	movq	%rax, %rcx
	movl	$79, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L20:
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	__PRETTY_FUNCTION__.3(%rip), %rax
	movq	%rax, %rcx
	movl	$84, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L28:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	output_operands, .-output_operands
	.section	.rodata
	.align 8
.LC9:
	.string	"write(data->output, instruct.instruct, instruct.len) != -1 && \"write fail\""
	.text
	.globl	output_opcode
	.type	output_opcode, @function
output_opcode:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movzbl	32(%rbp), %eax
	movzbl	%al, %edx
	movq	-8(%rbp), %rax
	movl	264(%rax), %eax
	leaq	33(%rbp), %rcx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	cmpq	$-1, %rax
	jne	.L32
	leaq	__PRETTY_FUNCTION__.2(%rip), %rax
	movq	%rax, %rcx
	movl	$91, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L32:
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	output_operands
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	output_opcode, .-output_opcode
	.section	.rodata
.LC10:
	.string	"instruction input: %s\n"
.LC11:
	.string	"0 && \"mall fail\""
.LC12:
	.string	"%u\n"
.LC13:
	.string	"0"
	.align 8
.LC14:
	.string	"0 && \"more than two operands per instruction\""
	.text
	.globl	process_instruction
	.type	process_instruction, @function
process_instruction:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$264, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -264(%rbp)
	movq	%rsi, -272(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-272(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-272(%rbp), %rax
	leaq	sep(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ft_split_fn@PLT
	movq	%rax, -224(%rbp)
	cmpq	$0, -224(%rbp)
	jne	.L34
	leaq	__PRETTY_FUNCTION__.1(%rip), %rax
	movq	%rax, %rcx
	movl	$105, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L34:
	movq	-224(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L35
	movq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L33
.L35:
	movq	-224(%rbp), %rax
	movq	(%rax), %rdx
	leaq	-208(%rbp), %rax
	movq	-264(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_basic_instruct
	movq	$0, -240(%rbp)
	jmp	.L37
.L38:
	leaq	-191(%rbp), %rdx
	movq	-240(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$1, -240(%rbp)
.L37:
	movzbl	-192(%rbp), %eax
	movzbl	%al, %eax
	cmpq	%rax, -240(%rbp)
	jb	.L38
	movq	-200(%rbp), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -248(%rbp)
	movq	$1, -232(%rbp)
	jmp	.L39
.L41:
	movq	-216(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	leaq	-1(%rax), %rdx
	movq	-216(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$44, %al
	jne	.L40
	movq	-216(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	leaq	-1(%rax), %rdx
	movq	-216(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
.L40:
	addl	$1, -248(%rbp)
	addq	$1, -232(%rbp)
.L39:
	movq	-232(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-224(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -216(%rbp)
	cmpq	$0, -216(%rbp)
	jne	.L41
	cmpl	$0, -248(%rbp)
	jne	.L42
	leaq	__PRETTY_FUNCTION__.1(%rip), %rax
	movq	%rax, %rcx
	movl	$129, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L42:
	cmpl	$1, -248(%rbp)
	jne	.L43
	leaq	__PRETTY_FUNCTION__.1(%rip), %rax
	movq	%rax, %rcx
	movl	$132, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L43:
	cmpl	$2, -248(%rbp)
	jne	.L44
	movq	-224(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rsi
	movq	-224(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdi
	leaq	-144(%rbp), %rdx
	subq	$8, %rsp
	subq	$56, %rsp
	movq	%rsp, %rax
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-192(%rbp), %rcx
	movq	-184(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-160(%rbp), %rcx
	movq	%rcx, 48(%rax)
	call	new_operand@PLT
	addq	$64, %rsp
	movl	-248(%rbp), %edx
	leaq	-144(%rbp), %rsi
	movq	-264(%rbp), %rdi
	subq	$8, %rsp
	subq	$56, %rsp
	movq	%rsp, %rax
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-192(%rbp), %rcx
	movq	-184(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-176(%rbp), %rcx
	movq	-168(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-160(%rbp), %rcx
	movq	%rcx, 48(%rax)
	call	output_opcode
	addq	$64, %rsp
	movl	$0, -244(%rbp)
	jmp	.L46
.L44:
	leaq	__PRETTY_FUNCTION__.1(%rip), %rax
	movq	%rax, %rcx
	movl	$136, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L47:
	movl	-244(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	subq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	-144(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	free_operand@PLT
	addl	$1, -244(%rbp)
.L46:
	movl	-244(%rbp), %eax
	cmpl	-248(%rbp), %eax
	jl	.L47
	movq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	ft_free_2darr@PLT
.L33:
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L48
	call	__stack_chk_fail@PLT
.L48:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	process_instruction, .-process_instruction
	.section	.rodata
	.align 8
.LC15:
	.string	"(*head)->type == TOKEN_IDENTIFIER && \"expected identifier token\""
	.text
	.globl	next_command_block
	.type	next_command_block, @function
next_command_block:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	cmpl	$13, %eax
	jne	.L50
	movl	$0, %eax
	jmp	.L51
.L50:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	cmpl	$10, %eax
	je	.L52
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$153, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L52:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L53
.L55:
	movq	-16(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, -16(%rbp)
.L53:
	movq	-16(%rbp), %rax
	movq	40(%rax), %rax
	movl	(%rax), %eax
	cmpl	$13, %eax
	je	.L54
	movq	-16(%rbp), %rax
	movq	40(%rax), %rax
	movl	(%rax), %eax
	cmpl	$1, %eax
	jne	.L55
.L54:
	movq	-16(%rbp), %rax
	movq	40(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	$0, 40(%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	cmpl	$1, %eax
	jne	.L56
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	40(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	$0, 40(%rax)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free_token@PLT
.L56:
	movq	-8(%rbp), %rax
.L51:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	next_command_block, .-next_command_block
	.section	.rodata
.LC16:
	.string	"command %lu:\n"
.LC17:
	.string	"remaining head:"
	.text
	.globl	parser
	.type	parser, @function
parser:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movq	240(%rax), %rax
	movq	%rax, %rdi
	call	lexer@PLT
	movq	%rax, -32(%rbp)
	movq	$0, -24(%rbp)
.L58:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	next_command_block
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movq	%rax, %rsi
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_token_list@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free_token_list@PLT
	cmpq	$0, -16(%rbp)
	jne	.L58
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	print_token_list@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free_token_list@PLT
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L59
	call	__stack_chk_fail@PLT
.L59:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	parser, .-parser
	.globl	main
	.type	main, @function
main:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$304, %rsp
	movl	%edi, -292(%rbp)
	movq	%rsi, -304(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-304(%rbp), %rdx
	movl	-292(%rbp), %ecx
	leaq	-288(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	init@PLT
	leaq	-288(%rbp), %rax
	movq	%rax, %rdi
	call	parser
	leaq	-288(%rbp), %rax
	movq	%rax, %rdi
	call	cleanup
	.cfi_endproc
.LFE15:
	.size	main, .-main
	.section	.rodata
	.align 16
	.type	__PRETTY_FUNCTION__.5, @object
	.size	__PRETTY_FUNCTION__.5, 19
__PRETTY_FUNCTION__.5:
	.string	"get_basic_instruct"
	.align 16
	.type	__PRETTY_FUNCTION__.4, @object
	.size	__PRETTY_FUNCTION__.4, 16
__PRETTY_FUNCTION__.4:
	.string	"output_2gp_regs"
	.align 16
	.type	__PRETTY_FUNCTION__.3, @object
	.size	__PRETTY_FUNCTION__.3, 16
__PRETTY_FUNCTION__.3:
	.string	"output_operands"
	.align 8
	.type	__PRETTY_FUNCTION__.2, @object
	.size	__PRETTY_FUNCTION__.2, 14
__PRETTY_FUNCTION__.2:
	.string	"output_opcode"
	.align 16
	.type	__PRETTY_FUNCTION__.1, @object
	.size	__PRETTY_FUNCTION__.1, 20
__PRETTY_FUNCTION__.1:
	.string	"process_instruction"
	.align 16
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 19
__PRETTY_FUNCTION__.0:
	.string	"next_command_block"
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
movq %rax, %rdx
movl 0x1234(%rip), %eax
movq 8(%rbp), %rax
movq 16(%rax, %rbx, 2), %rdx
movq 0x7FFFFFFF, %rax
movq -0x7FFFFFFF, %rax
movq $42, %rax
movq %rax, 0x1234(%rbp)
movq (%rax, %rbx, 4), %rcx
movq 16(%rax, %rbx, 2), %rdx
movq %fs:0x10, %rax
movq %rax, %cr3
movsd %xmm0, %xmm1
vmovaps %ymm1, %ymm2
movq $42, 8(%rbp)
movq symbol_name(%rip), %rax
movq symbol_name, %rax
