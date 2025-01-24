/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:35:54 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 20:36:32 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>
#include <stdio.h>

static void	sort_env(char ***en, int index)
{
	while ((*en)[index + 1])
	{
		(*en)[index] = (*en)[index + 1];
		index++;
	}
	(*en)[index] = NULL;
}

int	unset(char **argv, char ***env)
{
	int	i;
	int	present;

	i = 1;
	while (argv[i])
	{
		present = already_present(argv[i], *env);
		if (present >= 0)
		{
			free((*env)[present]);
			(*env)[present] = NULL;
			sort_env(env, present);
		}
		i++;
	}
	return (0);
}
