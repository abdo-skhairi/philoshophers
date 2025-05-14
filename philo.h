/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:36:31 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:42:14 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_MAX "You Have Exceeded the limit of philosophers\n"
# define ERR_ARG "Number of args is not Correct\n"
# define ERR_NBR "Number is not Correct\n"
# define ERR_MEM "Allocation Faield\n"
# define ERR_PTH "Probleme Creating Thread\n"
# define ERR_MTX "Mutex Problem\n"
# define ERR_DST "Probleme Destroying The Mutex\n"
# define ERR_TIM "Clock Probleme\n"
# define ERR_WTH "Threading Probleme\n"

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef long long		t_long;

int		philo_parsing(int narg, char **args, t_info *info);
void	clear_leaks(int ***leaks);

void	destroy_mutex(pthread_mutex_t *mtx, int max);
void	unlock_mutex(t_info *info);
int		crash(char *msg, t_info *info);
void	ready_to_finish(t_info *info);

int		init_table(t_info *info);

int		philo_start_dining(t_info *info);
int		is_alive(t_philo *philo, bool condition);

t_long	get_time(void);
void	ft_usleep(t_long time, t_info *info);

void	output_action(t_philo *philo, char *msg);

void	*monitor(void *arg);

void	sleeping(t_philo *philo);
void	think(t_philo *philo);
int		eat(t_philo *philo);

typedef struct s_info
{
	int				nb_philo;
	int				n_meals;
	bool			death_flag;
	t_long			tt_eat;
	t_long			tt_die;
	t_long			tt_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_eat;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor_thread;
	t_philo			*philo;
}	t_info;

typedef struct s_philo
{
	int			pos;
	int			fork[2];
	int			meals_counter;
	t_long		start_time;
	t_long		last_meal_time;
	t_info		*table;
	pthread_t	thread;
}	t_philo;

#endif
