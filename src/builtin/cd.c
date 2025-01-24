/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:30:26 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 20:31:47 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"
#include <dirent.h>

int	cd(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
		return (chdir(getenv("HOME")));
	if (i != 2)
		return (printf("Error: Wrong Argument count :)\n"));
	if (opendir(argv[1]) == NULL)
		return (printf("Error cd: no such file or directory :)\n"));
	return (chdir(argv[1]));
}
