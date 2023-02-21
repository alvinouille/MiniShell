/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:32:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/21 00:54:52 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*ft_lstadd_back(t_token **lst, t_token *new)
// {
// 	t_token	*last;

// 	last = NULL;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		last = ft_lstlast(*lst);
// 		last->next = new;
// 	}
// 	return (*lst);
// }

void	init_list(t_dblist *l)
{
	l->first = NULL;
	l->last = NULL;
	l->first_env = NULL;
	l->prev_env = NULL;
}

void	add_node_back_token(t_dblist *l, char *str, int *index)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (lstclear(l), free_exit(NULL));
	new->prev = l->last;
	new->next = NULL;
	if (index)
		new->value = get_token(str, index);
	else
		new->value = str;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
}

void	add_node_back_env(t_dblist *l, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (lstclear(l), free_exit(NULL));
	new->prev = l->prev_env;
	new->next = NULL;
	new->key = key;
	new->value = value;
	if (l->prev_env)
		l->prev_env->next = new;
	else
		l->first_env = new;
	l->prev_env = new;
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

// void	*new_token(t_token **lst, char *str)
// {
// 	t_token		*new;

// 	new = ft_lstnew(str);
// 	if (!new)
// 		return (NULL);
// 	return (ft_lstadd_back(lst, new));
// }

/*	Only required to get information about the linked list  
 *	IMPORTANT NOTICE : remove before final push  
 */

void	print_lst(t_dblist dblist)
{
	while (dblist.first)
	{
		printf("value : %s\n", dblist.first->value);
		printf("%d\n", dblist.first->type);
		dblist.first = dblist.first->next;
	}
}