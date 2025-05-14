/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:14 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:00:31 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	output_action(philo, "is sleeping");
	ft_usleep(philo->table->tt_sleep, philo->table);
}

void	think(t_philo *philo)
{
	output_action(philo, "is thinking");
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork[1]]);
	output_action(philo, "has taken a fork");
	if (philo->table->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->table->forks[0]);
		ft_usleep(philo->table->tt_die, philo->table);
		return (0);
	}
	pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
	output_action(philo, "has taken a fork");
	output_action(philo, "is eating");
	pthread_mutex_lock(&philo->table->lock_eat);
	philo->last_meal_time = get_time();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->lock_eat);
	ft_usleep(philo->table->tt_eat, philo->table);
	pthread_mutex_unlock(&philo->table->forks[philo->fork[0]]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork[1]]);
	return (1);
}
