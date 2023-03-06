/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:18:56 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/01 16:15:48 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getsize(t_dblist dblist)
{
	int	size;

	size = 0;
	while (dblist.first)
	{
		size += ft_strlen(dblist.first->value);
		dblist.first = dblist.first->next;
	}
	return (size);
}

void	create_token_momo(t_dblist *dblist, char *new)
{
	t_token		*tmp;
	char		**split;
	int			i;
	
	i = 0;
	tmp = dblist->first;
	split = ft_split(new, ' ');
	while (split[i])
		i++;
	printf("i : %d\n", i);
	while (i > 0)
	{
		tmp->value = split[i];
		printf("tmp->value : %s\n", tmp->value);
		i--;
	}
}

void	tokjoin(t_dblist *dblist)
{
	char		*new;
	t_token		*tmp;
	// t_dblist	*new;

	new = NULL;
	tmp = dblist->first;
	new = malloc(sizeof(char) * getsize(*dblist) + 1);
	while (tmp)
	{
		new = ft_strjoin(new, tmp->value);
		tmp = tmp->next;
	}
	create_token_momo(dblist, new);
}
