#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

void    read_input(char **env);

int status;

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
    status = 0;
    env = ft_matdup(env);
    ft_signals();
    read_input(env);
    free_matrix(env);
    return(0);
}

void    print_parse(t_list *list)
{
    t_list  *tmp = list;
    t_command     *cmd;
	t_list	*tmparg;

	printf("\n______________PARSER_______________\n");
    while (tmp)
    {
        printf("NEW COMMAND\t");
        cmd = tmp->content;
        printf("CMD: %s\n", cmd->cmd);
		tmparg = cmd->args;
        while (tmparg)
        {
            printf("\tARG: %s\n",  (char *)tmparg->content);
            tmparg = tmparg->next;
        }
		printf("\n\tINPATH:%s -----> OUTPATH:%s\n", cmd->inpath, cmd->outpath);
		if (cmd->inconnect)
			printf("CONNECTOR IN: %i (1 = PIPE, 7 = &)\n", cmd->inconnect);
		if (cmd->outconnect)
			printf("CONNECTOR OUT: %i\n", cmd->outconnect);
        tmp = tmp->next;
    }
	printf("\n______________________________________\n");
}

void    print_tokens(t_list *list)
{
    t_list  *tmp = list;
    t_token   *tkn;

	printf("\n________________TOKENS_________________\n");
    while (tmp)
    {
        tkn = tmp->content;
        printf("TYPE:\t%i\tVALUE:\t[%s]\tprev: [%p] - cur : [%p]\n", tkn->type, tkn->value, tmp->prev, tmp);
        tmp = tmp->next;
    }
	printf("\n______________________________________\n");
}

int blank_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void	close_fds(t_list *lst)
{
	t_list	*cmd;
	t_command	command;

	cmd = lst;
	while (cmd)
	{
		command = *(t_command *)cmd->content;
		if (command.infd != STDIN_FILENO)
			close(command.infd);
		if (command.outfd != STDOUT_FILENO)
			close(command.outfd);
		cmd = cmd->next;
	}
}

void read_input(char **env) {
    char *str;
    t_list *tlist = NULL;
    t_list *plist = NULL;

    while (status != -1) {
        str = readline(PROMPT" ");
        if (!str) break;  // Gestione dell'EOF
        if (blank_check(str)) {
            free(str);
            continue;
        }
        add_history(str);
        tlist = tokenize(str, &tlist);
        free(str);
        print_tokens(tlist);
        tlist = expand(&tlist, env);  // Chiamata all'expander
        plist = parser(&tlist, &plist);
        print_tokens(tlist);
        print_parse(plist);
        execute(&plist, &env);
        ft_lstclear(&tlist, free_token);
        ft_lstclear(&plist, free_command);
    }
}
