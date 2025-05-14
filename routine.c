/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:28 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:00:50 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo, bool condition)
{
	int	status;

	status = 0;
	if (condition == 0)
	{
		pthread_mutex_lock(&philo->table->lock_death);
		if (philo->table->death_flag == 1)
			status = 1;
		pthread_mutex_unlock(&philo->table->lock_death);
		return (status);
	}
	else
	{
		if (philo->table->n_meals < 0)
			return (0);
		if (philo->meals_counter < philo->table->n_meals)
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (philo->pos % 2 == 0)
		ft_usleep(philo->table->tt_eat / 2, philo->table);
	while (!is_alive(philo, 0) && !is_alive(philo, 1))
	{
		think(philo);
		if (!eat(philo))
			return (NULL);
		sleeping(philo);
	}
	return (NULL);
}

static void	set_time(t_info *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		table->philo[i].start_time = get_time();
		table->philo[i].last_meal_time = get_time();
	}
}

static int	philo_create(t_info *table)
{
	int	i;

	i = -1;
	set_time(table);
	if (pthread_create(&table->monitor_thread, NULL, monitor, table))
		return (crash(ERR_PTH, table));
	while (++i < table->nb_philo)
		if (pthread_create(&table->philo[i].thread, NULL,
				&routine, &table->philo[i]))
			return (crash(ERR_PTH, table));
	i = -1;
	if (pthread_join(table->monitor_thread, NULL))
		return (crash(ERR_WTH, table));
	while (++i < table->nb_philo)
		if (pthread_join(table->philo[i].thread, NULL))
			return (crash(ERR_WTH, table));
	return (1);
}

int	philo_start_dining(t_info *table)
{
	if (!table->n_meals)
		return (1);
	if (!philo_create(table))
		return (0);
	return (1);
}
