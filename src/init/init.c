#include <main.h>

void	read_file(char *file_name, char **buffer) {
	struct stat	file_stat;
	int			fd;

	if (*buffer) {
		ft_free((void**)buffer);
	}
	if (stat(file_name, &file_stat) == -1) {
		if (errno == ENOENT) {
			assert(0 && "file does not exist");
		} else {
			assert(0 && "stat failed for an unknown reason");
		}
	}
	assert(file_stat.st_size && "read file has size 0");
	*buffer = malloc(file_stat.st_size * sizeof(char) + 1);
	buffer[0][file_stat.st_size] = 0;
	assert(*buffer && "malloc failed");
	fd = open(file_name, O_RDONLY);
	assert(fd > 0 && "couldn't open input file");
	if (read(fd, *buffer, file_stat.st_size) != file_stat.st_size) {
		assert(0 && "error reading input file");
	}
}

void	get_input(t_main *data, int ac, char *av[]) {
	char	input_file[1024];

	if (ac == 1) {
		strcpy(input_file, "input.asm");
	} else if (ac == 2) {
		if (strlen(av[1]) > (sizeof input_file - 1)) {
			assert(0 && "input file name too long");
		}
		strcpy(input_file, av[1]);
	} else {
		assert(0 && "more than 1 input given");
	}
	read_file(input_file, &data->input);
}


void	init(t_main *data, int ac, char *av[]) {
	bzero(data, sizeof *data);

	init_leaf_operand_sets(data->leaf_operand_sets);
	data->instruct_set = init_instruct_set(data->leaf_operand_sets);
	data->bin = dyn_arr_init2(3, sizeof(uint8_t), 0, NULL);
	assert(data->bin && "malloc fail");

	//data->operand_set = new_operand_set(SET_OPERAND_MASTER);

	get_input(data, ac, av);

	char	*output_path = "out.bin";
	mode_t	permissions = S_IRWXU | S_IRUSR | S_IWUSR |S_IXUSR;
	data->output = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, permissions);
	assert(data->output > 0 && "could't open output file");
}

