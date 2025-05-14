/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:49 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:00:37 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_fork(t_info *table)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!fork)
		return (printf(ERR_MEM), NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL))
			return (printf(ERR_MTX), destroy_mutex(fork, i), NULL);
	}
	return (fork);
}

static int	set_philo_struct(t_info *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		table->philo[i].pos = i + 1;
		table->philo[i].meals_counter = 0;
		table->philo[i].table = table;
		table->philo[i].fork[0] = i;
		table->philo[i].fork[1] = i - 1;
		if (i == 0)
			table->philo[i].fork[1] = table->nb_philo - 1;
	}
	return (1);
}

int	init_table(t_info *table)
{
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		return (printf(ERR_MEM), 0);
	if (!set_philo_struct(table))
		return (0);
	table->forks = init_fork(table);
	table->death_flag = 0;
	if (!table->forks)
		return (0);
	if (pthread_mutex_init(&table->lock_eat, NULL))
		return (crash(ERR_MTX, table));
	if (pthread_mutex_init(&table->lock_death, NULL))
	{
		pthread_mutex_destroy(&table->lock_eat);
		return (crash(ERR_MTX, table));
	}
	if (pthread_mutex_init(&table->print_mutex, NULL))
	{
		pthread_mutex_destroy(&table->lock_eat);
		pthread_mutex_destroy(&table->lock_death);
		return (crash(ERR_MTX, table));
	}
	return (1);
}
