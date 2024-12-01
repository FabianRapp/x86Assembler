#include <operands.h>
#include <instruction_types.h>

// frees the content, not the struct it self
void	free_operand_type(t_operand_type *type) {
	(void)type;
}

// frees the content, not the struct it self
void	free_operand(t_operand *operand) {
	free(operand->content);
}

// frees the content, not the struct it self
void	free_operand_set(t_operand_set *operand_set) {
	for (size_t i = 0; i < operand_set->sub_set_count; i++) {
		free_operand_set(operand_set->sub_sets + i);
	}
	dyn_arr_free((void **)(&operand_set->sub_sets));
	dyn_arr_free((void **)(&operand_set->set));
}

// frees the content, not the struct it self
void	free_operand_combination(t_operand_combination *combination) {
	dyn_arr_free((void **)&combination->left);
	dyn_arr_free((void **)&combination->right);
	combination->left_count = 0;
	combination->right_count = 0;
}
