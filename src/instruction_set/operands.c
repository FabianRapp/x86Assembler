#include <operands.h>

t_operand	new_operand(t_operand_type type) {
	t_operand	operand;

	bzero(&operand, sizeof operand);
	operand.type = type;
	switch(type) {
		case (GP_REGISTER_OPERAND):
		case (SEGMENT_REGISTER_OPERAND):
			operand.bin_bits = 3;
			break ;
		case (MEMORY_OPERAND):
			operand.bin_bits = UNKNOWN_SIZE;
			break ;
		case (SEGMENT_OFFSET_OPERAND):
			operand.bin_bits = UNKNOWN_SIZE;
			break ;
		case (IMMEDIATE_OPERAND):
			operand.bin_bits = UNKNOWN_SIZE;
			break ;
	}
	assert(!operand.bin);
	return (operand);
}
