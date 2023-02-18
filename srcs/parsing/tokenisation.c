/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:33:36 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/18 02:01:23 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	what_red(char *str)
{
	if (ft_strnstr(str, "<<", 2))
		return (DROUT);
	else if (ft_strnstr(str, ">>", 2))
		return (DRIN);
	else if (ft_strnstr(str, "<", 1))
		return (RIN);
	else
		return (ROUT);
}

void	tokenisation(t_dblist *dblist)
{
	t_token *previous;
	t_token	*buf;

	buf = dblist->first;
	previous = NULL;
	while (buf)
	{
		if (is_pipe(buf->value))
			buf->type = PIPE;
		else if (is_red(buf->value))
			buf->type = what_red(buf->value);
		else if (previous)
		{
			if (is_red(previous->value))
			{
				if (previous->type == 5)
					buf->type = LIM;
				else
					buf->type = FD;
			}
		}
		else
			buf->type = WORD;
		previous = buf;
		buf = buf->next;
	}
}