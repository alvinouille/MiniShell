/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:24:33 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/18 01:48:51 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

/* The open() system call requires these preprocessor directives  */
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>

/* Definition of boolean type  */
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/* Definition of ERROR_SIGNAL  */
typedef enum e_sig_err {
	ERR_OPEN,
	ERR_ARG,
	ERR_EXIST,
	ERR_EXE,
	ERR_FORK,
	ERR_PIPE,
	ERR_MEM,
	ERR_ENV,
	ERR_PATH,
	ERR__LENGHT
}	t_sig_err;

/* It required by exit_error in <main.c> to handle differents
   types of errors  */
typedef struct s_error
{
	int		sig_err;
	char	*sig_msg;
}			t_error;

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**env;
}			t_args;

typedef struct s_storage_cmd
{
	char					**path;
	char					**bin_args;
	char					*bin_path;
	char					*bin;
	int						pos;
	struct s_storage_cmd	*next;
	struct s_storage_cmd	*prev;
}							t_storage_cmd;

typedef struct s_dblist
{
	t_storage_cmd	*first;
	t_storage_cmd	*last;
}					t_dblist;

typedef struct s_data
{
	int				pfd[2];
	int				fd_in;
	int				fd[2];
	int				nb_cmd;
	pid_t			*pid;
	t_args			args;
	t_dblist		dblist;
}					t_data;

#endif
