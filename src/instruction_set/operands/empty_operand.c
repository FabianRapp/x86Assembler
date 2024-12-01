#include <operands.h>

static bool	_is_empty_type(char *str) {
	if (!str || strlen(str) == 0) {
		return (true);
	}
	return (false);
}

static t_operand	_new_empty_operand(char *str) {
	t_operand	operand = {
		.type = EMPTY_OPERAND,
		.volume_size = 0,
		.binary_bits = 0,
		.content = NULL,
	};
	(void)str;
	return (operand);
}

//only call this to inito the leaf operand array
t_operand_set	set_operand_empty(void) {
	t_operand_type	type = {
		.type = EMPTY_OPERAND,
		.is_type = _is_empty_type,
		.new_operand = _new_empty_operand,
	};
	t_operand_set	empty_set = new_operand_set(SET_OPERAND_EMPTY);
	operand_set_add_type(&empty_set, type);
	return (empty_set);
}
