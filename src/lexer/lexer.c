#include <lexer.h>

typedef enum e_token_type {
	TOKEN_UNKNOWN,
	TOKEN_SEP,
	TOKEN_DOT,
	TOKEN_COLUMN,
	TOKEN_WHITESPACE,
}	t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_lexer {
	char	*input;
	t_token	last_token;
	char	last;
	char	cur;
	char	next;
	size_t	pos;
}	t_lexer;

void	lex_read(t_lexer *lex) {
	assert(lex->input && "lexer had not input str");

	lex->cur = lex->input[lex->pos++];
	if (lex->cur) {
		lex->next = lex->input[lex->pos];
	} else {
		lex->next = 0;
	}
}

bool	lex_comment(t_lexer *lex, t_token *token) {

	return (false);
}

bool	lex_sep(t_lexer *lex, t_token *token) {
	char	signs_uncond[] = {'\n',};
	char	signs_cond[] = {';', '#'};

	for (size_t i = 0; i < sizeof signs_uncond / sizeof signs_uncond[0]; i++) {
		if (lex->cur == signs_uncond[i]) {
			token->type = TOKEN_SEP;
			return (true);
		}
	}
	for (size_t i = 0; i < sizeof signs_cond / sizeof signs_cond[0]; i++) {
		if (lex->cur == signs_cond[i] && lex->last_token.type != TOKEN_SEP) {
			token->type = TOKEN_SEP;
			return (true);
		}
	}
	return (false);
}

bool	lex_dot(t_lexer *lex, t_token *token) {
	char	signs[] = {'.',};

	for (size_t i = 0; i < sizeof signs / sizeof signs[0]; i++) {
		if (lex->cur == signs[i]) {
			token->type = TOKEN_DOT;
			return (true);
		}
	}
	return (false);
}

bool	lex_column(t_lexer *lex, t_token *token) {
	char	signs[] = {':',};

	for (size_t i = 0; i < sizeof signs / sizeof signs[0]; i++) {
		if (lex->cur == signs[i]) {
			token->type = TOKEN_COLUMN;
			return (true);
		}
	}
	return (false);
}

bool	lex_whitespace(t_lexer *lex, t_token *token) {
	if (!isspace(lex->cur) || lex->cur == '\n') {
		return (false);
	}
	while (lex->cur && isspace(lex->cur) && lex->cur != '\n') {
		lex_read(lex);
	}
	token->type = TOKEN_WHITESPACE;
	return (true);
}

t_token	lex_next(t_lexer *lex) {
	t_token	token;
	// order matters
	bool	(*typing[])(t_lexer*, t_token*) = {
		lex_comment,
		lex_sep,
		lex_dot,
		lex_column,
		lex_whitespace,
	};

	bzero(&token, sizeof token);
	for (size_t i = 0; i < sizeof typing / sizeof typing[0]; i++) {
		if (typing[i](lex, &token)) {
			return (token);
		}
	}
	assert(0 && "couldn't lex token");
	return (token);
}


