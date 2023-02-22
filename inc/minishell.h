/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:53:47 by alvina            #+#    #+#             */
/*   Updated: 2023/02/22 20:41:42 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	GNU C Library  */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/*	Personal Library  */
# include "utils.h"
# include "tools.h"
# include "lst.h"
# include "parsing.h"
# include "expansion.h"

/*	Declaration of the global variable required to manage the
	exit_status code  */
extern int g_exit_status;

/*	Memory cleaning  */
void	lstclear(t_dblist *dblist);
char	**free_tab(char **tab, int j);

/*	The main program  */
void	minishell(char *str, char **env);

/*	Required to create the token  */
int			is_space(char *str);
int			is_red(char *str);
int			is_pipe(char *str);
int			is_separator(char *str);
int			changing_state(char c, int state);
int			count_words(char *str);
char		**first_split(char *str);
char		**splitting(char **tab, char *str, int state);
int			wording_other(char *str, char ***tab, int j, int *state);
int			wording_sep(char *str, char ***tab, int j, int (*f)(char *));
int			length(char *str, int *state);

/*	Required to generate token  */
void	*new_token(t_token **lst, char *str);
void	token_generator(char **tab, t_dblist *dblist);

/*	Tokenisation  */
int		what_red(char *str);
void	tokenisation(t_dblist *dblist);

/*	Error management  */
void	free_exit(char *error);

#endif