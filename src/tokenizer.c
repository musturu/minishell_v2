/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:39:39 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:37:26 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*getwordvalue(char **str, char **ret);

static	t_TokenType	get_token_type(char *str)
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

static char	*get_token_value(char *str, t_TokenType type)
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

int	append_token(char **str, t_list **lst)
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

static char	*handle_load(char **str)
{
	if (**str != '"' && **str != '\'')
		return (ft_substr(*str, 0, space_until_next(*str)));
	if (ft_strchr(*str, **str))
		return (ft_substr(*str, 0, ft_strchr(*str + 1, **str) - *str));
	return (NULL);
}

static char	*getwordvalue(char **str, char **ret)
{
	char	*tmp;
	char	*load;

	if (*ret == NULL)
		*ret = ft_strdup("");
	tmp = *ret;
	if (*ret && !ft_istokenquotes(**str)
		&& (!**str || ft_istokenchar(**str) || ft_isspace(**str)))
	{
		tmp = ft_strdup(*ret);
		free(*ret);
		return (tmp);
	}
	load = handle_load(str);
	if (!load)
		return (NULL);
	*ret = ft_strjoin(*ret, load);
	*str += ft_strlen(load);
	free(tmp);
	free(load);
	return (getwordvalue(str, ret));
}
