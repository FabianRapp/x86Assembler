#pragma once

#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <stdnoreturn.h>
#include <elf.h>

#include <my_elf.h>
#include <libft.h>
#include <lexer.h>
#include <ir.h>
#include <instruction_set.h>
#include <operands.h>

// todo: make operand sets that represent the diffrent rex groups
/*
https://wiki.osdev.org/X86-64_Instruction_Encoding :
use when:
	-using 64-bit operand size and the instruction does not default to 64-bit operand size; or
    -using one of the extended registers (R8 to R15, XMM8 to XMM15, YMM8 to YMM15, CR8 to CR15 and DR8 to DR15); or
    -using one of the uniform byte registers SPL, BPL, SIL or DIL.
not allowed when AH, CH, BH or DH is used
otherwise ignored, tho multiple rex bytes are undefined
	excetions that don't need rex prefix exists
 	(eg.: pushq (pushl not encodable), callq and more (mostly stack ops)
 	only for long mode
*/
typedef union u_rex {
	uint8_t			buf;
	struct {
		uint8_t		pad : 1;
		uint8_t		enable : 1;
		uint8_t		pad2 : 2;

/* w: When 1, a 64-bit operand size is used. Otherwise, when 0, the default
	operand size is used (which is 32-bit for most but not all instructions, see
https://wiki.osdev.org/X86-64_Instruction_Encoding#Operand-size_and_address-size_override_prefix )
*/
		uint8_t		w : 1;
		uint8_t		r : 1;
		uint8_t		x : 1;
		uint8_t		b : 1;//new registers eg r9
	};
}	t_rex;

//eg.: SIMD prefix (0x66, 0xF2 or 0xF3)
typedef union u_mandetory_prefix {
	int8_t		buf;
	struct {
	};
}	t_mandetory_prefix;

typedef struct s_prefix {
	t_mandetory_prefix	mand;
	t_rex				rex;
}	t_prefix;

//0 bytes are skiped
//todo
typedef struct s_op_code_bin {
	t_prefix	prefix;
	uint8_t		escape_seq[2];
	
}	t_op_code_bin;



typedef struct s_main {
	t_operand_set			leaf_operand_sets[SET_OPERAND_COUNT];
	uint8_t					*bin;
	size_t					bin_size;

	char					*input;
	t_instruct_set			instruct_set;
	int						output;
}	t_main;

void	init(t_main *data, int ac, char *av[]);
