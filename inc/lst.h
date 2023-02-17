/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:18:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/16 18:19:16 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "tools.h"

t_token	*ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstnew(char *str);
t_token	*ft_lstlast(t_token *lst);

#endif