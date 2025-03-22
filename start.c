/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:36:26 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/18 20:40:18 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *p)
{
	t_data	*philo;
	long	*eat_die;

	philo = (t_data *)p;
	while (1)
	{
		philo->i = 0;
		while (philo->i++ < philo[0].nphilo)
		{
			eat_die = bring_time(&philo[philo->i - 1]);
			pthread_mutex_lock(philo[philo->i - 1].eatt);
			if (get_time() - eat_die[0] > eat_die[1])
			{
				do_it(philo);
				free(eat_die);
				return (NULL);
			}
			pthread_mutex_unlock(philo[philo->i - 1].eatt);
			free(eat_die);
		}
	}
	return (NULL);
}

int	break_while(t_data *philo)
{
	if (*philo->is_dead)
	{
		pthread_mutex_unlock(philo->dead);
		pthread_mutex_unlock(philo->print);
		return (0);
	}
	return (1);
}

void	give_fork_place(t_data *philo)
{
	philo->left_fork = philo->place % philo->nphilo;
	philo->right_fork = (philo->left_fork + 1) % philo->nphilo;
	pthread_mutex_lock(philo->eatt);
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->eatt);
}

void	*all(void *p)
{
	t_data	*philo;

	philo = (t_data *)p;
	give_fork_place(philo);
	while (1)
	{
		if (!thinking(philo))
			break ;
		if (!odd(philo))
			break ;
		if (!even(philo))
			break ;
		if (!eating(philo))
			break ;
		if (!sleeping(philo))
			break ;
		usleep(philo->nsleep * 1000);
	}
	if (philo->check_left)
		pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	if (philo->check_right)
		pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	return (NULL);
}

void	one_philo(int curent)
{
	printf("0 1 is thinking\n");
	usleep(curent * 1000);
	printf("%d 1 died\n", curent + 1);
}
