/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:07:59 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:07:59 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtin/builtin.h"
#include <stdio.h>
#include <string.h>

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = ft_calloc(sizeof(char), len + 2);
	if (!result)
		return (NULL);
	memcpy(result, s1, len);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*expand_var(char *var, char **env)
{
	int		start;
	char	*ret;
	char	c;

	start = 0;
	if (var[start] == '?')
	{
		ret = ft_itoa(g_status % 255);
		return (ret);
	}
	while (ft_isalnum(var[start]) || var[start] == '_')
		start++;
	c = var[start];
	var[start] = '\0';
	if (get_env(env, var))
		ret = ft_strdup(get_env(env, var));
	else
		ret = ft_strdup("");
	var[start] = c;
	return (ret);
}

int	var_len(char *var)
{
	int	start;

	start = 0;
	if (*var == '?')
		return (1);
	while (ft_isalnum(var[start]) || var[start] == '_')
		start++;
	return (start);
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	in_single_quote;
	char	in_double_quote;

	result = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}
