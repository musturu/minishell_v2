/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:51:54 by mamerlin          #+#    #+#             */
/*   Updated: 2024/12/18 13:51:54 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>

static char	*handle_quoted_expansion(char *quoted_str, char **env)
{
	char	*result;
	char	*next_part;
	char	*start;

	result = allocate_empty_string();
	if (!result)
		return (NULL);
	next_part = quoted_str;
	while ((start = strchr(next_part, '$')))
	{
		if (*(start + 1) == '"' || isspace((unsigned char)*(start + 1)))
		{
			start++;
			continue ;
		}
		result = process_expansion(result, &next_part, start, env);
		if (!result)
			return (NULL);
	}
	result = append_to_result(result, next_part, strlen(next_part));
	return (result);
}

static void	handle_token_expansion(t_token *tkn, char **env)
{
	int	env_index;

	if (tkn->type == TOKEN_DBQUOTE)
		tkn->value = handle_quoted_expansion(tkn->value, env);
	else if (strchr(tkn->value, '$'))
		tkn->value = expand_multiple_env(tkn->value, env);
	else if (ft_strlen(tkn->value) == 1)
		tkn->value = ft_strdup("$");
	else
	{
		env_index = str_to_env_index(env, tkn->value + 1);
		tkn->value = env_index == -1
			? ft_strdup("")
			: ft_strdup(env[env_index] + ft_strlen(tkn->value) + 1);
	}
}

t_list	*quote_expand(t_list **list, char **env)
{
	t_list	*tmp;
	t_token	*tkn;

	tmp = *list;
	while (tmp)
	{
		tkn = tmp->content;
		if (tkn->type == TOKEN_DBQUOTE || strchr(tkn->value, '$'))
		{
			handle_token_expansion(tkn, env);
			tkn->type = TOKEN_WORD;
		}
		tmp = tmp->next;
	}
	return (*list);
}
