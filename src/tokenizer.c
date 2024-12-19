/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:39:39 by lmoricon          #+#    #+#             */
/*   Updated: 2024/12/18 14:10:19 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static e_TokenType	get_token_type(char *str)
{
	if (!*str)
		return (TOKEN_EOF);
	if (!ft_strncmp(str, "|", 1))
		return (TOKEN_PIPE);
	if (!ft_strncmp(str, ">>", 2))
		return (TOKEN_REDIR_APPEND);
	if (!ft_strncmp(str, "<<", 2))
		return (TOKEN_REDIR_PRE);
	if (!ft_strncmp(str, ">", 1))
		return (TOKEN_REDIR_OUT);
	if (!ft_strncmp(str, "<", 1))
		return (TOKEN_REDIR_IN);
	else
		return (TOKEN_WORD);
}

static char	*get_token_value(char *str, e_TokenType type)
{
	char	*ret;
	
	ret = NULL;
	if (type == TOKEN_EOF)
		return (ft_strdup("EOF"));
	if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT)
		return (ft_substr(str, 0, 1));
	else if (type != TOKEN_WORD)
		return (ft_substr(str, 0, 2));
	else if (type == TOKEN_WORD)
		return (getwordvalue(&str, &ret));
	else
		return (NULL);
}

static int	append_token(char **str, t_list **lst)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (0);
	tok->type = get_token_type(*str);
	tok->value = get_token_value(*str, tok->type);
	if (!tok->value)
		return (0);
	*str += ft_strlen(tok->value);
	ft_lstadd_back(lst, ft_lstnew(tok));
	return (1);
}

t_list	*tokenize(char *str, t_list **list)
{
	go_next(&str);
	if (!*str)
	{
		if (!append_token(&str, list))
			return (NULL);
		return (*list);
	}
	if (!append_token(&str, list))
		return (NULL);
	return (tokenize(str, list));
}
