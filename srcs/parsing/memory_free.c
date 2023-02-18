/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:43:34 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/18 01:46:14 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstclear(t_dblist *l)
{
	t_token	*buf;
	t_token	*body;

	if (!l->first)
		return ;
	buf = l->first;
	while (buf)
	{
		body = buf->next;
		free(body);
		buf = buf->next;
	}
}

char	**free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	if (j == -1)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	else
	{
		while (i < j)
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
	return (NULL);
}