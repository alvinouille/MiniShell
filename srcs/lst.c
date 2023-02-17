/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:32:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/16 17:33:08 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	return (*lst);
}

t_token	*ft_lstnew(char *str)
{
	t_token	*lst;

	lst = malloc(sizeof(t_token));
	if (!lst)
		return (NULL);
	lst->value = str;
	lst->type = 0;
	lst->next = NULL;
	return (lst);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst->next)
	{
		while (lst && lst->next)
			lst = lst->next;
	}
	return (lst);
}
