#include <operands.h>
#include "operand_types.h"

void	_add_gp_reg_type(t_operand_set *set) {
	t_operand_type	gp_reg = {
		.type = GP_REG,
		.is_type = _is_gp_reg,
		.new_operand = _new_gp_reg,
	};
	dyn_arr_add_save((void**)&set->set, &gp_reg, set->count++);
}

static t_operand_type	_match_type(t_operand_set set, char *operand_str) {
	for (size_t i = 0; i < set.count; i++) {
		if (set.set[i].is_type(operand_str)) {
			return (set.set[i]);
		}
	}
	assert(0 && "couldn't match operand type");
	__builtin_unreachable();
}

static t_operand	_new_operand(t_operand_set set, char *operand_str) {
	t_operand_type	type = _match_type(set, operand_str);

	return (type.new_operand(operand_str));
}

t_operand_set	new_operand_set(void) {
	t_operand_set	set = {
		.set = dyn_arr_init(sizeof(t_operand_type), 1),
		.new_operand = _new_operand,
	};
	assert(set.set && "malloc fail");
	_add_gp_reg_type(&set);
	return (set);
}

