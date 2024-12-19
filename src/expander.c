/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:00:00 by username          #+#    #+#             */
/*   Updated: 2024/12/18 16:00:52 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char	*allocate_empty_string(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	*str = '\0';
	return (str);
}

static char	*get_env_value(char *start, char **env)
{
	int	env_index;

	env_index = str_to_env_index(env, start + 1);
	if (env_index != -1)
		return (ft_strdup(env[env_index] + ft_strlen(start)));
	return (ft_strdup(""));
}

char	*append_to_result(char *result, const char *text, size_t length)
{
	char	*new_result;
	size_t	current_len;

	current_len = strlen(result);
	new_result = realloc(result, current_len + length + 1);
	if (!new_result)
		return (NULL);
	strncat(new_result, text, length);
	return (new_result);
}

char	*process_expansion(char *result, char **next_part, char *start, char **env)
{
	char	*env_value;
	char	*end;
	char	saved;

	end = start + 1;
	while (*end && *end != '$' && !isspace((unsigned char)*end))
		end++;
	saved = *end;
	*end = '\0';
	env_value = get_env_value(start, env);
	*end = saved;
	result = append_to_result(result, *next_part, (size_t)(start - *next_part));
	if (!result)
		return (NULL);
	result = append_to_result(result, env_value, strlen(env_value));
	free(env_value);
	*next_part = end;
	return (result);
}

char	*expand_multiple_env(char *input, char **env)
{
	char	*result;
	char	*next_part;
	char	*start;

	result = allocate_empty_string();
	if (!result)
		return (NULL);
	next_part = input;
	while ((start = strchr(next_part, '$')))
	{
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

	if (strchr(tkn->value, '$'))
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

t_list	*expand(t_list **list, char **env)
{
	t_list	*tmp;
	t_token	*tkn;

	tmp = *list;
	while (tmp)
	{
		tkn = tmp->content;
		/*if (tkn->type == TOKEN_DOLLAR)*/
		/*{*/
			handle_token_expansion(tkn, env);
			/*tkn->type = TOKEN_WORD;*/
		/*}*/
		tmp = tmp->next;
	}
	return (*list);
}
