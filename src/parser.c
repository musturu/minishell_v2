/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:52:52 by mamerlin          #+#    #+#             */
/*   Updated: 2024/08/20 19:07:07 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>


/*
 * the parser functions in the same exact way the tokenizer does, by calling itself it attaches
 * at the end of the list a new node, consuming the utilized token nodes in the process.
 *
 */



static char	*get_command_command(t_list **tokens)
{
	token	*tkn;
	char	*ret;

	tkn = (*tokens)->content;
	if (is_after_break(*tokens) && (is_string(tkn->type)))  
	{
		ret = ft_strdup(tkn->value);
		ft_lst_remove_node(tokens, *tokens, free_token);
		return (ret);
	}
	else
		return (ft_strdup("ERROR"));
}


static t_list	*get_command_args(t_list **tokens)
{
	t_list	*ret;
	token	*tknnext;

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
		if ((((token *)(lst->content))->type == TOKEN_REDIR_IN || ((token *)(lst->content))->type == TOKEN_REDIR_PRE) && lst->next)
		{
			lst = lst->next;
			if (is_string(((token *)(lst->content))->type))
			{
				ret = ft_strjoin(((token *)(lst->prev->content))->value, ((token *)(lst->content))->value);
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
		if ((((token *)(lst->content))->type == TOKEN_REDIR_OUT || ((token *)(lst->content))->type == TOKEN_REDIR_APPEND) && (*tokens)->next)
		{
			lst = lst->next;
			if (is_string(((token *)(lst->content))->type))
			{
				ret = ft_strjoin(((token *)(lst->prev->content))->value, ((token *)(lst->content))->value);
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
//dovremmo mettere anche || e && ? bho
static TokenType get_command_inconnect(t_list **tokens, int isfirst)
{
	token	*tkn;

	tkn = (*tokens)->content;
	if (!(*tokens)->prev && isfirst)
		return (0);
	if (tkn->type == TOKEN_AND)
	{
		ft_lst_remove_node(tokens, *tokens, free_token);
		return (TOKEN_AND);
	}
	if (tkn->type == TOKEN_PIPE)
	{
		ft_lst_remove_node(tokens, *tokens, free_token);
		print_tokens(*tokens);
		return (TOKEN_PIPE);
	}
	return 0;
}

//dovremmo mettere anche ||, && e ;? bho
static TokenType get_command_outconnect(t_list **tokens)
{
	token	*tkn;

	tkn = (*tokens)->content;
	if (tkn->type == TOKEN_AND)
	{
		return (TOKEN_AND);
	}
	if (tkn->type == TOKEN_PIPE)
	{
		return (TOKEN_PIPE);
	}
	if (tkn->type == TOKEN_EOF)
	{
		return (TOKEN_EOF);
	}
	return 0;
}

static int	append_cmd(t_list	**tokens, t_list **parsed_list)
{
	command	*cmd;

	cmd = ft_calloc(1, sizeof(command));
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
	if (cmd->cmd && *cmd->cmd == *"ERROR") //potrebbe rompersi se esistesse un comando chiamato ERROR ........
		return (0);
	cmd->args = get_command_args(tokens);
	cmd->outconnect = get_command_outconnect(tokens);
	cmd->outfd = STDOUT_FILENO;
	cmd->infd = STDIN_FILENO;
	ft_lstadd_back(parsed_list, ft_lstnew(cmd));
	return (1);
}

t_list	*parser(t_list **tokens,t_list **parsed_list)
{
	if (!*tokens || ((token *)(*tokens)->content)->type == TOKEN_EOF)
		return (*parsed_list);
	if (!append_cmd(tokens, parsed_list))
	{
		ft_lstclear(parsed_list, free_command);
		ft_lstclear(tokens, free_token);
		return (NULL);
	}
	return (parser(tokens, parsed_list));
}

