#include <lexer.h>

const char *token_type_to_str(t_token_type token) {
    switch (token) {
        case TOKEN_UNKNOWN:       return "TOKEN_UNKNOWN";
        case TOKEN_SEP:           return "TOKEN_SEP";
        case TOKEN_COLUMN:        return "TOKEN_COLUMN";
        case TOKEN_MATH_OP:       return "TOKEN_MATH_OP";
        case TOKEN_COMMA:         return "TOKEN_COMMA";
        case TOKEN_COMMENT:       return "TOKEN_COMMENT";
        case TOKEN_WHITESPACE:    return "TOKEN_WHITESPACE";
        case TOKEN_REG:           return "TOKEN_REG";
        case TOKEN_DOLLAR:        return "TOKEN_DOLLAR";
        case TOKEN_STR_LITERAL:   return "TOKEN_STR_LITERAL";
        case TOKEN_CHAR_LITERAL:  return "TOKEN_CHAR_LITERAL";
        case TOKEN_NB_LITERAL:    return "TOKEN_NB_LITERAL";
        case TOKEN_DIRECTIVE:     return "TOKEN_DIRECTIVE";
        case TOKEN_IDENTIFIER:    return "TOKEN_IDENTIFIER";
        case TOKEN_BRACE_OPEN:    return "TOKEN_BRACE_OPEN";
        case TOKEN_BRACE_CLOSE:   return "TOKEN_BRACE_CLOSE";
        case TOKEN_EOF:           return "TOKEN_EOF";
        default:                  return "UNKNOWN_TOKEN_TYPE";
    }
}

void	lex_print(t_lexer *lex) {
	printf("lexer: \n");
	printf("pos: %lu\n", lex->pos);
	printf("last: %c\n", lex->last);
	printf("cur: %c\n", lex->cur);
	printf("next: %c\n", lex->next);
	char *tmp = ft_substr(lex->input, lex->pos, lex->pos + 10);
	assert(tmp && "malloc fail");
	printf("input + pos: |%s|..\n", tmp);
	free(tmp);
	printf("last token: ");
	print_token(&lex->last_token);
	printf("line %lu\n", lex->debug_info.line_idx);
}

t_debug_info	lex_make_debug_info(t_lexer *lex) {
	t_debug_info	info = {
		.line_idx = 0,
		.col_idx = 0,
		.line = lex->input,
	};
	return (info);
	(void)lex;
}

void	lex_read(t_lexer *lex) {
	assert(lex->input && "lexer had not input str");
	lex->debug_info.col_idx++;
	lex->last = lex->cur;
	lex->cur = lex->input[++lex->pos];
	if (lex->cur) {
		lex->next = lex->input[lex->pos + 1];
	} else {
		lex->next = 0;
	}
	if (lex->last == '\n') {
		lex->debug_info.col_idx = 0;
		free(lex->debug_info.line);
		lex->debug_info.line_idx++;
		char	*line_begin = lex->input + lex->pos;
		size_t	line_len = strchr(line_begin, '\n') - line_begin;
		lex->debug_info.line = strndup(lex->input + lex->pos, line_len);
	}
}

//slow but fine for now
void	lex_read_append(t_lexer *lex, char **dest_str) {
	assert(ft_strjoin_inplace_char(dest_str, lex->cur) && "malloc fail");
	lex_read(lex);
}

bool	lex_comment(t_lexer *lex, t_token *token) {
	if (lex->cur == '@') {
		bool	except = false;

		while (lex->cur != '\n' || except) {
			if (!except && lex->cur == '\\') {
				except = true;
				lex_read(lex);
				continue ;
			}
			lex_read_append(lex, &token->str);
		}
		token->type = TOKEN_COMMENT;
		return (true);
	}
	return (false);
}

bool	lex_sep(t_lexer *lex, t_token *token) {
	char	signs_uncond[] = {'\n',};
	char	signs_cond[] = {';', '#'};

	for (size_t i = 0; i < sizeof signs_uncond / sizeof signs_uncond[0]; i++) {
		if (lex->cur == signs_uncond[i]) {
			token->type = TOKEN_SEP;
			lex_read(lex);
			return (true);
		}
	}
	for (size_t i = 0; i < sizeof signs_cond / sizeof signs_cond[0]; i++) {
		if (lex->cur == signs_cond[i] && lex->last_token.type != TOKEN_SEP) {
			token->type = TOKEN_SEP;
			lex_read(lex);
			return (true);
		}
	}
	return (false);
}

bool	lex_comma(t_lexer *lex, t_token *token) {
	char	signs[] = {',',};

	for (size_t i = 0; i < sizeof signs / sizeof signs[0]; i++) {
		if (lex->cur == signs[i]) {
			token->type = TOKEN_COMMA;
			lex_read(lex);
			return (true);
		}
	}
	return (false);
}

bool	lex_math_op(t_lexer *lex, t_token *token) {
	char	signs[] = {'-', '+', '*'};//'/'

	for (size_t i = 0; i < sizeof signs / sizeof signs[0]; i++) {
		if (lex->cur == signs[i]) {
			token->type = TOKEN_MATH_OP;
			lex_read_append(lex, &token->str);
			return (true);
		}
	}
	return (false);
}
bool	lex_brace(t_lexer *lex, t_token *token) {
	switch (lex->cur) {
		case ('('):
			token->type = TOKEN_BRACE_OPEN;
			break ;
		case (')'):
			token->type = TOKEN_BRACE_CLOSE;
			break ;
		default:
			return (false);
	}
	lex_read(lex);
	return (true);
}

bool	lex_dollar(t_lexer *lex, t_token *token) {
	char	signs[] = {'$',};

	for (size_t i = 0; i < sizeof signs / sizeof signs[0]; i++) {
		if (lex->cur == signs[i]) {
			token->type = TOKEN_DOLLAR;
			lex_read(lex);
			return (true);
		}
	}
	return (false);
}

bool	lex_directive(t_lexer *lex, t_token *token) {
	if (lex->cur != '.') {
		return (false);
	}
	token->type = TOKEN_DIRECTIVE;
	lex_read_append(lex, &token->str);
	while (isalnum(lex->cur) || lex->cur == '_' || lex->cur == '-') {
		lex_read_append(lex, &token->str);
	}
	return (true);
}

bool	lex_column(t_lexer *lex, t_token *token) {
	char	signs[] = {':',};

	for (size_t i = 0; i < sizeof signs / sizeof signs[0]; i++) {
		if (lex->cur == signs[i]) {
			token->type = TOKEN_COLUMN;
			lex_read(lex);
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

bool	lex_reg(t_lexer *lex, t_token *token) {
	if (lex->cur != '%') {
		return (false);
	}
	token->type = TOKEN_REG;
	lex_read_append(lex, &token->str);
	while (isalnum(lex->cur)) {
		lex_read_append(lex, &token->str);
	}
	return (true);
}

bool	lex_str_char_literal(t_lexer *lex, t_token *token) {
	if (lex->cur != '\'' && lex->cur != '"') {
		return (false);
	}
	char	quote	= lex->cur;
	bool	except = false;
	token->type = TOKEN_STR_LITERAL;
	if (quote == '\'') {
		token->type = TOKEN_CHAR_LITERAL;
	}
	lex_read(lex);
	while ((lex->cur != quote || except) && (lex->cur != '\n' || except)) {
		if (!except && lex->cur == '\\') {
			except = true;
			lex_read(lex);
			continue ;
		}
		lex_read_append(lex, &token->str);
		except = false;
	}
	assert(lex->cur == quote && "unexpected literal termination");
	lex_read(lex);
	return (true);
}

bool	lex_identifier(t_lexer *lex, t_token *token) {
	if (!isalpha(lex->cur) && lex->cur != '_') {
		return (false);
	}
	while (isalnum(lex->cur) || lex->cur == '_') {
		lex_read_append(lex, &token->str);
	}
	token->type = TOKEN_IDENTIFIER;
	return (true);
}

bool	lex_nb_literal(t_lexer *lex, t_token *token) {
	if (!isdigit(lex->cur)) {
		return (false);
	}
	char	bin[] = "01";
	char	octal[] = "01234567";
	char	decimal[] = "0123456789";
	char	hex[] = "0123456789abcdefABCDEF";
	char	*char_set = decimal;

	if (lex->cur == '0' && (lex->next == 'x' || lex->next == 'X')) {
		char_set = hex;
		lex_read_append(lex, &token->str);
		lex_read_append(lex, &token->str);
	} else if (lex->cur == '0' && (lex->next == 'b' || lex->next == 'B')) {
		char_set = bin;
		lex_read_append(lex, &token->str);
		lex_read_append(lex, &token->str);
	} else if (lex->cur == '0' && isdigit(lex->next)) {
		char_set = octal;
		lex_read_append(lex, &token->str);
	}
	if (!ft_is_charset(lex->cur, char_set))
		lex_print(lex);
	assert(ft_is_charset(lex->cur, char_set) && "first digit has to be valid");
	while (ft_is_charset(lex->cur, char_set)) {
		lex_read_append(lex, &token->str);
	}
	token->type = TOKEN_NB_LITERAL;
	return (true);
}

bool	lex_eof(t_lexer *lex, t_token *token) {
	if (lex->cur) {
		return (false);
	}

	token->type = TOKEN_EOF;
	return (true);
}

t_token	lex_next(t_lexer *lex) {
	t_token	token;
	// order matters
	bool	(*typing[])(t_lexer*, t_token*) = {
		lex_eof,
		lex_comment,//has to be very early; todo: other comment types
		lex_sep,
		lex_dollar,
		lex_brace,
		lex_comma,
		lex_column,
		lex_whitespace,
		lex_reg,
		lex_nb_literal,
		lex_str_char_literal, //todo
		lex_directive,
		lex_math_op,//has to be after directive
		lex_identifier,
	};

	bzero(&token, sizeof token);
	token.str = calloc(1, sizeof(char));
	assert(token.str && "malloc fail");
	token.debug_info = lex->debug_info;
	token.debug_info.line = strdup(lex->debug_info.line);
	for (size_t i = 0; i < sizeof typing / sizeof typing[0]; i++) {
		if (typing[i](lex, &token)) {
			return (token);
		}
	}
	lex_print(lex);

	assert(0 && "couldn't lex token");
	return (token);
}

t_lexer	new_lexer(char *input) {
	t_lexer	lex = {
		.input = input,
		//.last_token,
		.last = 0,
		.cur = input[0],
		.pos = 0,
	};
	lex.debug_info = lex_make_debug_info(&lex);
	lex.debug_info.line_idx = 1;
	char	*line_begin = lex.input + lex.pos;
	size_t	line_len = strchr(line_begin, '\n') - line_begin;
	lex.debug_info.line = strndup(lex.input + lex.pos, line_len);
	if (input[0]) {
		lex.next = input[1];
	}
	return (lex);
}

//unlinks the cloned token from the list
t_token	*clone_token(t_token *in) {
	assert(in && "tring to clone NULL");
	t_token	*clone = ft_memdup(in, sizeof(t_token));
	assert(clone && "malloc fail");
	assert(in->debug_info.line && "no debug line info in token?");
	clone->debug_info.line = strdup(clone->debug_info.line);
	if (in->str) {
		clone->str = strdup(clone->str);
	}
	assert((clone->str || !in->str) && clone->debug_info.line && "malloc fail");
	clone->next = 0;
	return (clone);
}

//frees the content and the struct itself
void	free_token(t_token *token) {
	free(token->debug_info.line);
	free(token->str);
	free(token);
}

void	free_token_list2(t_token **head) {
	t_token	*cur = *head;

	if (!cur) {
		return ;
	}
	t_token	*next;
	while (cur) {
		next = cur->next;
		free_token(cur);
		cur = next;
	}
}

void	free_token_list(t_token *head) {
	if (!head) {
		return ;
	}
	t_token	*next;
	while (head) {
		next = head->next;
		free_token(head);
		head = next;
	}
}

void	print_token(t_token *token) {
	if (!token) {
		printf("TOKEN: WAS NULL!\n");
		return ;
	}
	printf("%lu: ", token->debug_info.line_idx);
	//printf("TOKEN: line %lu col %lu: %s: ", token->debug_info.line_idx,
	//	token->debug_info.col_idx, token->debug_info.line);
	printf("%s", token_type_to_str(token->type));
	printf(": %s", token->str);
	printf("\n");
}

void	print_token_list(t_token *head) {
	size_t	idx = 0;
	while (head) {
		printf("%lu: ", idx++);
		print_token(head);
		head = head->next;
	}
}

t_token *lexer(char *data) {
	t_lexer	lex = new_lexer(data);
	t_token	head;
	t_token	*cur = &head;

	do {
		cur->next = malloc(sizeof head);
		assert(cur->next && "malloc fail");
		*cur->next = lex_next(&lex);
		cur = cur->next;
		//printf("new token: ");
		//print_token(cur);
		lex.last_token = *cur;
	} while (cur->type != TOKEN_EOF);
	free(lex.debug_info.line);
	return (head.next);
}
