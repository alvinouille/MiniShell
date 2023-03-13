/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:41:15 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/12/01 19:50:19 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_H
# define GET_H

# include "tools.h"

char	*get_bin(char *cmd);
char	**get_path(char	*env[]);
char	*get_bin_path(char *cmd, char *bin, char **path);
char	**get_bin_args(char *cmd, char *bin);

#endif
