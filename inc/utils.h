/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:09:54 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/16 22:06:26 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "tools.h"

int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(char *big, char *little, int len);
bool	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *str, int *k);

#endif