
#include "../minishell.h"
#include <stdio.h>


char	is_break(t_list *tokens)
{
	t_token	*tkn;

	tkn = tokens->content;
	return (tkn->type == TOKEN_EOF || tkn->type == TOKEN_PIPE || tkn->type == TOKEN_AND);
}

char	is_after_break(t_list *tokens)
{
	t_token	*tkn;

	if (tokens->prev == NULL)
		return (1);
	tkn = tokens->prev->content;
	if (tkn == TOKEN_WORD && tokens->prev->prev && ((t_token *)(tokens->prev->prev->content))->type == TOKEN_REDIR_OUT)
		return (1);
	return (tkn->type == TOKEN_AND || tkn->type == TOKEN_PIPE);
}

char	is_string(e_TokenType type)
{
	return (type == TOKEN_WORD
		|| type == TOKEN_SQUOTE
		|| type == TOKEN_DBQUOTE);
}


char	is_redirection(e_TokenType type)
{
	return (type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_PRE
		|| type == TOKEN_REDIR_APPEND);
}
