/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:09:54 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/28 20:08:30 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "tools.h"

int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(char *big, char *little, int len);
bool	ft_strcmp(const char *s1, const char *s2);
int		get_state(char c);
int		ft_isalnum(int c);

void	ft_putendl_fd(char *s, int fd);
char	*ft_strdup(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
char	*join(char *s1, char *s2);
int		ft_strchr(char *str, char c);
int		ft_isalpha(int c);
char	*simple_join(char *s1, char *s2);

#endif