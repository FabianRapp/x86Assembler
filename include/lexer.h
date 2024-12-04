#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <ctype.h>

#include <libft.h>

#define LABEL_TYPE 0x1
#define DIRECTIVE_TYPE 0x2
#define COMMAND_TYPE 0x4

typedef enum e_token_type {
	TOKEN_UNKNOWN,
	TOKEN_SEP,
	TOKEN_COLUMN,
	TOKEN_MATH_OP,
	TOKEN_COMMA,
	TOKEN_COMMENT,
	TOKEN_WHITESPACE,
	TOKEN_REG,
	TOKEN_DOLLAR,
	TOKEN_STR_LITERAL,
	TOKEN_CHAR_LITERAL,
	TOKEN_NB_LITERAL,
	TOKEN_DIRECTIVE,
	TOKEN_IDENTIFIER,
	TOKEN_BRACE_OPEN,
	TOKEN_BRACE_CLOSE,
	TOKEN_EOF,
}	t_token_type;

typedef struct s_debug_info {
	size_t	line_idx;
	size_t	col_idx;
	char	*line;
}	t_debug_info;

typedef struct s_token	t_token;
typedef struct s_token {
	t_token_type	type;
	char			*str;
	t_debug_info	debug_info;
	t_token			*next;
}	t_token;

typedef struct s_lexer {
	char			*input;
	t_token			last_token;
	char			last;
	char			cur;
	char			next;
	size_t			pos;
	t_debug_info	debug_info;
}	t_lexer;

t_token	*clone_token(t_token *in);
void	free_token(t_token *token);
void	free_token_list(t_token *head);
void	free_token_list2(t_token **head);
t_token *lexer(char *data);
void	print_token_list(t_token *head);
void	print_token(t_token *token);

