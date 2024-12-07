#include "../minishell.h"
#include <stdio.h>

char	is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	if (!ft_strncmp(cmd, "cd", len))
		return (1);
	if (!ft_strncmp(cmd, "env", len))
		return (1);
	if (!ft_strncmp(cmd, "exit", len))
		return (1);
	if (!ft_strncmp(cmd, "e", len))
		return (1);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	//add others
	return (0);
}

char **listomap(char *cmd, t_list **list)
{
	int i;
	int size;
	char **mat;


	size = ft_lstsize(*list);
	mat = (char **)ft_calloc(sizeof(char *) , (size + 2));
	mat[0] = cmd;
	i = 1;
	while ((*list))
	{
		mat[i] = ft_strdup((*list)->content);
		i++;
		*list = (*list)->next;
	}
	mat[i] = NULL;
	if (*list)
		ft_lstclear(list, free);
	return (mat);
}
