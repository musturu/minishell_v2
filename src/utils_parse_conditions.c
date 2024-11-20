
#include "../minishell.h"
#include <stdio.h>


char	is_break(t_list *tokens)
{
	token	*tkn;

	tkn = tokens->content;
	return (tkn->type == TOKEN_EOF || tkn->type == TOKEN_PIPE || tkn->type == TOKEN_AND);
}

char	is_after_break(t_list *tokens)
{
	token	*tkn;

	if (tokens->prev == NULL)
		return (1);
	tkn = tokens->prev->content;
	if (tkn == TOKEN_WORD && tokens->prev->prev && ((token *)(tokens->prev->prev->content))->type == TOKEN_REDIR_OUT)
		return (1);
	return (tkn->type == TOKEN_AND || tkn->type == TOKEN_PIPE);
}

char	is_string(TokenType type)
{
	return (type == TOKEN_WORD 
		|| type == TOKEN_SQUOTE 
		|| type == TOKEN_DBQUOTE);
}


char	is_redirection(TokenType type)
{
	return (type == TOKEN_REDIR_OUT 
		|| type == TOKEN_REDIR_IN 
		|| type == TOKEN_REDIR_PRE 
		|| type == TOKEN_REDIR_APPEND);
}
