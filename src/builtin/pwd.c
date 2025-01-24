/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:36:58 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 20:37:33 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	pwd(void)
{
	size_t	size;
	char	*pwd;

	size = PATH_MAX;
	pwd = malloc(size);
	if (pwd == NULL)
		return (1);
	getcwd(pwd, size);
	if (pwd == NULL)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
