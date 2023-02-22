/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:02:38 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/21 18:49:55 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	The string will be split at each change of state.
	A new_dblist containing splited token is created and
	the old_dblist point to the new_dblist .
*/

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

int	get_state(char c)
{
	if (c == '\'')
		return (SP_QUOTES);
	else if (c == '"')
		return (DB_QUOTES);
	return (NONE);
}

char	*get_token(char *str, int *k)
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
	return (do_job(dup));
}

static int	countwords(char *str)
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

void	split_state(t_dblist *old_dblist)
{
	static int	index = 0;
	t_dblist	new_dblist;
	t_token		*tmp;
	int			j;

	init_list(&new_dblist);
	tmp = old_dblist->first;
	while (tmp)
	{
		j = -1;
		while (++j < countwords(tmp->value))
			add_node_back_token(&new_dblist, tmp->value, &index);
		tmp = tmp->next;
		index = 0;
	}

	(*old_dblist) = new_dblist;
}

// int main(int argc, char **argv)
// {
// 	int		i;
// 	char	*str1;
// 	char	*str2;
// 	t_token	*head;
// 	t_token	*splited;
	
// 	// str1  = "'\"\"'\"a\"$L'+2'$HOME_\"'''\"ab  ";
// 	i = 0;
// 	str1  = "echo";
// 	str2 = "\"a\"$L'+2'$HOME_";
// 	new_token(&head, str1);
// 	new_token(&head, str2);
// 	splited = split_state(head);
// 	while (splited != NULL)
// 	{
// 		i++;
// 		// printf("str : %s\n", splited->value);
// 		splited = splited->next;
// 	}
// 	printf("i : %d\n", i);
// 	// while (splited[i])
// 	// {
// 	// 	printf("splited : |%s|\n", splited[i]);
// 	// 	i++;
// 	// }
// }
