#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <operands.h>

typedef enum e_instruct_type {
	MOV_INSTRUCT,
}	t_instruct_type;



typedef struct s_instruct {
	t_instruct_type			instruct_type;
	char					*name;
	uint8_t					len;
	uint8_t					instruct[20];
	t_operand_combination	*operand_combinations;
	size_t					operand_combination_count;
} __attribute((__may_alias__))	t_instruct;

typedef	struct s_instruct_set {
	size_t			size;
	t_instruct		*set;
}	t_instruct_set;

