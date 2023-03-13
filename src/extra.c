/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:26:15 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/15 19:25:39 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "tools.h"
#include "error.h"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	extra_launcher(t_data *data, int i)
{
	close(data->pfd[1]);
	if (i != 0)
		close(data->fd_in);
	if (i != data->nb_cmd)
		data->fd_in = data->pfd[0];
}

char	**extra_bin_args(char *cmd, char *bin, int i)
{
	char	**str;

	str = malloc(sizeof(char *) * 3);
	str[0] = ft_strdup(bin);
	str[1] = ft_strdup(&cmd[i]);
	str[2] = NULL;
	return (str);
}

void	extra_init(t_data *data)
{
	if (data->fd[0] != -1)
		close(data->fd[0]);
	perror(data->args.argv[data->args.argc - 1]);
	// exit(EXIT_FAILURE);
}

void	extra_loop_free(t_storage_cmd *node)
{
	int	i;

	i = -1;
	if (node->bin_args != NULL)
	{
		while (node->bin_args[++i])
			free(node->bin_args[i]);
	}
	free(node->bin_args);
	i = -1;
	if (node->path != NULL)
	{
		while (node->path[++i])
			free(node->path[i]);
	}
	free(node->path);
}

void	loop_job(t_data *data, t_storage_cmd *tmp, int i)
{
	if (pipe(data->pfd) == -1)
		exit_error(ERR_PIPE);
	if (ft_strcmp("here_doc", data->args.argv[1]) && i == 0)
		here_doc(data);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		exit_error(ERR_FORK);
	else if (data->pid[i] == 0)
		do_job(data, tmp);
	else
		extra_launcher(data, i);
}
