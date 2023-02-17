/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:43 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/17 15:26:23 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_token *lst)
{
	while (lst)
	{
		printf("%s ", lst->value);
		printf("%d\n", lst->type);
		lst = lst->next;
	}
}