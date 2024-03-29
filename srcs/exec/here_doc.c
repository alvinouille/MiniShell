/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/24 19:54:00 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	nul_character(char *limiter)
{
	ft_putstr_fd("warning: here-document ", STDOUT_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted ", STDOUT_FILENO);
	ft_putstr_fd(limiter, STDOUT_FILENO);
	ft_putstr_fd(")\n", STDOUT_FILENO);
}

int	do_here_doc(t_list **lst, char *limiter)
{
	char	*line;

	line = NULL;
	while (!ft_strcmp(line, limiter))
	{
		free(line);
		line = readline("heredoc> ");
		if (g_g.exit_here_doc)
			return (0);
		if (!line)
		{
			nul_character(limiter);
			break ;
		}
		if (ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, ((t_cmd *)((*lst)->content))->pfd[1]);
		if (!ft_strcmp(line, "\n"))
			ft_putstr_fd("\n", ((t_cmd *)((*lst)->content))->pfd[1]);
	}
	return (1);
}

static void	end_here_doc(int stdin_cpy, t_list **tmp, t_list **list)
{
	t_list	*tmd;
	t_cmd	*content;

	tmd = *tmp;
	content = (t_cmd *)tmd->content;
	dup2(stdin_cpy, 0);
	close(stdin_cpy);
	if (g_g.exit_here_doc == 1)
	{
		g_g.exit_here_doc = 0;
		close(content->pfd[0]);
		close(content->pfd[1]);
		return (ft_lstclear(list, cmd_cleaner));
	}
	return (opening(list));
}

static void	init(int *stdin_cpy)
{
	*stdin_cpy = dup(0);
	ft_state(HERE_DOC);
	signal(SIGINT, &sig_handler);
}

void	here_doc(t_list **list, t_list *tmp, t_cmd *cmd)
{
	t_token	*token;
	t_list	*red;
	int		stdin_cpy;

	stdin_cpy = 0;
	tmp = (*list);
	init(&stdin_cpy);
	while (tmp)
	{
		cmd = (t_cmd *)(tmp->content);
		red = cmd->red;
		while (red)
		{
			token = (t_token *)(red->content);
			if (token && token->type == DRIN)
				close_w_r_side(tmp, token, cmd);
			if (g_g.exit_here_doc)
				return (end_here_doc(stdin_cpy, &tmp, list));
			red = red->next;
		}
		tmp = tmp->next;
	}
	end_here_doc(stdin_cpy, list, list);
}
