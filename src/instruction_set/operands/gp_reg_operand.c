#include <operands.h>

static t_operand	_new_gp_reg1(char *str) {
	t_operand	operand = {
		.type = GP_REG1,
		.volume_size = 8,
		.binary_bits = 3,
		.op_code = {0},
		.content = strdup(str),
	};
	char *regs[] =	{"%al", "%cl", "%dl", "%bl", "%sil", "%dil", "%spl", "%bpl",
		"%r8b", "%r9b", "%r10b", "%r11b", "%r12b", "%r13b", "%r14b", "%r15b",};
	uint8_t	op_codes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
			0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};

	assert(sizeof op_codes / sizeof op_codes[0] == sizeof regs / sizeof regs[0]
		&& "arrays are wrong");
	assert(operand.content && "malloc fail");

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			operand.op_code[0] = op_codes[i];
			return (operand);
		}
	}
	assert(0 && "Should never be reached");
	__builtin_unreachable();
}

static bool	_is_gp_reg1(char *str) {
	if (!str) {
		return (false);
	}
	char *regs[] =	{"%al", "%cl", "%dl", "%bl", "%sil", "%dil", "%spl", "%bpl",
		"%r8b", "%r9b", "%r10b", "%r11b", "%r12b", "%r13b", "%r14b", "%r15b",};

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			return (true);
		}
	}
	return (false);
}

//to initialze the leaf array
t_operand_set	set_gp_reg1(void) {
	t_operand_set	set = new_operand_set(SET_GP_REG_1);
	t_operand_type	type = {
		.type = GP_REG1,
		.is_type = _is_gp_reg1,
		.new_operand = _new_gp_reg1,
	};
	operand_set_add_type(&set, type);
	return (set);
}

static t_operand	_new_gp_reg2(char *str) {
	t_operand	operand = {
		.type = GP_REG2,
		.volume_size = 8,
		.binary_bits = 3,
		.op_code = {0},
		.content = strdup(str),
	};
	char *regs[] =	{"%ax", "%cx", "%dx", "%bx", "%si", "%di", "%sp", "%bp",
		"%r8w", "%r9w", "%r10w", "%r11w", "%r12w", "%r13w", "%r14w", "%r15w",};
	uint8_t	op_codes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110,
		0b111, 0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};

	assert(sizeof op_codes / sizeof op_codes[0] == sizeof regs / sizeof regs[0]
		&& "arrays are wrong");
	assert(operand.content && "malloc fail");

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			operand.op_code[0] = op_codes[i];
			return (operand);
		}
	}
	assert(0 && "Should never be reached");
	__builtin_unreachable();
}

static bool	_is_gp_reg2(char *str) {
	if (!str) {
		return (false);
	}
	char *regs[] =	{"%ax", "%cx", "%dx", "%bx", "%si", "%di", "%sp", "%bp",
		"%r8w", "%r9w", "%r10w", "%r11w", "%r12w", "%r13w", "%r14w", "%r15w",};

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			return (true);
		}
	}
	return (false);
}

//to initialze the leaf array
t_operand_set	set_gp_reg2(void) {
	t_operand_set	set = new_operand_set(SET_GP_REG_2);
	t_operand_type	type = {
		.type = GP_REG2,
		.is_type = _is_gp_reg2,
		.new_operand = _new_gp_reg2,
	};
	operand_set_add_type(&set, type);
	return (set);
}

static t_operand	_new_gp_reg4(char *str) {
	t_operand	operand = {
		.type = GP_REG4,
		.volume_size = 8,
		.binary_bits = 3,
		.op_code = {0},
		.content = strdup(str),
	};
	char *regs[] =	{"%eax", "%ecx", "%edx", "%ebx", "%esi", "%edi", "%esp",
		"%ebp", "%r8d", "%r9d", "%r10d", "%r11d", "%r12d", "%r13d", "%r14d",
		"%r15d",
	};
	uint8_t	op_codes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110,
		0b111, 0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};

	assert(sizeof op_codes / sizeof op_codes[0] == sizeof regs / sizeof regs[0]
		&& "arrays are wrong");
	assert(operand.content && "malloc fail");

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			operand.op_code[0] = op_codes[i];
			return (operand);
		}
	}
	assert(0 && "Should never be reached");
	__builtin_unreachable();
}

static bool	_is_gp_reg4(char *str) {
	if (!str) {
		return (false);
	}
	char *regs[] =	{"%eax", "%ecx", "%edx", "%ebx", "%esi", "%edi", "%esp",
		"%ebp", "%r8d", "%r9d", "%r10d", "%r11d", "%r12d", "%r13d", "%r14d",
		"%r15d",
	};

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			return (true);
		}
	}
	return (false);
}

//to initialze the leaf array
t_operand_set	set_gp_reg4(void) {
	t_operand_set	set = new_operand_set(SET_GP_REG_4);
	t_operand_type	type = {
		.type = GP_REG4,
		.is_type = _is_gp_reg4,
		.new_operand = _new_gp_reg4,
	};
	operand_set_add_type(&set, type);
	return (set);
}

static t_operand	_new_gp_reg8(char *str) {
	t_operand	operand = {
		.type = GP_REG8,
		.volume_size = 8,
		.binary_bits = 3,
		.op_code = {0},
		.content = strdup(str),
	};
	char *regs[] =	{"%rax", "%rcx", "%rdx", "%rbx", "%rsi", "%rdi", "%rsp",
		"%rbp", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15",};
	uint8_t	op_codes[] = {0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
			0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111};

	assert(sizeof op_codes / sizeof op_codes[0] == sizeof regs / sizeof regs[0]
		&& "arrays are wrong");
	assert(operand.content && "malloc fail");

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			operand.op_code[0] = op_codes[i];
			return (operand);
		}
	}
	assert(0 && "Should never be reached");
	__builtin_unreachable();
}

static bool	_is_gp_reg8(char *str) {
	if (!str) {
		return (false);
	}
	char *regs[] =	{"%rax", "%rcx", "%rdx", "%rbx", "%rsi", "%rdi", "%rsp",
		"%rbp", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15",};

	for (size_t i = 0; i < sizeof regs / sizeof regs[0]; i++) {
		if (!strcmp(regs[i], str)) {
			return (true);
		}
	}
	return (false);
}

//to initialze the leaf array
t_operand_set	set_gp_reg8(void) {
	t_operand_set	set = new_operand_set(SET_GP_REG_8);
	t_operand_type	type = {
		.type = GP_REG8,
		.is_type = _is_gp_reg8,
		.new_operand = _new_gp_reg8,
	};
	operand_set_add_type(&set, type);
	return (set);
}
