#include <instruction_set.h>

void	add_instruct(t_instruct_set *instruct_set, t_instruct instruct) {
	dyn_arr_add_save((void **)(&instruct_set->set), &instruct,
		instruct_set->size++);
}

// frees the conent, not struct itself
void	free_instruct(t_instruct *instruct) {
	//for (size_t i = 0; i < dyn_arr_get_len(instruct.operand_combinations); i++) {
	//	free_operand(*instruct.operand_combinations[i].left);
	//	free(instruct.operand_combinations[i].left);
	//	free_operand(*instruct.operand_combinations[i].right);
	//	free(instruct.operand_combinations[i].right);
	//}
	dyn_arr_free((void **)&instruct->operand_combinations);
	free(instruct->name);
}

t_instruct_set	init_instruct_set(t_operand_set operand_sets[SET_OPERAND_COUNT])
{
	t_instruct_set	instruct_set;
	instruct_set.size = 0;
	/*
		TODO: i think i have to make a function here that frees
		not base operand sets/sets with sub sets but it must not free the sets
		in operand_sets[]
	*/
	//instruct_set.set = dyn_arr_init2(3, sizeof(t_instruct), 0, free_instruct);
	instruct_set.set = dyn_arr_init2(3, sizeof(t_instruct), 0, NULL);
	assert(instruct_set.set && "malloc fail");

	add_mov_instructs(&instruct_set, operand_sets);
	return (instruct_set);
}

void	free_instruct_set(t_instruct_set instruct_set) {
	//for (size_t i = 0; i < instruct_set.size; i++) {
	//	free_instruct(instruct_set.set[i]);
	//}
	dyn_arr_free((void **)(&instruct_set.set));
}
