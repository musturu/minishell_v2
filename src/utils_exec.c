/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:53:58 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:06:13 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char	is_builtin(char *cmd)
{
	if (!cmd)
		return (-1);
	if (!ft_strncmp(cmd, "echo", 4))
		return (0);
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(cmd, "env", 3))
		return (0);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (0);
	if (!ft_strncmp(cmd, "export", 6))
		return (1);
	if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	return (-1);
}

int	exec_builtin(char *cmd, char **argv, char ***en, int *ret)
{
	int	r;

	if (!ft_strncmp(cmd, "echo", 4))
		r = echo(argv);
	if (!ft_strncmp(cmd, "cd", 2))
		r = cd(argv);
	if (!ft_strncmp(cmd, "env", 3))
		r = env(*en);
	if (!ft_strncmp(cmd, "exit", 4))
		r = ft_exit(argv);
	if (!ft_strncmp(cmd, "pwd", 3))
		r = pwd();
	if (!ft_strncmp(cmd, "export", 5))
		r = (export(argv, en));
	if (!ft_strncmp(cmd, "unset", 5))
		r = (unset(argv, en));
	*ret = r;
	return (r);
}

char	**listomap(char *cmd, t_list *list)
{
	int		i;
	int		size;
	char	**mat;

	size = ft_lstsize(list);
	mat = (char **)ft_calloc(sizeof(char *), (size + 2));
	mat[0] = ft_strdup(cmd);
	i = 1;
	while ((list))
	{
		mat[i] = ft_strdup((list)->content);
		i++;
		list = (list)->next;
	}
	mat[i] = NULL;
	return (mat);
}

int	pipes(t_list **lst)
{
	t_command	*cur;
	t_command	*next;
	int			piped[2];

	cur = (*lst)->content;
	next = (*lst)->next->content;
	if (pipe(piped) == -1)
		return (0);
	next->infd = piped[0];
	cur->outfd = piped[1];
	return (1);
}

int	access_or_create(char *path)
{
	if (access(path, W_OK) == 0)
		return (1);
	else if (access(path, F_OK) == -1)
		return (-1);
	return (0);
}
