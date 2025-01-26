/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eggxecutor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:04:23 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:34:57 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

void	get_path(char **env, t_command **command);
void	execute_fork(t_command **cur, char ***env);

static int	redir_out(t_command *cmd)
{
	if (cmd->outpath)
	{
		if (cmd->outpath[1] == '>')
		{
			if (access_or_create(cmd->outpath + 2))
				cmd->outfd = open(cmd->outpath
						+ 2, O_APPEND | O_CREAT | O_WRONLY, 00600);
			else
				return (0);
		}
		else
		{
			if (access_or_create(cmd->outpath + 1))
			{
				cmd->outfd = open(cmd->outpath + 1,
						O_CREAT | O_WRONLY | O_TRUNC, 00600);
			}
			else
				return (0);
		}
	}
	return (1);
}

static int	redir_in(t_command *cmd)
{
	if (cmd->inpath)
	{
		if (cmd->inpath[1] == '<')
		{
			if (!heredoc(cmd, NULL))
				return (0);
		}
		else
		{
			if (access(cmd->inpath + 1, R_OK) == 0)
				cmd->infd = open(cmd->inpath + 1, O_RDONLY);
			else
				return (0);
		}
	}
	return (1);
}

void	get_path(char **env, t_command **c)
{
	char	**paths;
	char	*cmd;
	char	*ret;
	int		i;

	if (is_builtin((*c)->cmd) >= 0 ||!access((*c)->cmd, F_OK) || !(*c)->cmd)
		return ;
	i = -1;
	cmd = ft_strjoin("/", (*c)->cmd);
	paths = ft_split(get_env(env, "PATH"), ':');
	ret = ft_strjoin(paths[0], cmd);
	while (paths[++i] && access(ret, F_OK) != 0)
	{
		free(ret);
		ret = ft_strjoin(paths[i], cmd);
	}
	free(cmd);
	free_matrix(paths);
	if (access(ret, F_OK) == 0)
	{
		free((*c)->cmd);
		(*c)->cmd = ret;
		return ;
	}
	free (ret);
}

int	execute(t_list **parsed_list, char ***env)
{
	t_command	*cur;
	pid_t		pid;

	pid = 0;
	if (!(*parsed_list))
		return (1);
	cur = (*parsed_list)->content;
	if (cur->outconnect == TOKEN_PIPE && !pipes(parsed_list))
		return (0);
	if (is_builtin((cur->cmd)) != 1)
		pid = fork();
	if (!pid)
	{
		if (cur->outconnect == TOKEN_PIPE)
			close(((t_command *)((*parsed_list)->next->content))->infd);
		execute_fork(&cur, env);
	}
	if (cur->outfd != STDOUT_FILENO)
		close(cur->outfd);
	if (cur->infd != STDIN_FILENO)
		close(cur->infd);
	execute(&(*parsed_list)->next, env);
	waitpid(pid, &g_status, 0);
	return (1);
}

void	execute_fork(t_command **cur, char ***env)
{
	get_path(*env, cur);
	if (!redir_in(*cur) || !redir_out(*cur))
		exit(printf("couldnt open files\n"));
	if ((*cur)->infd != STDIN_FILENO)
		dup2((*cur)->infd, STDIN_FILENO);
	if ((*cur)->outfd != STDOUT_FILENO)
		dup2((*cur)->outfd, STDOUT_FILENO);
	if (!(*cur)->cmd)
		exit(0);
	(*cur)->argv = listomap((*cur)->cmd, (*cur)->args);
	if (is_builtin((*cur)->cmd) != -1)
		exec_builtin((*cur)->cmd, (*cur)->argv, env, &g_status);
	else if (execve((*cur)->cmd, (*cur)->argv, *env) == -1)
	{
		write(2, "command not found\n", 18);
		g_status = 127;
	}
	if (is_builtin((*cur)->cmd) != 1)
		exit(g_status);
}
