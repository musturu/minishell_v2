/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:17:06 by mamerlin          #+#    #+#             */
/*   Updated: 2025/01/24 20:56:49 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char	*get_env(char **env, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0
			&& env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	ft_lst_remove_node(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (current == node)
		{
			if (!prev)
				*lst = current->next;
			if (prev)
				prev->next = current->next;
			if (current->next)
				current->next->prev = prev;
			ft_lstdelone(current, del);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_contains_dollar(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

char	**ft_matdup(char **mat)
{
	int		i;
	char	**ret;

	i = 0;
	while (mat[i])
		i++;
	ret = ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (--i >= 0)
		ret[i] = ft_strdup(mat[i]);
	return (ret);
}
