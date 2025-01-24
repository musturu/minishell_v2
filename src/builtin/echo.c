/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:27:38 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 20:29:44 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	echo(char **argv, char **env)
{
	char	nflag;

	(void)env;
	argv += 1;
	nflag = (argv[0] && argv[0][0] && argv[0][0] == '-' && argv[0][1] == 'n');
	argv += nflag;
	while (*argv)
	{
		printf("%s", *argv++);
		if (*argv)
			printf(" ");
	}
	if (nflag)
		return (0);
	printf("\n");
	return (0);
}
