#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"
#include <dirent.h>

int cd(char **argv)
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
	if (opendir(argv[1]) == NULL)
	{
		printf("Error cd: no such file or directory :)\n");
		return 12;	

	}
	return (chdir(argv[1]));
}
