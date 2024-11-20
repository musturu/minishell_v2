#include "../minishell.h"
#include <time.h>

void	free_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	if (mat)
		free(mat);
}

void	free_token(void	*tok)
{
	token	*tkn;

	tkn = tok;
	if (tkn != NULL)
	{
		if (tkn->value != NULL)
			free(tkn->value);
		tkn->value = NULL;
		free(tkn);
	}
}

void	free_command(void *comd)
{
	command	*cmd;

	cmd = comd;
	if (cmd != NULL)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		cmd->cmd = NULL;
		if (cmd->inpath)
			free(cmd->inpath);
		cmd->inpath = NULL;
		if (cmd->outpath)
			free(cmd->outpath);
		cmd->outpath = NULL;
		if (cmd->args)
			ft_lstclear(&cmd->args, free);
		cmd->args = NULL;
		if (cmd->argv)
			free_matrix(cmd->argv);
		cmd->argv = NULL;
	}
}
