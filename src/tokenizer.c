/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:39:39 by lmoricon          #+#    #+#             */
/*   Updated: 2024/11/20 19:41:05 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

static TokenType   get_token_type(char *str)
{
    if (!*str)
        return (TOKEN_EOF);
    if (!ft_strncmp(str, "\"", 1))
        return (TOKEN_DBQUOTE);
    if (!ft_strncmp(str, "\'", 1))
        return (TOKEN_SQUOTE);
    if (!ft_strncmp(str, "|", 1))
        return (TOKEN_PIPE);
    if (!ft_strncmp(str, ">>", 2))
        return (TOKEN_REDIR_APPEND);
    if (!ft_strncmp(str, "<<", 2))
        return (TOKEN_REDIR_PRE);
    if (!ft_strncmp(str, ">", 1))
        return (TOKEN_REDIR_OUT);
    if (!ft_strncmp(str, "<", 1))
        return (TOKEN_REDIR_IN);
    if (!ft_strncmp(str, "&", 1)) //NOT NEEDED
        return (TOKEN_AND);
    // if (!ft_strncmp(str, "$", 1))
    //     return (TOKEN_DOLLAR);
    if (!ft_strncmp(str, "(", 1)) //NOT NEEDED
        return (TOKEN_OPEN_P);
    if (!ft_strncmp(str, ")", 1)) //NOT NEEDED
        return (TOKEN_CLOSE_P);
    // if (!ft_strncmp(str, " ", 1))
    //     return (TOKEN_SPACE);
    if (!ft_strncmp(str, "\\", 1)) //NOT NEEDED
        return (TOKEN_BACKSLASH);
    else
        return (TOKEN_WORD);
}

static char    *get_token_value(char   *str, TokenType type)
{
    if (type == TOKEN_EOF)
        return (ft_strdup("EOF"));
    if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || type == TOKEN_AND || type == TOKEN_DOLLAR || type == TOKEN_CLOSE_P || type == TOKEN_OPEN_P || type == TOKEN_SPACE)
        return (ft_substr(str, 0, 1));
    else if (type != TOKEN_WORD && type != TOKEN_DBQUOTE && type != TOKEN_SQUOTE)
        return (ft_substr(str, 0, 2));
    else if (type == TOKEN_WORD)
        return (ft_substr(str, 0, space_until_next(str)));
    else if (type == TOKEN_SQUOTE)
		return (squote_manager(str));
    else if (type == TOKEN_DBQUOTE)
        return (dquote_manager(str));
    else
        return NULL;
}

	static int append_token(char **str, t_list **lst)
{
    token   *tok;

    tok = ft_calloc(1, sizeof(token));
    if (!tok)
        return (0);
    tok->type = get_token_type(*str);
    tok->value = get_token_value(*str, tok->type);
    if (!tok->value)
        return (0);
    *str += ft_strlen(tok->value);
    if (tok->type == TOKEN_SQUOTE || tok->type == TOKEN_DBQUOTE)
        *str += 2;
    ft_lstadd_back(lst, ft_lstnew(tok));
    return (1);
}


//to add : EXPANDER

t_list    *tokenize(char   *str, t_list  **list)
{
    go_next(&str);
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
