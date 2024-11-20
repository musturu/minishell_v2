#include "../minishell.h"
#include <curses.h>
#include <stdio.h>

void    read_input(char **env);

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
	(void)argc;
	(void)argv;
	printf("%s\n", env[1]);
    ft_signals();
    read_input(env);
}

void    print_parse(t_list *list)
{
    t_list  *tmp = list;
    command     *cmd;
	t_list	*tmparg;

	printf("______________PARSER_______________\n\n");
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
	printf("______________________________________\n\n");
}

void    print_tokens(t_list *list)
{
    t_list  *tmp = list;
    token   *tkn;

	printf("________________TOKENS_________________\n\n");
    while (tmp)
    {
        tkn = tmp->content;
        printf("TYPE:\t%i\tVALUE:\t[%s]\tprev: [%p] - cur : [%p]\n", tkn->type, tkn->value, tmp->prev, tmp);
        tmp = tmp->next;
    }
	printf("______________________________________\n\n");
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
    while (1)
    {
        str = readline(PROMPT" ");
        add_history(str);
        if (blank_check(str))
            continue;
        tlist = tokenize(str, &tlist, env); //add guard
		printf("exited tokenizer\n");
        print_tokens(tlist);
        plist = parser(&tlist, &plist);
		printf("exited parser\n");
		if (plist == NULL)
			printf("syntax error\n");
        print_parse(plist);
		execute(&plist, env);
		printf("exited executor\n");
        ft_lstclear(&tlist, free_token);
        ft_lstclear(&plist, free_command);
        tlist = NULL;
		plist = NULL;
    }
}
