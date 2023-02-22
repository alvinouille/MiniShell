/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:42:29 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/22 16:24:05 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	token_generator(char **tab, t_dblist *dblist)
{
	int	i;

	i = -1;
	while (tab[++i])
		add_node_back_token(dblist, tab[i], NULL);
}

void	minishell(char *str, char **env)
{
	char		**tab;
	t_dblist	*dblist;
	t_dblist	*test;
	
	get_dblist(&init_list, &dblist);
	init_env(dblist, env);
	tab = first_split(str);
	if (!tab)
		return (free(str), exit(0));
	token_generator(tab, dblist);
	tokenisation(dblist);
	get_dblist(NULL, &test);
	// print_lst(test);
	split_state(dblist);
	// free_tab(tab, -1);
    // free(str);
    // lstclear(&dblist);
}

void	init_env(t_dblist *dblist, char **env)
{
	char	**new_env;
	
	new_env = NULL;
	// if (!env || !*env)
	// 	return (NULL);
	while (*env)
	{
		new_env = ft_split(*env, '=');
		add_node_back_env(dblist, new_env[0], new_env[1]);
		env++;
	}
}

int main(int argc, char **argv, char **env)
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
		minishell(str, env);
	}

	// init_list(&dblist);
	// add_node_back_token(&dblist, "echo", NULL);
	// add_node_back_token(&dblist, "\"a\"$L'+2'$HOME_", NULL);
	// // print_lst(dblist);
	// split_state(&dblist);
	// print_lst(dblist);
}