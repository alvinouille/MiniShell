/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:12:42 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/17 01:25:38 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

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
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

typedef enum e_state
{
	NONE,
	SP_QUOTES,
	DB_QUOTES
}	t_state;

#endif