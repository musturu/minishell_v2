
#include "../minishell.h"

static void	handlec(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handleq(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	handlec_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	ft_signals(void)
{
	signal(SIGINT, handlec);
	signal(SIGQUIT, handleq);
}
