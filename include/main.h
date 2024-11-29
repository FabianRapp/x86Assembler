#pragma once

#include <string.h>
#include <assert.h>
#include <libft.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include <instruction_set.h>

typedef struct s_main {
	char				*input;
	t_instruct_set	instruct_set;
}	t_main;

void	init(t_main *data, int ac, char *av[]);
