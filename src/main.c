#include <main.h>

noreturn void	cleanup(t_main *data) {
	free(data->input);
	free_instruct_set(data->instruct_set);
	//free_operand_set(&data->operand_set);
	close(data->output);
	for (t_operand_set_type i = 0; i < SET_OPERAND_COUNT; i++) {
		free_operand_set(data->leaf_operand_sets + i);
	}
	exit(0);
}

static bool	sep(char c) {
	return (isspace(c));
}

//ignore compiler warnong the the 'const' return val is ignored to keep it
//for readbility
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"

//DO NOT modify the returned instruction: pointers lead to allocation in the
//main instruction set
//TODO: first parse operands then parse instruction, quite large refactor but 
//basic data structure idea should work for that
const t_instruct	get_basic_instruct(t_main *program, char *line) {
	for (size_t i = 0; i < program->instruct_set.size; i++) {
		const t_instruct	instruct = program->instruct_set.set[i];
		char		*name = instruct.name;
		if (!strcmp(line, name)) {
			return (instruct);
		}
	}
	assert(0 && "invalid instruction");
	__builtin_unreachable();
}

#pragma GCC diagnostic pop

void	output_2gp_regs(t_main *data, t_operand operand[2])
{
	uint8_t	bits = operand[0].binary_bits + operand[1].binary_bits;
	assert(bits == 6
		&& "unsupported operand opcode size: larger than 1 byte");
	uint8_t	code = ~((1 << bits) - 1);// to set the unused bits with 1
	//shift the register codes into position
	code |= ((operand[0].op_code[0] << operand[0].binary_bits)
			| (operand[1].op_code[0]));
	assert(write(data->output, &code, 1) != -1
		&& "write fail");
}


//TODO: think of something scaleable, maye refactor opernad typinfo in some way
//prob do refactor later when it might be more obvious how
void	output_operands(t_main *data, t_operand operand[2],
		int operand_count)
{
	if (operand_count == 2) {
		printf("%s\n%s\n",operand[0].content, operand[1].content);
		switch (operand[0].type) {
			case (GP_REG1):
			case (GP_REG2):
			case (GP_REG4):
			case (GP_REG8):
				switch (operand[1].type) {
					case (GP_REG1):
					case (GP_REG2):
					case (GP_REG4):
					case (GP_REG8):
						output_2gp_regs(data, operand);
						break ;
				default:
					assert(0 && "opernad 1 has not implemented type");
				}
				break ;
			default:
				assert(0 && "opernad 0 has not implemented type");
		}
		return ;
	}
	printf("oerpand_count: %d\n", operand_count);
	assert(0 && "unsupported operand combination");
}

void	output_opcode(t_main *data, const t_instruct instruct,
			t_operand operand[2], int operand_count)
{
	//prefix with operation codes (prefix is defined in instruction set atm)
		assert(write(data->output, instruct.instruct, instruct.len) != -1
			&& "write fail");
	output_operands(data, operand, operand_count);
		//todo:
	//ModR/M byte
	//SIB byte
	//Displacement
	//Immediate
}

void	process_instruction(t_main *data, const char *instruction_str) {
	printf("instruction input: %s\n", instruction_str);
	char	**instruct_parts = ft_split_fn(instruction_str, sep);
	if (!instruct_parts) {
		assert(0 && "mall fail");
	}
	if (!instruct_parts[0]) {
		free(instruct_parts);
		return ;
	}
	const t_instruct	instruct = get_basic_instruct(data, instruct_parts[0]);
	for (size_t i = 0; i < instruct.len; i++) {
		printf("%u\n", instruct.instruct[i]);
	}
	printf("%s\n", instruct.name);
	char		*operand_str;
	int			operand_idx = 0;
	t_operand	operands[2];
	for (size_t part_idx = 1;
		(operand_str = instruct_parts[part_idx]); part_idx++)
	{
		if (operand_str[strlen(operand_str) - 1] == ',') {
			operand_str[strlen(operand_str) - 1] = 0;
		}
		operand_idx++;
	}
	if (operand_idx == 0) {
		//todo
		assert(0);
	} else if (operand_idx == 1) {
		//todo
		assert(0);
	} else if (operand_idx == 2) {
		new_operand(instruct, instruct_parts[1], instruct_parts[2], operands);
	} else {
		assert(0 && "more than two operands per instruction");
	}
	output_opcode(data, instruct, operands, operand_idx);
	for (int i = 0; i < operand_idx; i++) {
		free_operand(operands + i);
	}
	//assert(operand_idx <= instruct->max_operands
	//	&& operand_idx >= instruct->min_operands && "wrong operand count");
	ft_free_2darr(instruct_parts);
}

int	main(int ac, char *av[]) {
	t_main	data;

	init(&data, ac, av);
	char	**lines = ft_split(data.input, '\n');
	assert(lines && "malloc fail");
	char	*line;
	for (size_t idx_line = 0; (line = lines[idx_line]); idx_line++) {
		process_instruction(&data, line);
	}
	ft_free_2darr(lines);
	cleanup(&data);
}
