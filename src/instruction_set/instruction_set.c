#include <instruction_set.h>

//void	add_instruct(t_instruct_set *instruct_set, t_instruct *instruct)
//{
//	dyn_arr_add_save((void **)(&instruct_set->set), instruct,
//		instruct_set->size++);
//}

void	init_instruct_set(t_instruct_set *instruct_set) {
	instruct_set->size = 0;
	instruct_set->set = dyn_arr_init(sizeof(t_mov_instruct *), 0);
	assert(instruct_set->set && "malloc fail");

	add_mov_instructs(instruct_set);
	//printf("%d\n", buf[0]->src.bin_bits);
	//printf("%d\n", instruct_set->set[0]->dest.bin_bits);
}

void	free_instruct_set(t_instruct_set *instruct_set) {

	for (size_t i = 0; i < instruct_set->size; i++) {
		switch (instruct_set->set[i]->instruct_type) {
			case (MOV_INSTRUCT):
				free_mov_instruct((t_mov_instruct *)instruct_set->set[i]);
				break ;
			default:
				break ;
		}
	}
	dyn_arr_free((void **)(&instruct_set->set));
}
