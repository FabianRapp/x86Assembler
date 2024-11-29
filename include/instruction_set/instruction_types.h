#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef enum e_operand_type {
	GP_REGISTER_OPERAND,
	SEGMENT_REGISTER_OPERAND,
	SEGMENT_OFFSET_OPERAND,
	MEMORY_OPERAND,
	IMMEDIATE_OPERAND,
}	t_operand_type;

typedef struct s_operant {
	t_operand_type	type;
	int				bin_bits;
	unsigned char	*bin;
}	t_operand;

typedef enum e_instruct_type {
	MOV_INSTRUCT,
}	t_instruct_type;

typedef struct s_mov_struction {
	t_instruct_type		instruct_type;
	char				*name;
	uint8_t				max_operands;
	uint8_t				min_operands;
	uint8_t				len;
	uint8_t				instruct[20];

	t_operand			src;
	t_operand			dest;
} __attribute((__may_alias__)) __attribute((__packed__))	t_mov_instruct;

typedef struct s_instruct {
	t_instruct_type		instruct_type;
	char				*name;
	uint8_t				max_operands;
	uint8_t				min_operands;
	uint8_t				len;
	uint8_t				instruct[20];

	unsigned char		data[];
} __attribute((__may_alias__)) __attribute((__packed__))	t_instruct;

typedef	struct s_instruct_set {
	size_t			size;
	t_instruct	**set;
}	t_instruct_set;

