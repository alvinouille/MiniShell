/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:55:39 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/20 18:32:19 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define NO_ENDL 0
# define ENDL 1

static int	slash_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	if (str[i])
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;	
		}
		return (1);
	}
	return (0);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + 48, fd);
}

static void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!*tab)
		return ;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "$?", 2) && ft_strlen(tab[i]) == 2)
		{
			ft_putnbr_fd(g_exit_status, 1);
			break;
		}
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	echo(char **arg)
{
	int	i;
	int n;
	int	to_print;

	i = 0;
	n = ENDL;
	to_print = 0;
	if (!arg || !*arg)
	{
		write(1, "\n", 1);
		return ;
	}
	while (arg[i])
	{
		if (!slash_n(arg[i]))
		{
			to_print = i;
			break;
		}
		n = NO_ENDL;
		i++;
	}
	if (n == NO_ENDL)
	{
		if (to_print)
			print_tab(&arg[to_print]);
	}
	else
	{
		if (arg)
			print_tab(arg);
		write(1, "\n", 1);
	}
	g_exit_status = 0;
}