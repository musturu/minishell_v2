 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>

int echo(char **argv, char **env)
{
	char nflag;

	(void)env;
	argv += 1;
	nflag = (argv[0] && argv[0][0] && argv[0][0] == '-' && argv[0][1] == 'n');
	argv += nflag;
	while(*argv)
	{
		printf("%s", *argv++);
		if (*argv)
			printf(" ");
	}
	if (nflag)
		return (0);
	printf("\n");
	return (0);
}
