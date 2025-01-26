/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:24:39 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:06:52 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h>

int	cd(char **argv);
int	echo(char **argv);
int	ft_exit(char **argv);
int	pwd(void);
int	env(char **env);
int	export(char **argv, char ***env);
int	already_present(char *str, char **env);
int	unset(char **argv, char ***env);

#endif
