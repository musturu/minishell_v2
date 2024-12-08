#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"

int cd(char **argv, char **env)
{
	int i;
	i = 0;
	(void)env;
	while (argv[i])
		i++;
	if (i == 1)
	{
		return (chdir(getenv("HOME")));
	}
	if (i != 2)
	{
		printf("Error: Wrong Argument count :)\n");
		return -1;
	}
	return (chdir(argv[1]));
}

