#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	pwd()
{
	size_t	size;
	char	*pwd;

	size = PATH_MAX;
	pwd = malloc(size);
	if (pwd == NULL)
		return (1);
	getcwd(pwd, size);
	if (pwd == NULL)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	return(0);
}
