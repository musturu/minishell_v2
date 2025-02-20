/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:19:47 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:19:48 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

static void	readdoc(t_command *command, char **env, int fd)
{
	char	*line;
	int		i;

	(void)env;
	i = 0;
	while (++i)
	{
		if (i % 2 == 1)
			line = readline("--------D ");
		else
			line = readline("(.)       ");
		if (!line)
			break ;
		if (!ft_strncmp(line, command->inpath
				+ 2, ft_strlen(command->inpath + 2)))
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (line != 0)
		free(line);
}

int	heredoc(t_command *command, char **env)
{
	int	pid;
	int	fds[2];
	int	i;

	if (pipe(fds))
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handlec_heredoc);
		close(fds[0]);
		readdoc(command, env, fds[1]);
		close(fds[1]);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	wait(&i);
	close(fds[1]);
	command->infd = dup(fds[0]);
	close(fds[0]);
	ft_signals();
	return (1);
}
