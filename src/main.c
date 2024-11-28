#include <main.h>

void	cleanup(t_main *data) {
	free(data->input);
	free_instruct_set(&data->instruct_set);
}

int	main(int ac, char *av[]) {
	t_main	data = {
		.input = NULL,
		.instruct_set.size = 0,
		.instruct_set.set = NULL,
	};
	init(&data, ac, av);

	char *dummy = "movl %rax, %rbx";
	t_mov_instruct	*instruct = NULL;
	for (size_t i = 0; i < data.instruct_set.size; i++) {
		if (!strncmp(dummy, data.instruct_set.set[i]->name,
			strlen(data.instruct_set.set[i]->name)))
		{
			instruct = data.instruct_set.set[i];
			break ;
		}
	}
	printf("%s\n", instruct->name);

	cleanup(&data);
	return (0);
}
