/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:42:29 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/18 04:20:49 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;


void	token_generator(char **tab, t_dblist *dblist)
{
	int	i;

	i = -1;
	while (tab[++i])
		add_node_back(dblist, tab[i], NULL);
}

void	minishell(char *str)
{
	char **tab;
	t_dblist	dblist;

	init_list(&dblist);
	tab = first_split(str);
	if (!tab)
		return (free(str), exit(0));
	token_generator(tab, &dblist);
	tokenisation(&dblist);
	print_lst(dblist);
	free_tab(tab, -1);
    free(str);
    lstclear(&dblist);
}

int main()
{
	char		*str;
	
	g_exit_status = 0;
	while (21)
	{
        str = readline("femstohell > ");
		if (!str)
			return (ft_putstr_fd("exit\n", 1), 21);
		if (ft_strcmp(str, "exit"))
			return (free(str), ft_putstr_fd("exit\n", 1), 21);
		minishell(str);
	}
	t_dblist	dblist;

	// init_list(&dblist);
	// add_node_back(&dblist, "echo", NULL);
	// add_node_back(&dblist, "\"a\"$L'+2'$HOME_", NULL);
	// // print_lst(dblist);
	// split_state(&dblist);
	// print_lst(dblist);
}