/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:25:50 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/21 18:34:22 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

char 	*remove_quotes(char *str);
char	*do_job(char *str);
void	split_state(t_dblist *old_dblist);
char	*get_token(char *str, int *k);
char	**ft_split(char const *s, char c);
void	magic_space(char *str);
void	init_env(t_dblist *dblist, char **env);

#endif