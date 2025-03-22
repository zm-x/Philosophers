/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:24:53 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/22 15:55:48 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
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
	pthread_mutex_t	flag;
	int				left_fork;
	int				right_fork;
	int				av;
	sem_t			*is_dead;
	int				stop_flag;
	int				check_left;
	int				check_right;
	int				*has_finish;
	sem_t			*forks;
	sem_t			*dead_print;
	sem_t			*print;
	sem_t			*dead;
	sem_t			*eatt;
	sem_t			*etimes;
	pthread_t		lm9dm;
}					t_data;

typedef struct utilis
{
	int				i;
	sem_t			*forks;
	t_data			philo[200];
	sem_t			*print;
	sem_t			*eatt;
	sem_t			*dead_print;
	sem_t			*dead;
	sem_t			*etime;
	int				has_finish;
	long			start;
	int				error;
	pid_t			pid;
	pthread_t		lm9dm;
}					t_utilis;

size_t				ft_strlen(char *s);
int					error_func(int ac);
int					ft_atoi(char *nptr, t_utilis *useful);
long				get_time(void);
void				one_philo(int curent);
int					sleeping(t_data *philo);
int					eating(t_data *philo);
int					even(t_data *philo);
int					odd(t_data *philo);
void				check_open(t_utilis *useful, sem_t *sem);
int					thinking(t_data *philo);
void				unlink_all(void);
void				*all_bonus(void *p);
void				*death(void *philoo);
void				close_all(t_utilis *useful);
void				give_fork_place(t_data *philo);
void				close_all_p(t_data *useful);
int					break_while(t_data *philo);
void				check_death(void *p, int pids[]);
#endif
