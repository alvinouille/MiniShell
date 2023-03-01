/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:28:29 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/01 20:44:07 by mmeguedm         ###   ########.fr       */
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

int	get_var_size(char *str)
{
	int	i;
	int	vr_size;
	
	vr_size = 0;
	i = 0;
	while (str[i] && str[i] != EXPAND)
		i++;
	while (str[i] && ft_isalnum(str[i]))
	{
		i++;
		vr_size++;
	}
	return (vr_size);
}

int	get_exp_size(char *env_var)
{
	return (ft_strlen(ft_getenv(env_var)));
}

void	fill_sign_var(char *token, char **sign_var)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	(*sign_var) = malloc(sizeof(char) * (i + 10));
	i = 0;
	while (token[i])
	{
		(*sign_var)[i] = token[i];
		i++;
	}
	(*sign_var)[i] = 0;
}


int	set_var(char *str, char **sh_var, char **sign_var)
{
	int			i;
	int			j;

	(*sh_var) = malloc(sizeof(char) * get_var_size(str) + 2);
	if (!(*sh_var))
		free_exit(NULL);
	j = 0;
	i = 0;
	while (str[i] && str[i] != EXPAND)
		i++;
	if (str[i] == EXPAND)
		i++;
	while (str[i] && ft_isalnum(str[i]))
	{
		(*sh_var)[j] = str[i];
		i++;
		j++;
	}
	if (str[i] == '_')
		return (1);
	(*sh_var)[j] = 0;
	if (ft_issign(str[i]))
		return (fill_sign_var(&str[i], sign_var), 2);
	return (0);
}

void	fill_sign_new(char **new, char *sign_var)
{
	int	i;
	int	len_sign;
	
	len_sign = ft_strlen(sign_var);
	i = 0;
	while ((*new)[i])
		i++;
	while (len_sign >= 0)
	{
		(*new)[i] = *sign_var;
		len_sign--;
		i++;
		sign_var++;
	}
	(*new)[i] = 0;
}

char	*expansion(char *token)
{
	t_dblist	*dblist;
	char		*sh_var;
	char		*new;
	char		*sign_var;
	int			res;

	res = set_var(token, &sh_var, &sign_var);
	if (res == 1)
		return (NULL);
	if (sh_var[0] == 0)
		return (token);
	new = malloc(sizeof(char) * (ft_strlen(token) + ((get_exp_size(sh_var)) - (get_var_size(token)) + 1)));
	// new = malloc(10000);
	if (!new)
		return (free_exit(NULL), NULL);
	new = ft_getenv(sh_var);
	if (!new) 
		return (NULL);
	if (res == 2)
		fill_sign_new(&new, sign_var);
	return (new);
}

char	*state_00(char *str)
{
	return (expansion(str));
}

char	*state_01(char *str)
{
	char	*new;
	
	// printf("str1 : %s\n", str);
	new = remove_quotes(str);
	magic_space(new);
	return (new);
}

char	*state_02(char *str)
{
	char	*new;
	char	*new2;
	
	// printf("str2 : %s\n", str);
	new = remove_quotes(str);
	new2 = expansion(new);
	magic_space(new2);
	return (new2);
}

void	magic_space(char *str)
{
	if (!str)
		return ;
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
