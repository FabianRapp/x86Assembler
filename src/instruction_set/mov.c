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
	mov->max_operands = 2;
	mov->min_operands = 2;
	mov->len = 1;

	mov->name = strdup(name);
	assert(mov->name && "malloc fail");

	return (mov);
}
/*
	W: Enables 63-bit operand size.
	R: Extends the reg field in the ModR/M byte, allowing access to R8–R15 as destination registers.
	X: Extends the index field in the SIB byte for extended index registers.
	B: Extends the r/m field in the ModR/M byte, allowing access to R8–R15 as source operands or memory registers
*/
uint8_t	get_rex(bool w, bool r, bool x, bool b) {
	uint8_t	rex = 0;

	rex = 0b01000000;
	if (w) {
		rex |= 0b1000;
	}
	if (r) {
		rex |= 0b100;
	}
	if (x) {
		rex |= 0b10;
	}
	if (b) {
		rex |= 0b1;
	}
	return (rex);
}

//v1: refactor, correct and extend later
void	add_mov_instructs(t_instruct_set *instruct_set) {
	t_mov_instruct	*mov;

	//move gp-register to gp-register
	mov = new_mov_instruct("mov");
	mov->instruct[0] = get_rex(1, 0, 0, 0);
	//todo: incorrect*****
	mov->instruct[1] = 0x89;
	mov->len = 2;
	mov->operand_volume_min[0] = 1;
	mov->operand_volume_min[1] = 1;
	mov->operand_volume_max[0] = 8;
	mov->operand_volume_max[1] = 8;
	//********************
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movb");
	mov->instruct[0] = 0x88;
	mov->operand_volume_min[0] = 1;
	mov->operand_volume_min[1] = 1;
	mov->operand_volume_max[0] = 1;
	mov->operand_volume_max[1] = 1;
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movw");
	mov->instruct[0] = 0x89;
	mov->operand_volume_min[0] = 2;
	mov->operand_volume_min[1] = 2;
	mov->operand_volume_max[0] = 2;
	mov->operand_volume_max[1] = 2;
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movl");
	mov->instruct[0] = 0x89;
	mov->operand_volume_min[0] = 4;
	mov->operand_volume_min[1] = 4;
	mov->operand_volume_max[0] = 4;
	mov->operand_volume_max[1] = 4;
	add_instruct(instruct_set, mov);

	mov = new_mov_instruct("movq");
	mov->operand_volume_min[0] = 8;
	mov->operand_volume_min[1] = 8;
	mov->operand_volume_max[0] = 8;
	mov->operand_volume_max[1] = 8;
	mov->instruct[0] = get_rex(1, 0, 0, 0);
	mov->instruct[1] = 0x89;
	mov->len = 2;
	add_instruct(instruct_set, mov);

	//move segment-regster to gp-register
	//move gp-register to segment-register
	//move segment-offset to register
	//move gp-register to segment-offset
	//move immidiate to register
}

void	free_mov_instruct(t_mov_instruct *instruct) {
	t_mov_instruct	*mov = instruct;
	free(mov->name);
	free(mov);
}
