#include "../minishell.h"
#include "builtin/builtin.h"
#include <stdio.h>

char	is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	if (!ft_strncmp(cmd, "cd", len))
		return (0);
	if (!ft_strncmp(cmd, "env", len))
		return (1);
	if (!ft_strncmp(cmd, "exit", len))
		return (1);
	if (!ft_strncmp(cmd, "pwd", len))
		return (0);
	if (!ft_strncmp(cmd, "export", len))
		return (0);
	if (!ft_strncmp(cmd, "unset", len))
		return (1);
	//add others
	return (0);
}

int exec_builtin(char *cmd, char **argv, char **en, int *ret)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return echo(argv);
	if (!ft_strncmp(cmd, "cd", len))
		return cd(argv);
	if (!ft_strncmp(cmd, "env", len))
		return env(en);
	if (!ft_strncmp(cmd, "exit", len))
		return ft_exit();
	if (!ft_strncmp(cmd, "pwd", len))
		return pwd();
	if (!ft_strncmp(cmd, "export", len))
		return (export(argv, &en));
	if (!ft_strncmp(cmd, "unset", len))
		return (unset(argv, &en));
	(void)ret;
	return (0);

}



char **listomap(char *cmd, t_list **list)
{
	int i;
	int size;
	char **mat;

	size = ft_lstsize(*list);
	mat = (char **)ft_calloc(sizeof(char *) , (size + 2));
	mat[0] = ft_strdup(cmd);
	i = 1;
	while ((*list))
	{
		mat[i] = ft_strdup((*list)->content);
		i++;
		*list = (*list)->next;
	}
	mat[i] = NULL;
	return (mat);
}
