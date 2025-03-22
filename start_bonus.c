/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:36:26 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/22 16:29:38 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(void *p, int pids[])
{
	t_data	*philo;
	int		i;

	philo = (t_data *)p;
	sem_wait(philo->is_dead);
	if (!*philo->has_finish)
	{
		i = 0;
		while (i++ < philo->nphilo)
			sem_post(philo->etimes);
		i = 0;
		while (i++ < philo->nphilo)
			kill(pids[i - 1], 9);
	}
	unlink_all();
}

void	give_fork_place(t_data *philo)
{
	philo->left_fork = philo->place % philo->nphilo;
	philo->right_fork = (philo->left_fork + 1) % philo->nphilo;
	philo->last_eat = get_time();
}

void	*death(void *philoo)
{
	t_data	*philo;

	philo = (t_data *)philoo;
	while (1)
	{
		if (get_time() - philo->last_eat >= philo->ndie)
		{
			sem_wait(philo->dead_print);
			printf("%ld %d died\n", get_time() - philo->curent_time + 1,
				philo->place + 1);
			pthread_mutex_lock(&philo->flag);
			philo->stop_flag = 1;
			pthread_mutex_unlock(&philo->flag);
			sem_post(philo->is_dead);
			close_all_p(philo);
			return (NULL);
		}
		else if (philo->ntimes == 0)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

void	*all_bonus(void *p)
{
	t_data	*philo;

	philo = (t_data *)p;
	give_fork_place(philo);
	pthread_create(&philo->lm9dm, NULL, death, philo);
	while (1)
	{
		thinking(philo);
		even(philo);
		eating(philo);
		if (!sleeping(philo))
		{
			sem_post(philo->etimes);
			close_all_p(philo);
			pthread_join(philo->lm9dm, NULL);
			exit(0);
		}
		usleep(philo->nsleep * 1000);
	}
	return (NULL);
}

void	one_philo(int curent)
{
	printf("0 1 is thinking\n");
	usleep(curent * 1000);
	printf("%d 1 died\n", curent + 1);
}
