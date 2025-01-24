/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:52:52 by mamerlin          #+#    #+#             */
/*   Updated: 2024/12/15 17:24:31 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

static char	*get_command_command(t_list **tokens)
{
	t_token	*tkn;
	char	*ret;

	tkn = (*tokens)->content;
	if (is_after_break(*tokens) && (is_string(tkn->type)))
	{
		ret = ft_strdup(tkn->value);
		ft_lst_remove_node(tokens, *tokens, free_token);
		return (ret);
	}
	else
		return (NULL);
}

/*
*	cycles trough the list TOKEN_WORDS which are consecutive, destroying the
*	current element,
*	after having copied its content to the using lst_remove_node
*/
static t_list	*get_command_args(t_list **tokens)
{
	t_list	*ret;
	t_token	*tknnext;

	ret = NULL;
	tknnext = (*tokens)->content;
	while (is_string(tknnext->type))
	{
		ft_lstadd_back(&ret, ft_lstnew(ft_strdup(tknnext->value)));
		ft_lst_remove_node(tokens, *tokens, free_token);
		tknnext = (*tokens)->content;
	}
	return (ret);
}

static char	*get_command_in(t_list **tokens)
{
	t_list	*lst;
	char	*ret;

	lst = *tokens;
	while (lst && !is_break(lst))
	{
		if ((((t_token *)(lst->content))->type == TOKEN_REDIR_IN
			|| ((t_token *)(lst->content))->type == TOKEN_REDIR_PRE)
					&& lst->next)
		{
			lst = lst->next;
			if (is_string(((t_token *)(lst->content))->type))
			{
				ret = ft_strjoin(((t_token *)(lst->prev->content))->value,
						((t_token *)(lst->content))->value);
				ft_lst_remove_node(tokens, lst->prev, free_token);
				ft_lst_remove_node(tokens, lst, free_token);
				return (ret);
			}
			else
				return (ft_strdup("ERROR"));
		}
		lst = lst->next;
	}
	return (NULL);
}

static char	*get_command_out(t_list **tokens)
{
	t_list	*lst;
	char	*ret;

	lst = *tokens;
	while (lst && !is_break(lst))
	{
		if ((((t_token *)(lst->content))->type == TOKEN_REDIR_OUT
			|| ((t_token *)(lst->content))->type == TOKEN_REDIR_APPEND)
			&& (*tokens)->next)
		{
			lst = lst->next;
			if (is_string(((t_token *)(lst->content))->type))
			{
				ret = ft_strjoin(((t_token *)(lst->prev->content))->value,
						((t_token *)(lst->content))->value);
				ft_lst_remove_node(tokens, lst->prev, free_token);
				ft_lst_remove_node(tokens, lst, free_token);
				return (ret);
			}
			else
				return (ft_strdup("ERROR"));
		}
		lst = lst->next;
	}
	return (NULL);
}

/*
*	append_cmd works by creating a command element, it starts
*	by searching in all the list for
*	redirections, limiting the search by "breaks" (| and EOF)
*	then it moves on, by eliminating the
*	redirections, which can be anywhere on the command string,
*	we are left with a command as the first element of the token list
*	then every subsequent word is an argument to the command
*	and lastly we have an out_connector (| and EOF)
*/
int	append_cmd(t_list	**tokens, t_list **parsed_list)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (0);
	cmd->inconnect = get_command_inconnect(tokens, (*parsed_list) == NULL);
	cmd->inpath = get_command_in(tokens);
	if (cmd->inpath && *cmd->inpath == *"ERROR")
		return (0);
	cmd->outpath = get_command_out(tokens);
	if (cmd->outpath && *cmd->outpath == *"ERROR")
		return (0);
	cmd->cmd = get_command_command(tokens);
	if (cmd->cmd)
		cmd->args = get_command_args(tokens);
	cmd->outconnect = ((t_token *)(*tokens)->content)->type;
	cmd->outfd = STDOUT_FILENO;
	cmd->infd = STDIN_FILENO;
	ft_lstadd_back(parsed_list, ft_lstnew(cmd));
	return (1);
}
