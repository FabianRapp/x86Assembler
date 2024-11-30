#pragma once

#include <stdint.h>
#include <stdlib.h>

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
	size_t				operand_volume_max[2];
	size_t				operand_volume_min[2];
} __attribute((__may_alias__)) __attribute((__packed__))	t_mov_instruct;

typedef struct s_instruct {
	t_instruct_type		instruct_type;
	char				*name;
	uint8_t				max_operands;
	uint8_t				min_operands;
	uint8_t				len;
	uint8_t				instruct[20];
	size_t				operand_volume_max[2];
	size_t				operand_volume_min[2];
	unsigned char		data[];
} __attribute((__may_alias__)) __attribute((__packed__))	t_instruct;

typedef	struct s_instruct_set {
	size_t			size;
	t_instruct	**set;
}	t_instruct_set;

