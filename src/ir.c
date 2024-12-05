#include <ir.h>

static t_ir_command	*new_ir_command(void) {
	t_ir_command	*command = calloc(1, sizeof(t_ir_command));
	assert(command && "malloc fail");
	command->type = IR_COMMAND;
	command->operands = dyn_arr_init2(3, sizeof(t_token *), 0, free_token_list2);
	assert(command->operands && "malloc fail");
	return (command);
}

static void	free_ir_command(t_ir_command *command) {
	if (!command) {
		return ;
	}
	free_token_list(command->identifier);
	dyn_arr_free((void**) &command->operands);
	free(command);
}

static void	print_ir_command(t_ir_command *command) {
	assert(command->type == IR_COMMAND && "wrong type");
	assert(command->identifier && "command does not have an identifier");
	printf("COMMAND(line %lu):\n", command->identifier->debug_info.line_idx);
	print_token_list_indent(command->identifier, 4);
	for (size_t operand_idx = 0; operand_idx < command->operand_count;
		operand_idx++)
	{
		printf("|   Operand %lu:\n", operand_idx);
		print_token_list_indent(command->operands[operand_idx], 8);
	}
}

static t_ir_label	*new_ir_label(void) {
	t_ir_label	*label = calloc(1, sizeof(t_ir_label));
	assert(label && "malloc fail");
	label->type = IR_LABEL;
	return (label);
}

static void	free_ir_label(t_ir_label *label) {
	if (!label) {
		return ;
	}
	free_token_list(label->tokens);
	free(label);
}

static void	print_ir_label(t_ir_label *label) {
	assert(label->type == IR_LABEL && "wrong type");
	assert(label->tokens && "label does not have an identifier");
	printf("LABEL(line %lu):\n", label->tokens->debug_info.line_idx);
	print_token_list_indent(label->tokens, 4);
}

void	sub_type_ir_directive(t_ir_directive *directive) {
	assert(directive->type == IR_DIRECTIVE);
	assert(directive->tokens && "assumes tokens to be filled in");
	const char	*sections[] = {
		".text",
		".data",
		".bss",
		".section",
		".symtab",
	};
	const char	*scopes[] = {
		".global",
		".local",
	};
	const char	*types[] = {
		".type",
		".size",
		".weak",
	};
	const char	*frame[] = {
		".cfi_startproc",
		".cfi_endproc",
		".cfi_def_cfa",
		".cfi_def_cfa_offset",
		".cfi_def_cfa_register",
		".cfi_offset",
		".cfi_adjust_cfa_offset",
		".cfi_register",
		".cfi_restore",
	};
	const char	*allocs[] = {
		".byte",
		".word",
		".long",
		".quad",
		".zero",
		".asciz",
		".ascii",
	};
	const char	*debug[] = {
		".file",
		".loc",
		".frame",
		".debug_file",
		".debug_loc",
		".debug_frame",
		".debug_info",
		".eh_frame",
	};
	const char	*macros[] = {
		".ifdef",
		".ifndef",
		".else",
		".endif",
		".equ",
		".macro",
		".endm",
		".incbin",
	};
	const char	*def[] = {
		".comm",
		".lcomm",
	};
	const char	*align[] = {
		".p2align",
		".align",
	};
}

static t_ir_directive	*new_ir_directive(void) {
	t_ir_directive	*directive = calloc(1, sizeof(t_ir_directive));
	assert(directive && "malloc fail");
	directive->type = IR_DIRECTIVE;
	return (directive);
}

static void	free_ir_directive(t_ir_directive *directive) {
	if (!directive) {
		return ;
	}
	free_token_list(directive->tokens);
	free(directive);
}

static void	print_ir_directive(t_ir_directive *directive) {
	assert(directive->type == IR_DIRECTIVE && "wrong type");
	assert(directive->tokens && "directive does not have an identifier");
	printf("DIRECTIVE(line %lu):\n", directive->tokens->debug_info.line_idx);
	print_token_list_indent(directive->tokens, 4);
}

t_ir	*new_ir_node(t_ir_type type) {
	t_ir	*node = calloc(1, sizeof(t_ir));
	assert(node && "malloc fail");

	node->type = type;
	switch (type) {
		case (IR_COMMAND):
			node->node = new_ir_command();
			break ;
		case (IR_LABEL):
			node->node = new_ir_label();
			break ;
		case (IR_DIRECTIVE):
			node->node = new_ir_directive();
			break ;
		default:
			assert(0 && "unsupported type");
	}
	return (node);
}

void	free_ir_node(t_ir *node) {
	if (!node) {
		return ;
	}
	switch (node->type) {
		case (IR_COMMAND):
			free_ir_command(node->node);
			break ;
		case (IR_LABEL):
			free_ir_label(node->node);
			break ;
		case (IR_DIRECTIVE):
			free_ir_directive(node->node);
			break ;
		default:
			assert(0 && "unsupported type");
	}
	free(node);
}

void	free_ir_list(t_ir *head) {
	t_ir	*last = head;

	while (head) {
		head = head->next;
		free_ir_node(last);
		last = head;
	}
}

void	print_ir_node(t_ir *ir) {
	if (!ir) {
		printf("Node does not exist!\n");
		return ;
	}
	switch (ir->type) {
		case (IR_COMMAND):
			print_ir_command(ir->node);
			break ;
		case (IR_LABEL):
			print_ir_label(ir->node);
			break ;
		case (IR_DIRECTIVE):
			print_ir_directive(ir->node);
			break ;
		default:
			assert(0 && "unsupported type");
	}
	printf("----------------------------\n");
}


void	print_ir_list(t_ir *head) {
	size_t	idx = 0;
	for (t_ir *cur = head; cur; cur=cur->next, idx++) {
		printf("IR %lu: ", idx);
		print_ir_node(cur);
	}
}

void	print_ir_index(t_ir *head, size_t idx) {
	t_ir	*cur = head;
	for (size_t j = 0; j < idx && cur; j++, cur=cur->next);
	printf("IR %lu: ", idx);
	print_ir_node(cur);
}
