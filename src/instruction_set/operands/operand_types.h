#pragma once

#include <stdbool.h>
typedef struct s_operand	t_operand;

bool		_is_gp_reg(char *operand_str);
t_operand	_new_gp_reg(char *operand_str);
