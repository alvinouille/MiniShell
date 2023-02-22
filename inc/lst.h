/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:18:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/22 15:35:35 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "tools.h"

void		get_dblist(void (*fp)(t_dblist *), t_dblist **dblist);
void		add_node_back_env(t_dblist *l, char *key, char *value);
void		add_node_back_token(t_dblist *l, char *str, int *index);
void		print_lst(t_dblist dblist);
void		init_list(t_dblist *dblist);

// void	*new_token(t_token **lst, char *str);
// t_token	*ft_lstadd_back(t_token **lst, t_token *new);
// t_token	*ft_lstnew(char *str);
// t_token	*ft_lstlast(t_token *lst);

#endif