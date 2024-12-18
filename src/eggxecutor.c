#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

void get_path(char **env, t_command **command);
void	execute_fork(t_command **cur, t_command **prev, char ***env);


static int	access_or_create(char *path)
{
	if (access(path , W_OK) == 0)
		return (1);
	else if (access(path , F_OK) == -1)
		return (-1);
	return (0);
}

static int	redir_out(t_command *cmd)
{
	if (cmd->outpath)
	{
		if (cmd->outpath[1] == '>')
		{
			if (access_or_create(cmd->outpath + 2))
				cmd->outfd = open(cmd->outpath + 2, O_APPEND | O_CREAT | O_WRONLY, 00600);
			else
				return (0);
		}
		else
			if (access_or_create(cmd->outpath + 1))
			{
				cmd->outfd = open(cmd->outpath + 1, O_CREAT | O_WRONLY | O_TRUNC, 00600);
			}
			else
				return (0);
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
			if (access(cmd->outpath + 1, R_OK) == 0)
				cmd->infd = open(cmd->inpath + 1, O_RDONLY);
			else
				return (0);
		}
	}
	return (1);
}

void get_path(char **env, t_command **command)
{
	char	**paths;
	char	*cmd;
	char	*ret;
	int		i;

	if (is_builtin((*command)->cmd) >= 0 || !access((*command)->cmd, F_OK) || !(*command)->cmd)
		return ;
	i = 0;
	cmd = ft_strjoin("/", (*command)->cmd);
	paths = ft_split(env[str_to_env_index(env, "PATH")], ':');
	ret	= ft_strjoin(paths[i], cmd);
	while (paths[i] && access(ret, F_OK) != 0)
	{
		free(ret);
		ret	= ft_strjoin(paths[i], cmd);
		i++;
	}
	free(cmd);
	free_matrix(paths);
	if (access(ret, F_OK) == 0)
	{
		free((*command)->cmd);
		(*command)->cmd = ret;
		return ;
	}
	free(ret);
}

int	execute(t_list **parsed_list, char ***env)
{
	t_command	*cur;
	t_command	*next;
	t_command	*prev;
	int		piped[2];
	pid_t	pid;

	pid = 0;
	if (!(*parsed_list))
		return (1);
	cur = (*parsed_list)->content;
	if ((*parsed_list)->next)
		next = (*parsed_list)->next->content;
	if ((*parsed_list)->prev)
		prev = (*parsed_list)->prev->content;
	if (cur->outconnect == TOKEN_PIPE)
	{
		if (pipe(piped) == -1)
			return (0);
		next->infd = piped[0];
		cur->outfd = piped[1];
	}
	if (NEEDFORK(cur->cmd))
		pid = fork();
	if (!pid)
	{
		if (cur->outconnect == TOKEN_PIPE)
			close(piped[0]);
		execute_fork(&cur, &prev, env);
	}
	if (cur->outconnect == TOKEN_PIPE)
		close(piped[1]);
	if (cur->outfd != STDOUT_FILENO)
		close(cur->outfd);
	if (cur->infd != STDIN_FILENO)
		close(cur->infd);
	execute(&(*parsed_list)->next, env);
	if (cur->outconnect != TOKEN_AND)
		waitpid(pid, &status, 0);
	return (1);
}

void	execute_fork(t_command **cur, t_command **prev, char ***env)
{
	(void)prev;
	get_path(*env, cur);
	redir_in(*cur); //add guard
	redir_out(*cur); //add guard
	if ((*cur)->infd != STDIN_FILENO)
		dup2((*cur)->infd, STDIN_FILENO); //add dup2 guard
	if ((*cur)->outfd != STDOUT_FILENO)
		dup2((*cur)->outfd, STDOUT_FILENO); //add dup2 guard
	if (!(*cur)->cmd)
		exit(0);
	(*cur)->argv = listomap((*cur)->cmd, (*cur)->args);
	if (is_builtin((*cur)->cmd) != -1)
			exec_builtin((*cur)->cmd, (*cur)->argv, env, &status);
	else if (execve((*cur)->cmd ,(*cur)->argv, *env) == -1)
			printf("command %s not found\n", (*cur)->cmd);
	if (NEEDFORK((*cur)->cmd))
		exit(status);
}
