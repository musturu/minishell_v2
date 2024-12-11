
#ifndef BUILTIN_H
# define BUILTIN_H

#include <stdlib.h>

int cd(char **argv);
int echo(char **argv);
int	ft_exit();
int	pwd();
int	env(char **env);
int export(char **argv, char ***env);
int	already_present(char    *str, char    **env);
int	unset(char **argv, char ***env);

#endif
