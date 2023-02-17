/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:42:29 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/16 21:41:40 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*new_token(t_token **lst, char *str)
{
	t_token		*new;

	new = ft_lstnew(str);
	if (!new)
		return (NULL);
	return (ft_lstadd_back(lst, new));
}

t_token	*token_generator(char **tab)
{
	int	i;
	t_token *head;

	i = 0;
	head = NULL;
	while (tab[i])
	{
		if (!new_token(&head, tab[i]))
			return (ft_lstclear(&head), NULL);
		i++;
	}
	return (head);
}

void	minishell(char *str)
{
	char **tab;
	t_token *lst;
	t_token *head;

	tab = first_split(str);
	if (!tab)
		return (free(str), exit(0));
	lst = token_generator(tab);
	head = lst;
	tokenisation(&lst);
	print_lst(head);
	free_tab(tab, -1);
    free(str);
    ft_lstclear(&head);
}

int main()
{
	char	*str;

	while (21)
	{
        str = readline("nanoshell > ");
		if (!str)
			return (ft_putstr_fd("exit\n", 1), 21);
		if (ft_strcmp(str, "exit"))
			return (free(str), ft_putstr_fd("exit\n", 1), 21);
		minishell(str);
	}
}