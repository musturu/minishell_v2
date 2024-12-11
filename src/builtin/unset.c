#include "builtin.h"
#include <stdlib.h>

static void	sort_env(char ***env, int index)
{
	while ((*env)[index + 1])
	{
		(*env)[index] = (*env)[index + 1];
		index++;
	}
	(*env)[index] = NULL;
}


int	unset(char **argv, char ***env)
{
	int		i;
	int	present;

	i = 0;
	while (argv[i])
	{
		present = already_present(argv[i], *env);
		if (present > 0)
		{
			free((*env)[present]);
			(*env)[present] = NULL;
			sort_env(env, present);
		}
		i++;
	}
	return (0);
}
