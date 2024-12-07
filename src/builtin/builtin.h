
#ifndef BUILTIN_H
#define BUILTIN_H


int cd(char **argv, char **env);
int echo(char **argv, char **env);
int	ft_exit(char **argv, char **env);
char	*get_env(char **env, char *name);

#endif
