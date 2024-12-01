#include <instruction_set.h>

void	add_instruct(t_instruct_set *instruct_set, t_instruct instruct) {
	dyn_arr_add_save((void **)(&instruct_set->set), &instruct,
		instruct_set->size++);
}

// frees the conent, not struct itself
void	free_instruct(t_instruct *instruct) {
	dyn_arr_free((void **)&instruct->operand_combinations);
	free(instruct->name);
}

t_instruct_set	init_instruct_set(t_operand_set operand_sets[SET_OPERAND_COUNT])
{
	t_instruct_set	instruct_set;
	instruct_set.size = 0;
	instruct_set.set = dyn_arr_init2(3, sizeof(t_instruct), 0, free_instruct);
	assert(instruct_set.set && "malloc fail");

	add_mov_instructs(&instruct_set, operand_sets);
	return (instruct_set);
}

void	free_instruct_set(t_instruct_set instruct_set) {
	dyn_arr_free((void **)(&instruct_set.set));
}
