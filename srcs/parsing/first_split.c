/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:55:05 by alvina            #+#    #+#             */
/*   Updated: 2023/04/13 19:43:34 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	red_str(char *str, char ***tab, int j, int (*f)(char *))
{
	int	i;

	i = 0;
	(*tab)[j] = malloc(sizeof(char) * (f(str) + 1));
	if (!(*tab)[j])
	{
		free_tab(*tab, j);
		return (0);
	}
	while (f(&str[i]) && str[i])
	{
		(*tab)[j][i] = str[i];
		i++;
	}
	(*tab)[j][i] = '\0';
	return (i);
}

static int	word_str(char *str, char ***tab, int j)
{
	int	i;
	int	len;

	i = 0;
	len = length(str);
	(*tab)[j] = malloc(sizeof(char) * len + 1);
	if (!(*tab)[j])
	{
		free_tab(*tab, j);
		return (0);
	}
	while (i < len)
	{
		(*tab)[j][i] = str[i];
		i++;
	}
	(*tab)[j][i] = '\0';
	return (i);
}

static int	spliter(char *substr, char **tab, int *j, char *str)
{
	int	a;

	if (is_pipe(substr))
		a = red_str(substr, &tab, *j, is_pipe);
	else if (is_red(substr))
		a = red_str(substr, &tab, *j, is_red);
	else
		a = word_str(substr, &tab, *j);
	if (!a)
	{
		handler(4, NULL, NULL);
		free(str);
		exit(0);
	}
	(*j)++;
	return (a);
}

char	**splitting(char **tab, char *str)
{
	int	j;
	int	i;
	int	state;

	i = 0;
	j = 0;
	state = changing_state((char)-1);
	while (str[i])
	{
		state = changing_state(str[i]);
		if (state == 0 && is_separator(&str[i]))
		{
			if (!is_space(&str[i]))
				i += spliter(&str[i], tab, &j, str) - 1;
		}
		else if (str[i] != ' ' || state != 0)
			i += spliter(&str[i], tab, &j, str) - 1;
		i++;
	}
	tab[j] = 0;
	return (tab);
}

void	first_split(char *str)
{
	char	**tab;

	if (!parse_quote(str))
	{
		free(str);
		return ;
	}
	tab = (char **)malloc(sizeof(char *) * (count_words(str, -1) + 1));
	if (!tab)
	{
		free(str);
		exit_malloc();
	}
	tab = splitting(tab, str);
	free(str);
	if (!tab)
		exit_malloc();
	return (token_generator(tab, -1));
}
