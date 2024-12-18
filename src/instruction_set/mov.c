#include <mov.h>

//reallocates the given data into a new instruction
t_instruct	new_mov_instruct(char *name) {
	t_instruct	mov;
	bzero(&mov, sizeof mov);

	mov.instruct_type = MOV_INSTRUCT;
	mov.len = 1;

	mov.name = strdup(name);
	assert(mov.name && "malloc fail");

	mov.operand_combinations = dyn_arr_init2(3, sizeof(t_operand_combination), 0, free_operand_combination);
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
void	add_mov_instructs(t_instruct_set *instruct_set,
			t_operand_set operand_sets[SET_OPERAND_COUNT])
{
	//move gp-register to gp-register
	{
		//TODO IDK THIS 
		t_instruct	mov;
		mov = new_mov_instruct("mov");
		mov.instruct[0] = get_rex(1, 0, 0, 0);
		//todo: incorrect*****
		mov.instruct[1] = 0x89;
		mov.len = 2;
		//********************
		add_instruct(instruct_set, mov);
	}
	{
		t_instruct	mov;
		mov = new_mov_instruct("movb");
		add_operand_combination(&mov,
			add_set_to_combination(new_operand_combination(),
				operand_sets + SET_GP_REG_1, operand_sets + SET_GP_REG_1)
		);
		mov.instruct[0] = 0x88;
		add_instruct(instruct_set, mov);
	}
	{
		t_instruct	mov;
		mov = new_mov_instruct("movw");
		add_operand_combination(&mov,
			add_set_to_combination(new_operand_combination(),
				operand_sets + SET_GP_REG_2, operand_sets + SET_GP_REG_2)
		);
		mov.instruct[0] = 0x89;
		add_instruct(instruct_set, mov);
	}

	{
		t_instruct	mov;
		mov = new_mov_instruct("movl");
		add_operand_combination(&mov,
			add_set_to_combination(new_operand_combination(),
				operand_sets + SET_GP_REG_4, operand_sets + SET_GP_REG_4)
		);
		mov.instruct[0] = 0x89;
		add_instruct(instruct_set, mov);
	}

	{
		t_instruct	mov;
		mov = new_mov_instruct("movq");
		add_operand_combination(&mov,
			add_set_to_combination(new_operand_combination(),
				operand_sets + SET_GP_REG_8, operand_sets + SET_GP_REG_8)
		);
		mov.instruct[0] = get_rex(1, 0, 0, 0);
		mov.instruct[1] = 0x89;
		mov.len = 2;
		add_instruct(instruct_set, mov);
	}

	//move segment-regster to gp-register
	//move gp-register to segment-register
	//move segment-offset to register
	//move gp-register to segment-offset
	//move immidiate to register
}

