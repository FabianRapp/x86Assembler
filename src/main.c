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


//TODO: think of something scaleable, maye refactor opernad typinf in some way
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


//

//

//
//typedef enum e_operand_token_typen {
//	OPERAND_ERROR=0,
//	GP_REG,
//	SEG_REG, //todo
//	CTRL_REG, //todo
//	DEBUG_REG, //todo
//	SIMD_REG, //todo
//	PC_REG, //todo
//	X87_REG, //todo
//	DOLLAR, //todo
//	HEX_LITERAL, //todo
//	BIN_LITERAL, //todo
//	LITERAL, //todo
//	SIGNLE_QUOTE, //todo
//	DOUBLE_QUOTE, //todo
//	PARENTHESE_OPEN, //todo
//	PARENTHESE_CLOSE, //todo
//	COMMA, //todo
//	MINUS, //todo
//	COLUMN, //todo
//	ASTERIX, //todo
//}	t_operand_token_type;
//
//typedef struct s_operand_token t_operand_token;
//
//typedef struct s_operand_token {
//	t_operand_token_type	type;
//	size_t					volume_size;
//	uint8_t					op_code[20];
//	size_t					binary_bits;
//	char					*content;
//	t_operand_token			*next;
//}	t_operand_token;
//
//bool	parse_register_list(char **operand_part, t_operand_token *token,
//			char **register_list, size_t list_size, uint8_t *op_codes) {
//	for (size_t i = 0; i < list_size; i++) {
//		size_t	len = strlen(register_list[i]);
//		if (!strncmp(register_list[i], *operand_part, len)) {
//			token->content = strndup(*operand_part, len);
//			assert(token->content && "malloc fail");
//			*operand_part += len;
//			token->op_code[0] = op_codes[i];
//			return (true);
//		}
//	}
//	return (false);
//}
//
////return the given token filled out
//t_operand_token	*parse_reg(char **operand_part, t_operand_token *token) {
//	char	*gp_1_byte[] = {"%al", "%cl", "%dl", "%bl", "%sil", "%dil", "%spl",
//		"%bpl", "%r8b", "%r9b", "%r10b", "%r11b", "%r12b", "%r13b", "%r14b", "%r15b", };
//	uint8_t	gp_1_byte_opcodes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
//		0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};
//
//	char	*gp_2_byte[] = {"%ax", "%cx", "%dx", "%bx", "%si", "%di", "%sp",
//		"%bp", "%r8w", "%r9w", "%r10w", "%r11w", "%r12w", "%r13w", "%r14w", "%r15w", };
//	uint8_t	gp_2_byte_opcodes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
//		0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};
//
//	char	*gp_4_byte[] = {"%eax", "%ecx", "%edx", "%ebx", "%esi", "%edi",
//		"%esp", "%ebp", "%r8d", "%r9d", "%r10d", "%r11d", "%r12d", "%r13d", "%r14d", "%r15d", };
//	uint8_t	gp_4_byte_opcodes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
//		0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};
//
//	char	*gp_8_byte[] = {"%rax", "%rcx", "%rdx", "%rbx", "%rsi", "%rdi", "%rsp",
//		"%rbp", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15", };
//	uint8_t	gp_8_byte_opcodes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
//		0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};
//
//	if (parse_register_list(operand_part, token, gp_1_byte,
//			sizeof gp_1_byte / sizeof gp_1_byte[0], gp_1_byte_opcodes)) {
//		token->volume_size = 1;
//		token->binary_bits = 3;
//		token->type = GP_REG;
//		return (token);
//	}
//	if (parse_register_list(operand_part, token, gp_2_byte,
//			sizeof gp_1_byte / sizeof gp_1_byte[0], gp_2_byte_opcodes)) {
//		token->volume_size = 2;
//		token->binary_bits = 3;
//		token->type = GP_REG;
//		return (token);
//	}
//	if (parse_register_list(operand_part, token, gp_4_byte,
//			sizeof gp_1_byte / sizeof gp_1_byte[0], gp_4_byte_opcodes)) {
//		token->volume_size = 4;
//		token->binary_bits = 3;
//		token->type = GP_REG;
//		return (token);
//	}
//	if (parse_register_list(operand_part, token, gp_8_byte,
//			sizeof gp_1_byte / sizeof gp_1_byte[0], gp_8_byte_opcodes)) {
//		token->volume_size = 8;
//		token->binary_bits = 3;
//		token->type = GP_REG;
//		return (token);
//	}
//	assert(0 && "unsupported operand register");
//	__builtin_unreachable();
//}
//
//t_operand_token	*next_operand_token(char **operand_part) {
//	t_operand_token	*token = calloc(1, sizeof(t_operand_token));
//	assert(token && "malloc fail");
//	switch (**operand_part) {
//		case ('%'):
//			return (parse_reg(operand_part, token));
//		case (','):
//			token->type = COMMA;
//			token->content = strdup(",");
//			operand_part[0]++;
//			return (token);
//		default: assert(0 && "unsupported operand");
//	}
//
//	__builtin_unreachable();
//}
//
//void	free_operand_token_list(t_operand_token *list) {
//	t_operand_token	*last;
//
//	while (list) {
//		last = list;
//		list = list->next;
//		free(last->content);
//		free(last);
//	}
//}
//
//t_operand_token	*lex_operand(char *operand_part) {
//	if (!operand_part) {
//		return (NULL);
//	}
//	t_operand_token	head = {.next=NULL};
//	t_operand_token	*cur = &head;
//	while (*operand_part) {
//		cur->next = next_operand_token(&operand_part);
//		if (head.next && cur == head.next && cur->next->type == COMMA) {
//			free(cur->next->content);
//			free(cur->next);
//			cur->next = NULL;
//		} else {
//			cur = cur->next;
//		}
//	}
//	return (head.next);
//}
//
//t_operand_token	parse_operand(t_operand_token *token_list) {
//	t_operand_token	operand = {.next=NULL};
//	t_operand_token	*cur = token_list;
//
//	if (!cur->next) {
//		assert(cur->type != OPERAND_ERROR && "operand token type not set");
//		operand = *cur;
//		operand.content = strdup(cur->content);
//		operand.next = NULL;
//		assert(operand.content && "mall fail");
//		return (operand);
//	}
//	printf("%s\n", cur->next->content);
//	assert(0 && "token list longer than 1 should not be implemented yet?");
//	__builtin_unreachable();
//}
//

//
//int	main(int ac, char *av[]) {
//	t_main	data = {
//		.input = NULL,
//		.instruct_set.size = 0,
//		.instruct_set.set = NULL,
//	};
//	init(&data, ac, av);
//	char	**lines = ft_split(data.input, '\n');
//	assert(lines && "malloc fail");
//	char	*line;
//	for (size_t idx_line = 0; (line = lines[idx_line]); idx_line++) {
//		printf("line: %s\n", line);
//		char	**instruct_parts = ft_split_fn(line, sep);
//		if (!instruct_parts) {
//			assert(0 && "mall fail");
//		}
//		const t_instruct	*instruct;
//		instruct = get_basic_instruct(&data, instruct_parts[0]);
//		for (size_t i = 0; i < instruct->len; i++) {
//			printf("%u\n", instruct->instruct[i]);
//		}
//		assert(instruct && "broken");
//		printf("%s\n", instruct->name);
//		char	*operand_str;
//		t_operand_token	operands[2];
//		int				operand_idx = 0;
//		for (size_t part_idx = 1;
//			(operand_str = instruct_parts[part_idx]); part_idx++)
//		{
//			assert(operand_idx < 2 && "more than two operands per instruction");
//			t_operand_token	*operand_list = lex_operand(operand_str);
//			operands[operand_idx] = parse_operand(operand_list);
//			assert(operands[operand_idx].volume_size
//					>= instruct->operand_volume_min[operand_idx]
//				&& operands[operand_idx].volume_size
//					<= instruct->operand_volume_max[operand_idx]
//				&& "operand volume missmtach!"
//			);
//			operand_idx++;
//			free_operand_token_list(operand_list);
//		}
//		output_opcode(&data, instruct, operands, operand_idx);
//		for (int i = 0; i < operand_idx; i++) {
//			free(operands[i].content);
//		}
//		assert(operand_idx <= instruct->max_operands
//			&& operand_idx >= instruct->min_operands && "wrong operand count");
//		ft_free_2darr(instruct_parts);
//
//	}
//	ft_free_2darr(lines);
//	cleanup(&data);
//	return (0);
//}
