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

static void    read_input(char **env)
{
    char *str;
    t_list *tlist;
    t_list *plist;

    while (status != -1) 
	{
		tlist = NULL;
		plist = NULL;
		str = readline(PROMPT" ");
        if (!str)
			break;
        if (blank_check(str))
		{
            free(str);
            continue;
        }
        add_history(str);
        tlist = tokenize(str, &tlist);
        free(str);
        /*tlist = expand(&tlist);*/
        plist = parser(&tlist, &plist);
        ft_lstclear(&tlist, free_token);
        execute(&plist, &env);
        ft_lstclear(&plist, free_command);
    }
}

t_list	*tokenize(char *str, t_list **list)
{
	while (ft_isspace(*str))
		str = str + 1;
	if (!*str)
	{
		if (!append_token(&str, list))
			return (NULL);
		return (*list);
	}
	if (!append_token(&str, list))
		return (NULL);
	return (tokenize(str, list));
}

t_list *expand(t_list **list) {
    t_list *current = *list;
    while (current) {
        t_token *token = (t_token *)current->content;
        if (token->type == TOKEN_WORD) {
            char *new_value = expand_token_value(token->value);
            free(token->value);
            token->value = new_value;
        }
        current = current->next;
    }
    return *list;
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

