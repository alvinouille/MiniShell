/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:16:17 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/13 14:01:28 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(char *error)
{
	perror(error);
	exit(g_g.exit_status);
	clear_history();
}

int	error_msg(char *value)
{
	ft_putstr_fd("nanoshell: syntax error near unexpected token : ", 2);
	ft_putendl_fd(value, 2);
	g_g.exit_status = 2;
	return (0);
}

void	exit_malloc(void)
{
	handler(CLEANING, NULL, NULL);
	rl_clear_history();
	exit(12);
}
