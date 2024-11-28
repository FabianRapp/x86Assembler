#ifndef instruct_SET_H
# define instruct_SET_H

#include <stdint.h>
#include <libft.h>
#include <string.h>
#include <stdio.h>

#include <instruction_types.h>
#include <operands.h>
#include <mov.h>



//void	add_instruct(t_instruct_set *instruct_set, void *instruct);

void	init_instruct_set(t_instruct_set *instruct_set);

void	free_instruct_set(t_instruct_set *instruct_set);

#endif // instruct_SET_H
