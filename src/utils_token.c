/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:39:35 by lmoricon          #+#    #+#             */
/*   Updated: 2024/08/20 16:52:39 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_istokenchar(char c)
{
    if (c == '|' || c == '>' || c == '<' || c == '&' || c == '$' || c == ')' || c == '(' || c == '"' || c == '\'')
        return (1);
    return (0);
}

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

void    go_next(char **str)
{
    while (ft_isspace(**str))
        *str = *str + 1;
}

/* da aggiungere che potrebbero non esserci spazi, quindi in caso delimitato da /0 o un altro token*/
int space_until_next(char   *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isspace(str[i]) || ft_istokenchar(str[i]))
            break ;
        i++;
    }
    return (i);
}

