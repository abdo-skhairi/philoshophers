/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:11:28 by abdo              #+#    #+#             */
/*   Updated: 2025/05/14 12:28:33 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf(ERR_TIM), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_long time_to_sleep, t_info *table)
{
	t_long	start;
	t_long	now;

	start = get_time();
	while (!is_alive(table->philo, 0))
	{
		now = get_time();
		if (now - start >= time_to_sleep)
			return ;
		usleep(400);
	}
}
