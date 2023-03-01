/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:32:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/01 17:13:41 by mmeguedm         ###   ########.fr       */
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


void	add_node_back_token(t_list **l, char *str, int *index)
{
	t_token	*data;
	t_list	*new;

	data = malloc(sizeof(*data));
	new = malloc(sizeof(*new));
	if (!data || !new)
		return (ft_lstclear(l, token_cleaner), free_exit(NULL));
	data->value = get_token(str, index);
	new->content = data;
	new->next = NULL;
	ft_lstadd_back(l, new);
}

void	print_token(void *content)
{
	t_token *data;

	data = (t_token *)content;
	printf("%s ", data->value);
	printf("%d \n", data->type);
}

void	print_env(void *content)
{
	t_env *data;

	data = (t_env *)content;
	printf("%s=", data->key);
	printf("%s \n", data->value);
}

void	print_cmd(void *content)
{
	t_cmd *data;
	
	data = (t_cmd *)content;
	printf("\n---COMMANDE---\n");
	printf("\nARG : ");
	print_lst(data->arg, print_token);
	printf("\nRED : ");
	print_lst(data->red, print_token);
}

void	print_lst(t_list *lst, void (*print)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		print(lst->content);
		lst = lst->next;
	}
	printf("\n");
}
// void	add_node_back_env(t_dblist *l, char *key, char *value)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(*new));
// 	if (!new)
// 		return ;
// 		// return (ft_lstclear(l), free_exit(NULL));
// 	new->prev = l->prev_env;
// 	new->next = NULL;
// 	new->key = key;
// 	new->value = value;
// 	if (l->prev_env)
// 		l->prev_env->next = new;
// 	else
// 		l->first_env = new;
// 	l->prev_env = new;
// }

// t_token	*ft_lstnew(char *str)
// {
// 	t_token	*lst;

// 	lst = malloc(sizeof(t_token));
// 	if (!lst)
// 		return (NULL);
// 	lst->value = str;
// 	lst->type = 0;
// 	lst->next = NULL;
// 	return (lst);
// }

// t_token	*ft_lstlast(t_token *lst)
// {
// 	if (lst->next)
// 	{
// 		while (lst && lst->next)
// 			lst = lst->next;
// 	}
// 	return (lst);
// }

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
