/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_situation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:32:59 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/12 22:58:36 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_data *philo)
{
	pthread_mutex_lock(philo->print);
	pthread_mutex_lock(philo->dead);
	if (*philo->is_dead)
	{
		pthread_mutex_unlock(philo->print);
		pthread_mutex_unlock(philo->dead);
		return (0);
	}
	pthread_mutex_unlock(philo->dead);
	printf("%ld %d is thinking\n", get_time() - philo->curent_time, philo->place
		+ 1);
	pthread_mutex_unlock(philo->print);
	if (philo->place % 2 != 0)
		usleep(500);
	usleep(500);
	return (1);
}

int	odd(t_data *philo)
{
	if (philo->place % 2 == 0)
	{
		pthread_mutex_lock(philo->dead);
		if (*philo->is_dead)
			return (pthread_mutex_unlock(philo->dead), -1);
		pthread_mutex_unlock(philo->dead);
		pthread_mutex_lock(&philo->forks[philo->right_fork]);
		usleep(500);
		philo->check_right = 1;
		pthread_mutex_lock(philo->dead);
		if (*philo->is_dead)
		{
			pthread_mutex_unlock(philo->dead);
			pthread_mutex_unlock(&philo->forks[philo->right_fork]);
			philo->check_right = 0;
			return (-1);
		}
		pthread_mutex_unlock(philo->dead);
		pthread_mutex_lock(&philo->forks[philo->left_fork]);
		philo->check_left = 1;
	}
	return (1);
}

int	even(t_data *philo)
{
	if (philo->place % 2)
	{
		pthread_mutex_lock(philo->dead);
		if (*philo->is_dead)
		{
			pthread_mutex_unlock(philo->dead);
			return (-1);
		}
		pthread_mutex_unlock(philo->dead);
		pthread_mutex_lock(&philo->forks[philo->left_fork]);
		usleep(500);
		philo->check_left = 1;
		pthread_mutex_lock(philo->dead);
		if (*philo->is_dead)
		{
			pthread_mutex_unlock(philo->dead);
			pthread_mutex_unlock(&philo->forks[philo->left_fork]);
			philo->check_left = 0;
			return (-1);
		}
		pthread_mutex_unlock(philo->dead);
		pthread_mutex_lock(&philo->forks[philo->right_fork]);
		philo->check_right = 1;
	}
	return (1);
}

int	eating(t_data *philo)
{
	pthread_mutex_lock(philo->print);
	pthread_mutex_lock(philo->dead);
	if (!break_while(philo))
		return (0);
	pthread_mutex_unlock(philo->dead);
	printf("%ld %d has taken a fork\n", get_time() - philo->curent_time,
		philo->place + 1);
	pthread_mutex_lock(philo->dead);
	if (!break_while(philo))
		return (0);
	pthread_mutex_unlock(philo->dead);
	printf("%ld %d has taken a fork\n", get_time() - philo->curent_time,
		philo->place + 1);
	pthread_mutex_lock(philo->dead);
	if (!break_while(philo))
		return (0);
	pthread_mutex_unlock(philo->dead);
	printf("%ld %d is eating\n", get_time() - philo->curent_time, philo->place
		+ 1);
	pthread_mutex_unlock(philo->print);
	return (1);
}

int	sleeping(t_data *philo)
{
	pthread_mutex_lock(philo->eatt);
	philo->ntimes--;
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->eatt);
	usleep(philo->neat * 1000);
	philo->check_right = 0;
	philo->check_left = 0;
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	pthread_mutex_lock(philo->print);
	if (philo->ntimes == 0)
	{
		pthread_mutex_unlock(philo->print);
		return (0);
	}
	pthread_mutex_lock(philo->dead);
	if (!break_while(philo))
		return (-1);
	pthread_mutex_unlock(philo->dead);
	printf("%ld %d is sleeping\n", get_time() - philo->curent_time, philo->place
		+ 1);
	pthread_mutex_unlock(philo->print);
	return (1);
}
