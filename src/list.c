/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:53:16 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/15 16:22:42 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "get.h"
#include "utils.h"
#include "error.h"
#include <stdlib.h>

void	init_list(t_data *data)
{
	data->dblist.first = NULL;
	data->dblist.last = NULL;
}

void	add_node_front(t_dblist *l, int val)
{
	t_storage_cmd	*new;

	new = malloc(sizeof(*new));
	if (!new)
		exit(EXIT_FAILURE);
	new->pos = val;
	new->next = l->first;
	new->prev = NULL;
	if (l->first)
		l->first->prev = new;
	else
		l->last = new;
	l->first = new;
}

void	add_node_back(t_dblist *l, char *cmd, char *env[], t_data *data)
{
	t_storage_cmd	*new;
	static int		pos = 1;

	new = malloc(sizeof(*new));
	if (!new && pos > 1)
		return (lstfree(data), exit_error(ERR_MEM));
	else if (!new && pos == 1)
		return (exit_error(ERR_MEM));
	new->pos = pos;
	new->prev = l->last;
	new->next = NULL;
	new->bin = get_bin(cmd);
	new->path = get_path(env);
	new->bin_args = get_bin_args(cmd, new->bin);
	new->bin_path = get_bin_path(cmd, new->bin, new->path);
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
	pos++;
}

void	add_node(t_storage_cmd **storage, char *cmd, char *env[])
{
	t_storage_cmd	*new;
	static int		pos = 1;

	new = malloc(sizeof(*new));
	if (!new)
		return (exit_error(ERR_MEM));
	new->next = (*storage);
	new->bin = get_bin(cmd);
	new->path = get_path(env);
	new->bin_args = get_bin_args(cmd, new->bin);
	new->bin_path = get_bin_path(new->bin_args[0], new->bin, new->path);
	new->pos = pos;
	*(storage) = new;
	pos++;
}

void	lstfree(t_data *l)
{
	t_storage_cmd	*node;
	t_storage_cmd	*tmp;
	int				i;

	tmp = l->dblist.first;
	free(l->pid);
	while (tmp)
	{
		i = -1;
		node = tmp;
		tmp = tmp->next;
		free(node->bin);
		free(node->bin_path);
		extra_loop_free(node);
		free(node);
	}
	l->dblist.first = NULL;
	l->dblist.last = NULL;
}
