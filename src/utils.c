
#include "../minishell.h"
#include <stdio.h>


int str_to_env_index(char **env, char *name)
{
    int i = 0;
    int len = ft_strlen(name);

    while (env[i])
    {
        // Check if the current environment string starts with 'name' followed by '='
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
        {
            return i; // Return the index of the found environment variable
        }
        i++;
    }
    return -1; // Return -1 if the environment variable is not found
}

char	*get_env(char **env, char *name)
{
    int i = 0;
    int len = ft_strlen(name);

    while (env[i])
    {
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
        {
            return env[i] + len + 1;
        }
        i++;
    }
    return NULL;

}


void	ft_lst_remove_node(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (current == node)
		{
			if (!prev)
				*lst = current->next;
			if (prev)
				prev->next = current->next;
			if (current->next)
				current->next->prev = prev;
			ft_lstdelone(current, del);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_contains_dollar(const char *str)
{
    if (!str)
        return (0);
    while (*str)
    {
        if (*str == '$')
            return (1);
        str++;
    }
    return (0);
}
