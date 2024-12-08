

#include <stdio.h>


int env(char **env)
{
	int i;

	i = 0;
	while(env[i])
		printf("%s\n", env[i++]);
	return (1);
}


