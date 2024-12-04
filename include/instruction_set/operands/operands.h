#ifndef OPERANDS_H
# define OPERANDS_H


#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>
#include <stdbool.h>

#include <libft.h>

typedef struct s_instruct t_instruct;

enum e_operand_type {
	OPERAND_ERROR=0,
	EMPTY_OPERAND,
	//GP_REG,
	GP_REG1,
	GP_REG2,
	GP_REG4,
	GP_REG8,
	SEG_REG, //todo
	CTRL_REG, //todo
	DEBUG_REG, //todo
	SIMD_REG, //todo
	PC_REG, //todo
	X87_REG, //todo
	LITERAL, //todo
};
typedef struct s_operand	t_operand;

typedef struct s_operand_type {
	enum e_operand_type			type;
	bool						(*is_type)(char *operand_str);
	t_operand					(*new_operand)(char *operand_str);
}	t_operand_type;

void	free_operand_type(t_operand_type *type);

typedef struct s_operand {
	enum e_operand_type		type;
	t_operand				*sub_operands;
	size_t					volume_size;//eg.:al:1, ax:2, eax:4, rax:8
	uint8_t					op_code[20];//idk should be enough i think
	size_t					binary_bits;//count of op_code bits
	char					*content;
}	t_operand;

void	free_operand(t_operand *operand);

typedef enum e_operand_set_type {
	SET_OPERAND_ERROR,
	SET_OPERAND_EMPTY,
	//SET_OPERAND_MASTER,
	//SET_GP_REG,
	SET_GP_REG_1,
	SET_GP_REG_2,
	SET_GP_REG_4,
	SET_GP_REG_8,
	SET_OPERAND_COUNT
}	t_operand_set_type;

typedef struct s_operand_set	t_operand_set;
typedef struct s_operand_set
{
	t_operand_set_type	set_type;
	size_t				sub_set_count;
	t_operand_set		*sub_sets;
	t_operand_type		*set;
	size_t				count;
}	t_operand_set;


void			init_leaf_operand_sets(
					t_operand_set leaf_opernad_sets[SET_OPERAND_COUNT]);

void			free_operand_set(t_operand_set *operand_set);

/*****************************operand combinations****************************/

typedef struct s_opernad_combination {
	t_operand_set	*left;
	size_t			left_count;
	t_operand_set	*right;
	size_t			right_count;
}	t_operand_combination;

t_operand_combination	new_operand_combination(void);

//add_set_to_combination takes pointers but does allocate copies itself
//the only reason it takes pointers is so there is a simply way to pass
//either a left/right or both sets
t_operand_combination	add_set_to_combination(t_operand_combination combi,
							const t_operand_set *add_left,
							const t_operand_set *add_right);
void					add_operand_combination(t_instruct *instruct,
							t_operand_combination combi);

void			free_operand_combination(t_operand_combination *combination);
/*****************************************************************************/
//constructors for specific types(parses the specifc type)
t_operand		_gp_reg(char *operand_str);
//todo: others

//t_operand	new_operand(t_operand_set set, char *operand_str);

void	new_operand(const t_instruct instruct, char *operand_str1,
			char *operand_str2, t_operand operands[2]);

//base leaf set initializers:
t_operand_set	set_operand_error(void);
t_operand_set	set_operand_empty(void);
t_operand_set	set_gp_reg1(void);
t_operand_set	set_gp_reg2(void);
t_operand_set	set_gp_reg4(void);
t_operand_set	set_gp_reg8(void);

//base leaf initialzers utils:
t_operand_set	new_operand_set(t_operand_set_type set_type);
void			operand_set_add_sub_set(t_operand_set *set, t_operand_type type);
void			operand_set_add_type(t_operand_set *set, t_operand_type type);

#endif //OPERANDS_H
