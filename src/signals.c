/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:20:22 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:20:24 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handlec(int s)
{
	(void)s;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handleq(int s)
{
	(void)s;
	rl_redisplay();
}

void	handlec_heredoc(int s)
{
	(void)s;
	write(1, "\n", 1);
	exit(1);
}

void	ft_signals(void)
{
	signal(SIGINT, handlec);
	signal(SIGQUIT, handleq);
}
