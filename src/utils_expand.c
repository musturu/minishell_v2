/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:17:01 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:25:44 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_variable_expansion(char **str, char **env, char *ret)
{
	char	*tmp;
	char	*swp;

	(*str)++;
	tmp = expand_var(*str, env);
	*str += var_len(*str);
	swp = ret;
	ret = ft_strjoin(ret, tmp);
	free(tmp);
	free(swp);
	return (ret);
}

char	*append_char(char *ret, char c)
{
	char	*swp;

	swp = ret;
	ret = ft_strjoin_char(ret, c);
	free(swp);
	return (ret);
}

char	*expand_token(char *str, char **env)
{
	char	*ret;
	char	in_single_quote;
	char	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	ret = ft_strdup("");
	while (*str)
	{
		if (*str == '\'')
			in_single_quote = !in_single_quote;
		else if (*str == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*str == '$' && !in_single_quote)
		{
			ret = handle_variable_expansion(&str, env, ret);
			continue ;
		}
		else
			ret = append_char(ret, *str);
		str++;
	}
	ret = remove_quotes(ret);
	return (ret);
}
