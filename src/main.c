#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static t_list	*parser(t_list **tokens, t_list **parsed_list);
static void    read_input(char **env);

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


static int blank_check(char *str)
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

<<<<<<< Updated upstream
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
=======
static void    read_input(char **env)
{
>>>>>>> Stashed changes
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
        tlist = expand(&tlist);  // Chiamata all'expander
        plist = parser(&tlist, &plist);
<<<<<<< Updated upstream
        print_tokens(tlist);
        print_parse(plist);
        execute(&plist, &env);
=======
		print_parse(plist);
>>>>>>> Stashed changes
        ft_lstclear(&tlist, free_token);
        ft_lstclear(&plist, free_command);
    }
}


static t_list	*parser(t_list **tokens, t_list **parsed_list)
{
	if (!*tokens || ((t_token *)(*tokens)->content)->type == TOKEN_EOF)
		return (*parsed_list);
	if (!append_cmd(tokens, parsed_list))
	{
		ft_lstclear(parsed_list, free_command);
		ft_lstclear(tokens, free_token);
		return (NULL);
	}
	return (parser(tokens, parsed_list));
}



