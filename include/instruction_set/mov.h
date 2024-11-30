#ifndef MOV_H
# define MOV_H

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include <libft.h>
#include <operands.h>
#include <instruction_types.h>


void	add_instruct(t_instruct_set *instruct_set, t_instruct instruct);
void	add_mov_instructs(t_instruct_set *instruct_set);

#endif // MOV_H
