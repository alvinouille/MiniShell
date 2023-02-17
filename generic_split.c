/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:02:38 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/17 02:28:14 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum e_state
{
	NONE,
	SP_QUOTES,
	DB_QUOTES
}	t_state;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static bool	new_state(char c, int state)
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

static int	get_state(char c)
{
	if (c == '\'')
		return (SP_QUOTES);
	else if (c == '"')
		return (DB_QUOTES);
	return (NONE);
}

char	*ft_strdup(char *str, int *k)
{
	char			*dup;
	int				j;
	int				state;

	state = get_state(str[*k]);
	j = 0;
	dup = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[*k])
	{
		dup[j] = str[*k];
		j++;
		(*k)++;
		if (new_state(str[*k], state))
		{
			if (!state)
				break ;
			dup[j] = str[*k];
			j++;
			(*k)++;
			break ;
		}
	}
	dup[j] = '\0';
	return (dup);
}

int	countwords(char *str)
{
	int		index;
	int		word;
	int		state;
	
	word = 0;
	index = 0;
	state = get_state(str[index]);
	index++;
	while (str[index])
	{
		if (new_state(str[index], state))
		{
			word++;
			if (state && str[index + 1] != 0)
				index++;
			state = get_state(str[index]);
		}
		index++;
	}
	if (state == NONE)
		word++;
	return (word);
}

char	**ft_split(char *str)
{
	static int		k = 0;
	char	**split;
	int		index;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	index = 0;
	split = malloc(sizeof(char *) * (countwords(str) + 1));
	if (!split)
		return (NULL);
	while(i < countwords(str))
	{
		split[i] = ft_strdup(str, &k);
		i++;
	}
	split[i] = 0;
	k = 0;
	return (split);
}

int main(int argc, char **argv)
{
	int		i;
	char	**splited;
	char	*str;

	str = "'\"\"'\"a\"$L'+2'$HOME_\"'''\"ab  ";
	i = 0;
	printf("str : %s\n", str);
	splited = ft_split(str);
	if (argc != 2)
		return (-1);
	while (splited[i])
	{
		printf("splited : |%s|\n", splited[i]);
		i++;
	}
}