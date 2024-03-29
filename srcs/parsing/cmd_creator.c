/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:51:42 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/24 19:10:15 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*arg_red_list(t_list **arg_red, int type, char *str)
{
	t_token	*data;
	t_list	*new;

	data = create_token(str);
	if (!data)
	{
		g_g.exit_malloc = 1;
		exit (12);
	}
	data->type = type;
	new = ft_lstnew(data);
	if (!new)
	{
		ft_lstclear(arg_red, token_cleaner);
		g_g.exit_malloc = 1;
		exit (12);
	}
	return (ft_lstadd_back(arg_red, new));
}

t_cmd	*initializing_data(void)
{
	t_cmd	*data;

	data = malloc(sizeof(t_cmd));
	if (!data)
		return (NULL);
	data->arg = NULL;
	data->red = NULL;
	data->infile = -2;
	data->outfile = -2;
	data->pfd[0] = 0;
	data->pfd[1] = 0;
	return (data);
}

int	cmd_core(t_list **token, t_cmd *data, t_token *content, int *flag)
{
	if (content->type == WORD)
	{
		data->arg = arg_red_list(&data->arg, 0, content->value);
		if (!data->arg)
			return (cmd_cleaner(data), 0);
	}
	else
	{
		data->red = arg_red_list(&data->red, content->type,
				((t_token *)((*token)->next->content))->value);
		if (!data->red)
			return (cmd_cleaner(data), 0);
		(*token) = (*token)->next;
		(*flag)++;
	}
	return (1);
}

t_cmd	*data_cmd(t_list *token, int *flag)
{
	t_cmd	*data;
	t_token	*content;

	*flag = 1;
	data = initializing_data();
	if (!data)
		return (NULL);
	while (token)
	{
		content = (t_token *)token->content;
		if (content->type == PIPE)
			break ;
		if (!cmd_core(&token, data, content, flag))
			return (NULL);
		token = token->next;
		(*flag)++;
	}
	if (!token)
		*flag = 0;
	return (data);
}

void	cmd_generator(t_list **token, int i)
{
	int		flag;
	t_list	*list_cmd;
	t_list	*new_cmd;
	t_cmd	*data;
	t_list	*head;

	list_cmd = NULL;
	flag = 1;
	head = *token;
	while (flag)
	{
		data = data_cmd(*token, &flag);
		if (g_g.exit_malloc)
			cleaning_cmd(NULL, &head, &list_cmd);
		new_cmd = ft_lstnew(data);
		if (g_g.exit_malloc)
			cleaning_cmd(data, &head, &list_cmd);
		list_cmd = ft_lstadd_back(&list_cmd, new_cmd);
		while ((++i < flag) && (*token))
			(*token) = (*token)->next;
		i = -1;
	}
	ft_lstclear(&head, token_cleaner);
	looping(&list_cmd);
	return (here_doc(&list_cmd, NULL, NULL));
}
