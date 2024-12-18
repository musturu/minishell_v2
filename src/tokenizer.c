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
	if (!ft_strncmp(str, "$", 1))
		return (TOKEN_DOLLAR);
	if (!ft_strncmp(str, "\"", 1))
		return (TOKEN_DBQUOTE);
	if (!ft_strncmp(str, "\'", 1))
		return (TOKEN_SQUOTE);
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

static char	*get_token_value(char *str, e_TokenType type, char **env)
{
	if (type == TOKEN_EOF)
		return (ft_strdup("EOF"));
	if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_AND || type == TOKEN_CLOSE_P || type == TOKEN_OPEN_P
		|| type == TOKEN_SPACE)
		return (ft_substr(str, 0, 1));
	else if (type == TOKEN_DOLLAR)
		return (ft_substr(str, 0, space_until_next(str)));
	else if (type != TOKEN_WORD && type != TOKEN_DBQUOTE && type != TOKEN_SQUOTE)
		return (ft_substr(str, 0, 2));
	else if (type == TOKEN_WORD)
		return (word_manager(str, env));
	else if (type == TOKEN_SQUOTE)
		return (squote_manager(str));
	else if (type == TOKEN_DBQUOTE)
		return (dquote_manager(str, env));
	else
		return (NULL);
}

static int	append_token(char **str, t_list **lst, char **env)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (0);
	tok->type = get_token_type(*str);
	printf("str: \"%s\"\n", *str);
	tok->value = get_token_value(*str, tok->type, env);
	if (!tok->value)
		return (0);
	*str += ft_strlen(tok->value);
	if (tok->type == TOKEN_SQUOTE || tok->type == TOKEN_DBQUOTE)
		*str += 2;
	ft_lstadd_back(lst, ft_lstnew(tok));
	return (1);
}

int word_space(char *str)
{
	int	i;


	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || ft_istokenchar(str[i]))
			break ;
		i++;
	}
	while (str[i] && str[i] != '"')
		i++;

	return (i);
}

t_list	*tokenize(char *str, t_list **list, char **env)
{
	go_next(&str);
	if (!*str)
	{
		if (!append_token(&str, list, env))
			return (NULL);
		return (*list);
	}
	if (!append_token(&str, list, env))
		return (NULL);
	return (tokenize(str, list, env));
}
