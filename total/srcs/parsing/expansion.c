/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:28:29 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/27 21:01:46 by mmeguedm         ###   ########.fr       */
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
	t_dblist	*dblist;
	t_env		*tmp;

	get_dblist(NULL, &dblist);
	tmp = dblist->first_env;
	while (tmp)
	{
		if (ft_strcmp(env_var, tmp->key))
			return (ft_strlen(tmp->key));
		tmp = tmp->next;
	}
	return (-1);
}

char	*set_var(char *str)
{
	char		*sh_var;
	int			i;
	int			j;

	sh_var = malloc(sizeof(char) * get_var_size(str) + 2);
	if (!sh_var)
		return (free_exit(NULL), NULL);
	j = 0;
	i = 0;
	while (str[i] && str[i] != EXPAND)
		i++;
	if (str[i] == EXPAND)
		i++;
	while (str[i] && ft_isalnum(str[i]))
	{
		sh_var[j] = str[i];
		i++;
		j++;
	}
	sh_var[j] = 0;
	return (sh_var);
}

char	*var_expand(char *sh_var)
{
	t_dblist	*dblist;
	t_env		*tmp;
	char		*expand;

	get_dblist(NULL, &dblist);
	printf("token : %s\n", sh_var);
	tmp = dblist->first_env;
	while (tmp)
	{
		if (ft_strcmp(sh_var, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*expansion(char *token)
{
	t_dblist	*dblist;
	char		*sh_var;
	char		*new;
	int			i;

	sh_var = set_var(token);
	new = malloc(sizeof(char) * ((get_exp_size(token)) - (get_var_size(token)) + 1));
	if (!new)
		return (free_exit(NULL), NULL);
	new = var_expand(sh_var);
	if (!new)
		return (token);
	return (new);
}

char	*state_00(char *str)
{
	return (expansion(str));
}

char	*state_01(char *str)
{
	char	*new;

	new = remove_quotes(str);
	magic_space(new);
	return (new);
}

char	*state_02(char *str)
{
	char	*new;
	char	*new2;
	
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
