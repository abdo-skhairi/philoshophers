/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:25 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:38:57 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output_action(t_philo *philo, char *msg)
{
	t_long	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	time = get_time() - philo->start_time;
	if (!is_alive(philo, 0))
		printf("%lld %d %s\n", time, philo->pos, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
