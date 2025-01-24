/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:27:37 by lmoricon          #+#    #+#             */
/*   Updated: 2025/01/24 21:28:40 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static t_list	*parser(t_list **tokens, t_list **parsed_list);
static void		read_input(char **env);

int	g_status;

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_status = 0;
	env = ft_matdup(env);
	ft_signals();
	read_input(env);
	free_matrix(env);
	return (0);
}

static void	read_input(char **env)
{
	char	*str;
	t_list	*tlist;
	t_list	*plist;

	while (g_status != -1)
	{
		tlist = NULL;
		plist = NULL;
		str = readline(PROMPT" ");
		if (!str)
			break ;
		if (blank_check(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		tlist = tokenize(str, &tlist);
		free(str);
		tlist = expand(&tlist, env);
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

t_list	*expand(t_list **list, char **env)
{
	t_list	*current;
	t_token	*token;
	char	*new_value;

	current = *list;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == TOKEN_WORD)
		{
			new_value = expand_token(token->value, env);
			free(token->value);
			token->value = new_value;
		}
		current = current->next;
	}
	return (*list);
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
