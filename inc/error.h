/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:47:36 by mmeguedm          #+#    #+#             */
/*   Updated: 2022/11/14 13:22:15 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "tools.h"

void	check_file_permission(t_data *data);
void	check_path_env(t_data *data);
void	exit_error(int sig_err);
void	parse_args(t_data *data, int index);
void	close_fd(t_data *data);

#endif
