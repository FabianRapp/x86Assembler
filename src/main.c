#include <main.h>

void	cleanup(t_main *data) {
	free(data->input);
	free_instruct_set(&data->instruct_set);
}

const t_instruct	*get_basic_instruct(t_main *program, char *line) {

	for (size_t i = 0; i < program->instruct_set.size; i++) {
		const t_instruct	*instruct = program->instruct_set.set[i];
		char		*name = instruct->name;
		if (!strcmp(line, name)) {
			return (instruct);
		}
	}
	return (NULL);
}

bool	sep(char c) {
	return (isspace(c) || c == ',');
}

typedef enum e_operand_token_typen {
	GP_REG,
	SEG_REG,
	CTRL_REG,
	DEBUG_REG,
	SIMD_REG,
	PC_REG,
	X87_REG,
	DOLLAR,
	HEX_LITERAL,
	BIN_LITERAL,
	LITERAL,
	SIGNLE_QUOTE,
	DOUBLE_QUOTE,
	PARENTHESE_OPEN,
	PARENTHESE_CLOSE,
	COMMA,
	MINUS,
	COLUMN,
	ASTERIX,
}	t_operand_token_type;
typedef struct s_operand_token {

}	t_operand_token;


int	main(int ac, char *av[]) {
	t_main	data = {
		.input = NULL,
		.instruct_set.size = 0,
		.instruct_set.set = NULL,
	};
	init(&data, ac, av);
	char	**lines = ft_split(data.input, '\n');
	assert(lines && "malloc fail");
	char	*line;
	for (size_t idx_line = 0; (line = lines[idx_line]); idx_line++) {
		printf("line: %s\n", line);
		char	**instruct_parts = ft_split_fn(line, sep);
		if (!instruct_parts) {
			assert(0 && "mall fail");
		}
		const t_instruct	*instruct;
		instruct = get_basic_instruct(&data, instruct_parts[0]);
		assert(instruct && "broken");
		printf("%s\n", instruct->name);
		char	*operand_str;
		t_operand	operands[2];
		size_t		operand_idx = 0;
		for (size_t part_idx = 1;
			(operand_str = instruct_parts[part_idx]); part_idx++)
		{
			assert(operand_idx < 2 && "more than two operands per instruction");
			operands[operand_idx++];
			//todo parse operands: needs full lexer with parser
		}
		assert(operand_idx <= instruct->max_operands
			&& operand_idx >= instruct->min_operands && "wrong operand count");
		ft_free_2darr(instruct_parts);
	}
	ft_free_2darr(lines);
	cleanup(&data);
	return (0);
}
