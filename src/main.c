#include "../minishell.h"
#include <stdio.h>

void    read_input(char **env);

int status;

void ft_zozzle()
{
    printf("\n"PROMPT" ");
}

void    ft_signals()
{

    signal(SIGINT, ft_zozzle);
    signal(SIGKILL, ft_zozzle);
}

int main(int argc, char **argv, char **env)
{
    status = 0;
	(void)argc;
	(void)argv;
    ft_signals();
    read_input(env);
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

void    read_input(char **env)
{
    char *str;
    t_list *tlist;
    t_list *plist;

    tlist = NULL;
	plist = NULL;
    while (status != -1)
    {
        str = readline(PROMPT" ");
        if (blank_check(str))
            continue;
        add_history(str);
        tlist = tokenize(str, &tlist); //add guard
        expand(&tlist, env);
        plist = parser(&tlist, &plist);
        ft_lstclear(&tlist, free_token);
		if (plist == NULL)
			printf("syntax error\n");
		execute(&plist, env);
        ft_lstclear(&plist, free_command);
        tlist = NULL;
		plist = NULL;
        printf("status :%i\n", status);
    }
}
