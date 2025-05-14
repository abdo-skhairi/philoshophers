/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:41 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:37:10 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_table_arg(t_info *table, int **ent_arg, int n_arg)
{
	table->tt_die = (t_long)(*ent_arg[1]);
	table->tt_eat = (t_long)(*ent_arg[2]);
	table->tt_sleep = (t_long)(*ent_arg[3]);
	table->nb_philo = *ent_arg[0];
	table->n_meals = -1;
	if (n_arg == 5)
		table->n_meals = *ent_arg[4];
	clear_leaks(&ent_arg);
	return (1);
}

static int	number_is_valid(int **ent_arg, int n_arg)
{
	int		i;
	bool	flag;

	i = 0;
	flag = 0;
	if (n_arg == 5)
		flag = 1;
	while (i < n_arg - flag)
		if (!*ent_arg[i++])
			return (clear_leaks(&ent_arg), printf(ERR_NBR), 0);
	i = 0;
	while (i < n_arg)
		if (*ent_arg[i++] < 0 || *ent_arg[i++] < 60)
			return (clear_leaks(&ent_arg), printf(ERR_NBR), 0);
	return (1);
}

static int	ft_atoi(char *str)
{
	long long	nb;
	int			sg;

	nb = 0;
	sg = 1;
	while (*str && *str == ' ')
		str++;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			sg = -1;
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (-1);
		nb = (nb * 10) + (*str++ - 48);
	}
	nb *= sg;
	if (nb > 2147483647 || nb < -2147483648)
		return (-1);
	return ((int)nb);
}

static int	philo_arguments(t_info *table, int n_arg, char **arg)
{
	int		**ent_arg;
	int		i;

	ent_arg = malloc(sizeof(int *) * (n_arg + 1));
	if (!ent_arg)
		return (printf(ERR_MEM), 0);
	i = 0;
	while (arg[++i])
	{
		ent_arg[i - 1] = malloc(sizeof(int));
		if (!ent_arg[i - 1])
		{
			ent_arg[i - 1] = NULL;
			return (clear_leaks(&ent_arg), printf(ERR_MEM), 0);
		}
		*ent_arg[i - 1] = ft_atoi(arg[i]);
	}
	ent_arg[i - 1] = NULL;
	if (!number_is_valid(ent_arg, n_arg))
		return (0);
	return (set_table_arg(table, ent_arg, n_arg));
}

int	philo_parsing(int n_arg, char **args, t_info *table)
{
	if (n_arg != 4 && n_arg != 5)
		return (printf(ERR_ARG), 0);
	return (philo_arguments(table, n_arg, args));
}
