#pragma once

#include <lexer.h>

typedef enum e_ir_type {
	IR_COMMAND,
	IR_LABEL,
	IR_DIRECTIVE,
	IR_COUNT,
}	t_ir_type;

typedef struct s_ir_command {
	t_ir_type	type;
	t_token		*identifier;
	t_token		**operands;//array of lists
	size_t		operand_count;
}	t_ir_command;

typedef struct s_ir_label {
	t_ir_type	type;
	t_token		*tokens;
}	t_ir_label;

typedef enum e_directive_type {
	DIRECTIVE_SEGMENT,
}	t_directive_type;

typedef struct s_ir_directive {
	t_ir_type			type;
	t_directive_type	sub_type;
	t_token				*tokens;
}	t_ir_directive;

typedef struct s_ir	t_ir;
typedef struct s_ir {
	t_ir		*next;
	t_ir_type	type;
	void		*node;
}	t_ir;

void	sub_type_ir_directive(t_ir_directive *directive);
t_ir	*new_ir_node(t_ir_type type);
void	free_ir_node(t_ir *node);
void	free_ir_list(t_ir *head);
void	print_ir_index(t_ir *head, size_t idx);
void	print_ir_list(t_ir *head);
void	print_ir_node(t_ir *ir);
