/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:39:35 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 20:49:57 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_istokenchar(char c)
{
	if (c == '|' || c == '>' || c == '<'
		|| c == '"'
		|| c == '\'')
		return (1);
	return (0);
}

int	ft_istokenquotes(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	space_until_next(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || ft_istokenchar(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	blank_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
