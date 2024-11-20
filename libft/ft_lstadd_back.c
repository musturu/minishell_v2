/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:29:33 by lmoricon          #+#    #+#             */
/*   Updated: 2024/08/17 15:13:25 by mamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tem;

	if (!lst)
	{
		*lst = new;
		return ;
	}
	if (*lst)
	{
		tem = ft_lstlast(*(lst));
		tem -> next = new;
		new -> prev = tem;
	}
	else
		*lst = new;
}
