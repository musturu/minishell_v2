/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:34:14 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 20:34:31 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char **argv)
{
	int	i;

	i = 0;
	printf("exit\n");
	while (argv[i])
		i++;
	if (i == 1)
	{
		g_status = -1000;
		return (g_status);
	}
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		g_status = 1;
		return (1);
	}
	if (ft_isdigit(argv[1][0]) == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		g_status = 255;
		return (255);
	}
	g_status = ft_atoi(argv[1]);
	g_status = -g_status;
	return (g_status);
}
