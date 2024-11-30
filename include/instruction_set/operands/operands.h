#ifndef OPERANDS_H
# define OPERANDS_H


#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>
#include <stdbool.h>

#include <libft.h>

//typedef enum e_operand_token_typen {
//	TOKEN_OPERAND_ERROR=0,
//	TOKEN_GP_REG,
//	TOKEN_SEG_REG, //todo
//	TOKEN_CTRL_REG, //todo
//	TOKEN_DEBUG_REG, //todo
//	TOKEN_SIMD_REG, //todo
//	TOKEN_PC_REG, //todo
//	TOKEN_X87_REG, //todo
//	TOKEN_DOLLAR, //todo
//	TOKEN_HEX_LITERAL, //todo
//	TOKEN_BIN_LITERAL, //todo
//	TOKEN_LITERAL, //todo
//	TOKEN_SIGNLE_QUOTE, //todo
//	TOKEN_DOUBLE_QUOTE, //todo
//	TOKEN_PARENTHESE_OPEN, //todo
//	TOKEN_PARENTHESE_CLOSE, //todo
//	TOKEN_COMMA, //todo
//	TOKEN_MINUS, //todo
//	TOKEN_COLUMN, //todo
//	TOKEN_ASTERIX, //todo
//}	t_operand_token_type;
//
//typedef struct s_operand_token	t_operand_token;
//typedef struct s_operand_token {
//	t_operand_token_type	type;
//	char					*content;
//	t_operand_token			*next;
//}	t_operand_token;
enum e_operand_type {
	OPERAND_ERROR=0,
	GP_REG,
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
	enum e_operand_type	type;
	bool				(*const is_type)(char *operand_str);
	t_operand			(*const new_operand)(char *operand_str);
}	t_operand_type;

typedef struct s_operand {
	enum e_operand_type		type;
	size_t					volume_size;//eg.:al:1, ax:2, eax:4, rax:8
	uint8_t					op_code[20];//idk should be enough i think
	size_t					binary_bits;//count of op_code bits
	char					*content;
}	t_operand;

void	free_operand(t_operand operand);

typedef struct s_operand_set	t_operand_set;
typedef struct s_operand_set
{
	t_operand_type	*set;
	size_t			count;
	t_operand		(*const new_operand)(t_operand_set this,
						char *operand_str);
}	t_operand_set;

t_operand_set	new_operand_set(void);
void			free_operand_set(t_operand_set operand_set);

//constructors for specific types(parses the specifc type)
t_operand		_gp_reg(char *operand_str);
//todo: others


#endif //OPERANDS_H
