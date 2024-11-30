#include <operands.h>

void	free_operand(t_operand operand) {
	free(operand.content);
}

void	free_operand_set(t_operand_set operand_set) {
	dyn_arr_free((void **)(&operand_set.set));
}
