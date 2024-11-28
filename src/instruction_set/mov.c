#include <mov.h>

static void	add_instruct(t_instruct_set *instruct_set, void *instruct)
{
	dyn_arr_add_save((void **)(&instruct_set->set), &instruct,
		instruct_set->size++);
}

//reallocates the given data into a new instruction
t_mov_instruct	*new_mov_instruct(char *name) {
	t_mov_instruct	*mov = calloc(1, sizeof(t_mov_instruct));
	assert(mov && "malloc fail");

	mov->instruct_type = MOV_INSTRUCT;

	mov->name = malloc(sizeof(char) * (1 + strlen(name)));
	assert(mov->name && "malloc fail");
	strcpy(mov->name, name);

	return (mov);
}

void	add_mov_instructs(t_instruct_set *instruct_set) {
	t_mov_instruct	*mov;

	//move gp-register to gp-register
	mov = new_mov_instruct("mov ");
	mov->dest = new_operand(GP_REGISTER_OPERAND);
	mov->src = new_operand(GP_REGISTER_OPERAND);
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movb ");
	mov->dest = new_operand(GP_REGISTER_OPERAND);
	mov->src = new_operand(GP_REGISTER_OPERAND);
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movw ");
	mov->dest = new_operand(GP_REGISTER_OPERAND);
	mov->src = new_operand(GP_REGISTER_OPERAND);
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movl ");
	mov->dest = new_operand(GP_REGISTER_OPERAND);
	mov->src = new_operand(GP_REGISTER_OPERAND);
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movq ");
	mov->dest = new_operand(GP_REGISTER_OPERAND);
	mov->src = new_operand(GP_REGISTER_OPERAND);
	add_instruct(instruct_set, mov);

	//move segment-regster to gp-register
	//move gp-register to segment-register
	//move segment-offset to register
	//move gp-register to segment-offset
	//move immidiate to register
}

void	free_mov_instruct(void *instruct) {
	t_mov_instruct	*mov = instruct;
	free(mov->name);
	free(mov->src.bin);
	free(mov->dest.bin);
	free(mov);
}
