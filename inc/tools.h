/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:12:42 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/16 02:38:31 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define EXPAND 36

# include <aio.h>
typedef enum e_env_setting{
	CREATING,
	DELETING,
	ADDING,
	MODIFYING, 
	CLEANING,
	GETTING,
	APPENDING
}	t_env_setting;

extern int g_exit_status;

typedef char * (*t_fp_exp)(char *str);

typedef enum e_type
{
	WORD,
	FD,
	LIM,
	RIN,
	ROUT,
	DRIN,
	DROUT,
	PIPE
}	t_type;

typedef struct s_token
{
	char	*value;
	int		type;
	char	**path;
	char	**bin_args;
	char	*bin_path;
	char	*bin;
	int		pos;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**env;
}			t_args;

typedef	struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_list
{
	void			*content;
	int				a;
	struct s_list	*next;
}					t_list;

typedef void (*pf)(t_list **, char **, char *);

typedef struct s_cmd
{
	t_list 		*arg;
	t_list 		*red;
	int			pfd[2];
	int			infile;
	int			outfile;
}				t_cmd;

typedef enum e_state
{
	NONE,
	SP_QUOTES,
	DB_QUOTES
}	t_state;

/*	Required by Pipex to create the new double linked list
	that contains all data about binaries.
 */
typedef struct s_storage_cmd
{
	char					**path;
	char					**bin_args;
	char					*bin_path;
	char					*bin;
	char					**env;
	int						nb_cmd;
	int						pfd[2];
	int						fd_in;
	int						fd[2];
	pid_t					*pid;
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
	pid_t			*pid;
	t_dblist		dblist;
	t_args			args;
}					t_data;
/*	End of Pipex prerequisites  */

#endif