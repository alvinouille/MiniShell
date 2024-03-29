/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:18:56 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/13 16:02:58 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getsize(t_list *list)
{
	int		size;
	t_token	*data;

	data = (t_token *)(list->content);
	size = 0;
	while (list)
	{
		data = (t_token *)(list->content);
		size += ft_strlen(data->value);
		list = list->next;
	}
	return (size);
}

int	cleaning_spl_tkn(char **tab, t_list *lst)
{
	free_tab(tab, -1);
	if (lst)
		ft_lstclear(&lst, token_cleaner);
	return (0);
}

int	split_token(t_list **list, char *new, t_list *new_list, int i)
{
	t_list	*new_node;
	t_token	*data;
	char	**split;

	split = ft_split(new, ' ');
	if (!split)
		return (0);
	while (split && split[i] && split[i][0])
	{
		data = create_token(split[i]);
		new_node = ft_lstnew(data);
		if (!new_node || !data)
			return (free(new), cleaning_spl_tkn(split, new_list));
		new_list = ft_lstadd_back(&new_list, new_node);
		i++;
	}
	if (split && split[i] && !split[i][0])
	{
		new_list = ft_lstadd_back(&new_list, ft_lstnew(create_token("\0")));
		free(split[i]);
		free(split);
		split = NULL;
	}
	ft_lstclear(list, token_cleaner);
	return ((*list) = new_list, free(new), free_tab(split, -1), 1);
}

int	one_token_treatment(t_list **list)
{
	t_token	*data;
	char	*new;

	data = (t_token *)((*list)->content);
	if (data->type == WORD || data->type == FD)
	{
		new = ft_strdup(((t_token *)((*list)->content))->value);
		if (new && new[0] != '\0')
			split_token(list, new, NULL, 0);
		else
			free(new);
	}
	return (1);
}

int	tokjoin(t_list **list, int j)
{
	char	*new;
	t_list	*tmp;
	t_token	*data;

	if (j > 1)
	{
		tmp = (*list);
		data = (t_token *)((*list)->content);
		new = NULL;
		new = malloc(sizeof(char) * getsize(*(list)) + 1);
		if (!new)
			return (0);
		new[0] = '\0';
		while (tmp)
		{
			data = (t_token *)(tmp->content);
			new = ft_strjoin(new, data->value);
			if (!new)
				return (0);
			tmp = tmp->next;
		}
		return (split_token(list, new, NULL, 0));
	}
	else
		return (one_token_treatment(list));
}
