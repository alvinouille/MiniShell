/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:21:04 by alvina            #+#    #+#             */
/*   Updated: 2023/03/30 11:37:46 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	new_state(char c, int state)
{
	if (state == NONE)
	{
		if (c == '\'' || c == '"')
			return (true);
	}
	if (state == SP_QUOTES)
	{
		if (c == '\'')
			return (true);
	}
	if (state == DB_QUOTES)
	{
		if (c == '"')
			return (true);
	}
	return (false);
}

int	get_state(char c)
{
	if (c == '\'')
		return (SP_QUOTES);
	else if (c == '"')
		return (DB_QUOTES);
	return (NONE);
}

int	ft_strrlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
