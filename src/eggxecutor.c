#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


static int	access_or_create(char *path)
{
	if (access(path , W_OK) == 0)
		return (1);
	else if (access(path , F_OK) == -1)
		return (-1);
	return (0);
}


static int	redir_out(command *cmd)
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
				cmd->outfd = open(cmd->outpath + 1, O_CREAT | O_WRONLY, 00600);  //todo creare file
			}
			else
				return (0);
	}
	return (1);
}

static int	redir_in(command *cmd)
{
	if (cmd->inpath)
	{
		if (cmd->inpath[1] == '<') //da implementare <<
		{
		if (access(cmd->inpath + 2, R_OK) == 0)
				cmd->infd = open(cmd->outpath + 2, O_RDONLY);
		else
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




char	*get_path(char **env, char *command)
{
	char	**paths;
	char	*ret;
	int		i;

	i = 0;
	command = ft_strjoin("/", command);
	paths = ft_split(env[str_to_env_index(env, "PATH")], ':');
	ret	= ft_strjoin(*paths, command);
	while (paths[i] && access(ret, X_OK) != 0)
	{
		free(ret);
		ret	= ft_strjoin(paths[i], command);
		i++;
	}
	free(command);
	if (paths[i])
	{
		free_matrix(paths);
		return (ret);
	}
	free(ret);
	free_matrix(paths);
	return (NULL);
}

int	execute(t_list **parsed_list, char **env)
{
	command	*cur;
	command	*next;
	command	*prev;
	int		piped[2];
	pid_t	pid;

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
	pid = fork();

	printf("PID == %i\n", pid);
	if (!pid)
	{
		redir_in(cur); //add guard
		redir_out(cur); //add guard
		if (cur->infd != STDIN_FILENO)
		{
			printf("entrato in infd\n");
			dup2(cur->infd, STDIN_FILENO); //add dup2 guard
			close(prev->outfd);
		}
		if (cur->outfd != STDOUT_FILENO)
		{
			printf("entrato in outfd\n");
			dup2(cur->outfd,STDOUT_FILENO); //add dup2 guard
		}
		if (is_builtin(cur->cmd))
			printf("BUILTIN!\n");
		else
		{
			char	*prova = get_path(env, cur->cmd);
			printf("comando trovato:%s\n", prova);
			if (prova)
				cur->argv = listomap(prova, &cur->args);
			else
			 	cur->argv = listomap(cur->cmd, &cur->args);
			if (prova == NULL &&  execve(cur->cmd ,cur->argv, env) == -1)
					printf("command %s not found\n", cur->cmd);//spostare su un altra funzione a mettere get_path e argv su cmd cosi possono essere freeati
			else if (execve(prova ,cur->argv, env) == -1)
					printf("command %s not found\n", cur->cmd);//spostare su un altra funzione a mettere get_path e argv su cmd cosi possono essere freeati
		}
		return 0;

	}
	if (cur->inconnect == TOKEN_PIPE)
		close(prev->outfd);
	execute(&(*parsed_list)->next, env);
	if (cur->outconnect != TOKEN_AND)
		waitpid(pid, NULL, 0); //we can use the second parameter to store exit status of process. man waitpid
	return 1;
}

