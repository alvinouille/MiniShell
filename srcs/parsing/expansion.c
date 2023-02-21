/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:28:29 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/21 01:08:39 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	This file have to expand environment variables and apply
	differents functions in strict order depending on the
	type of token. 
	
	<State 0> remove quotes.
	<State 1> remove quotes -> magic space
	<State 2> remove quotes -> expand -> magic space
*/

char	*expansion(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == EXPAND)
			// Do job
		i++;
	}
	return (NULL);
}

char	*state_00(char *str)
{
	expansion(str);
	return (NULL);
}

char	*state_01(char *str)
{
	remove_quotes(str);
	magic_space(str);
	return (NULL);
}

char	*state_02(char *str)
{
	remove_quotes(str);
	expansion(str);
	magic_space(str);
	return (NULL);
}

void	magic_space(char *str)
{
	while (*str)
	{
		if (*str == SPACE)
			*str *= -1;
		str++;
	}
}

static t_fp_exp	handling_table(unsigned char state)
{
	static t_fp_exp	table[3] = {
		state_00,
		state_01,
		state_02
	};
	
	return (table[state]);
}

char 	*do_job(char *str)
{
	t_fp_exp	fp;
	
	fp = handling_table(get_state(str[0]));
	return (fp(str));
}

char 	*remove_quotes(char *str)
{
	char	*new;
	char	state_char;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str) - 1);
	state_char = str[i];
	str++;
	while (str[i] && str[i] != state_char)
	{
		new[i] = str[i]; // i++ tout a droite
		i++;
	}
	new[i] = 0;
	return (new);
}

// int	main(void)
// {
// 	remove_quotes("Hello World\n");
// }