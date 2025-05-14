/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:46 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:39:00 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_mutex(t_info *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_unlock(&table->forks[i]);
	pthread_mutex_unlock(&table->lock_death);
	pthread_mutex_unlock(&table->lock_eat);
	pthread_mutex_unlock(&table->print_mutex);
}

void	destroy_mutex(pthread_mutex_t *mtx, int max)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		if (pthread_mutex_destroy(&mtx[i]))
		{
			printf(ERR_DST);
			return ;
		}
	}
}

void	clear_leaks(int ***leaks)
{
	int	i;

	if (!leaks || !(*leaks))
		return ;
	i = -1;
	while ((*leaks)[++i])
		free((*leaks)[i]);
	free(*leaks);
	*leaks = NULL;
}

void	ready_to_finish(t_info *table)
{
	int	i;

	i = 0;
	unlock_mutex(table);
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->lock_eat);
	pthread_mutex_destroy(&table->lock_death);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philo);
}

int	crash(char *msg, t_info *table)
{
	if (msg)
		printf("%s\n", msg);
	if (table)
		destroy_mutex(table->forks, table->nb_philo);
	return (0);
}
