/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:37:47 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 20:46:58 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	already_present(char *str, char **env)
{
	int		i;
	int		len;
	char	*eq;

	i = -1;
	eq = ft_strchr(str, '=');
	len = eq ? (eq - str) : ft_strlen(str);
	while (env[++i])
	{
		if (!ft_strncmp(str, env[i], len)
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
	}
	return (-1);
}

void	matrixdup(char ***dst, char ***src)
{
	int	i;
	int	len;

	len = 0;
	if (!src || !*src)
	{
		*dst = NULL;
		return ;
	}
	while ((*src)[len])
		len++;
	*dst = (char **)malloc((len + 1) * sizeof(char *));
	if (!*dst)
		return ;
	for (i = 0; i < len; i++)
		(*dst)[i] = ft_strdup((*src)[i]);
	(*dst)[len] = NULL;
	for (i = 0; i < len; i++)
		free((*src)[i]);
	free(*src);
	*src = *dst;
}

void	update_exp(char *str, char ***env)
{
	int	i;

	i = already_present(str, *env);
	if (i == -1)
		return ;
	free((*env)[i]);
	(*env)[i] = ft_strdup(str);
}

void	insert_exp(char *str, char ***env)
{
	char	**new_env;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return ;
	for (int j = 0; j < i; j++)
		new_env[j] = ft_strdup((*env)[j]);
	if (ft_strchr(str, '=') != NULL)
	{
		new_env[i] = ft_strdup(str);
		new_env[i + 1] = NULL;
	}
	else
	{
		new_env[i] = ft_strjoin(str, "=''");
		new_env[i + 1] = NULL;
	}
	for (int j = 0; j < i; j++)
		free((*env)[j]);
	free(*env);
	*env = new_env;
}

int	export(char **argv, char ***en)
{
	int	i;

	i = 0;
	if (!argv[1])
		return (env(*en));
	while (argv[++i])
	{
		if (already_present(argv[i], *en) != -1)
			update_exp(argv[i], en);
		else
			insert_exp(argv[i], en);
	}
	return (0);
}
