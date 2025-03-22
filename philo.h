/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:24:53 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/11 19:38:53 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philos
{
	int				nphilo;
	int				ndie;
	int				neat;
	int				nsleep;
	int				ntimes;
	long			curent_time;
	long			last_eat;
	int				place;
	int				left_fork;
	int				right_fork;
	int				av;
	int				*is_dead;
	int				check_left;
	int				check_right;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sleep;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eatt;
	pthread_mutex_t	think;
	pthread_mutex_t	eat;
	int				i;
}					t_data;

typedef struct utilis
{
	int				i;
	pthread_t		thread[200];
	pthread_t		lm9dm;
	pthread_mutex_t	forks[200];
	t_data			philo[200];
	pthread_mutex_t	print;
	pthread_mutex_t	eatt;
	pthread_mutex_t	dead;
	long			start;
	int				error;
	int				is_dead;
}					t_utilis;

size_t				ft_strlen(char *s);
int					error_func(int ac);
int					ft_atoi(char *nptr, t_utilis *useful);
long				get_time(void);
long				*bring_time(t_data *philo);
int					sleeping(t_data *philo);
int					eating(t_data *philo);
int					even(t_data *philo);
int					odd(t_data *philo);
void				do_it(t_data *philo);
int					thinking(t_data *philo);
void				*all(void *p);
void				one_philo(int curent);
void				give_fork_place(t_data *philo);
int					break_while(t_data *philo);
void				*check_death(void *p);
#endif
