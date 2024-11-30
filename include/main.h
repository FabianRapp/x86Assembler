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

#include <libft.h>
#include <instruction_set.h>
#include <operands.h>

typedef struct s_main {
	char					*input;
	const t_instruct_set	instruct_set;
	const t_operand_set		operand_set;
	int						output;
}	t_main;

void	init(t_main *data, int ac, char *av[]);
