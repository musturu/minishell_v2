#include <stdio.h>
#include <unistd.h>
#include "builtin.h"

int cd(char **argv, char **env)
{
	int i;
	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		printf(get_env(env, "HOME"));
		return (chdir(get_env(env, "HOME")));
	}
	if (i != 2)
	{
		printf("Error: Wrong Argument count :)\n");
		return -1;
	}
	return (chdir(argv[1]));
}

