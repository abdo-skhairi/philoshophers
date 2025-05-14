/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:35 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 12:00:21 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info	table;

	if (!philo_parsing(ac - 1, av, &table))
		return (1);
	if (!init_table(&table))
		return (1);
	if (!philo_start_dining(&table))
		return (1);
	ready_to_finish(&table);
	return (0);
}
