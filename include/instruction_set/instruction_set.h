#ifndef instruct_SET_H
# define instruct_SET_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <libft.h>
#include <instruction_types.h>
#include <operands.h>
#include <mov.h>

void			add_instruct(t_instruct_set *instruct_set, t_instruct instruct);
t_instruct_set	init_instruct_set(t_operand_set operand_sets[SET_OPERAND_COUNT]);
void			free_instruct_set(t_instruct_set instruct_set);

#endif // instruct_SET_H
