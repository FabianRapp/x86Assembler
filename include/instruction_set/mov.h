#ifndef MOV_H
# define MOV_H

#include <assert.h>
#include <stdint.h>

#include <libft.h>
#include <operands.h>
#include <instruction_types.h>


void	add_mov_instructs(t_instruct_set *instruct_set);
void	free_mov_instruct(void *instruct);

#endif // MOV_H
