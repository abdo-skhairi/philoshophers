/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:22 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:00:44 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	timer_of_death(t_philo *philo)
{
	t_long		result_time;
	bool		status;

	pthread_mutex_lock(&philo->table->lock_eat);
	result_time = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->lock_eat);
	status = 0;
	if (result_time >= philo->table->tt_die)
		status = 1;
	return (status);
}

static int	observe_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].table->nb_philo)
	{
		if (timer_of_death(&philo[i]))
		{
			output_action(&philo[i], "died");
			pthread_mutex_lock(&philo->table->lock_death);
			philo->table->death_flag = 1;
			pthread_mutex_unlock(&philo->table->lock_death);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

static int	check_meal_counters(t_philo *philo)
{
	int	full;
	int	i;

	full = 0;
	i = 0;
	if (philo->table->n_meals == -1)
		return (0);
	while (i < philo[0].table->nb_philo)
	{
		pthread_mutex_lock(&philo->table->lock_eat);
		if (philo[i].meals_counter == philo[0].table->n_meals)
			full++;
		pthread_mutex_unlock(&philo[0].table->lock_eat);
		i++;
		usleep(100);
	}
	if (full == philo[0].table->nb_philo)
	{
		pthread_mutex_lock(&philo->table->lock_death);
		philo->table->death_flag = 1;
		pthread_mutex_unlock(&philo->table->lock_death);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_info	*table;

	table = (t_info *)arg;
	while (1)
		if (observe_death(table->philo) == 1
			|| check_meal_counters(table->philo) == 1)
			break ;
	return (arg);
}
