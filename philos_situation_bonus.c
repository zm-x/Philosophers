/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_situation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:32:59 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/22 15:40:04 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	thinking(t_data *philo)
{
	printf("%ld %d is thinking\n", get_time() - philo->curent_time, philo->place
		+ 1);
	if (philo->place % 2 != 0)
		usleep(500);
	usleep(500);
	return (1);
}

int	even(t_data *philo)
{
	if (!philo->stop_flag)
		sem_wait(philo->forks);
	usleep(100);
	if (!philo->stop_flag)
		sem_wait(philo->forks);
	return (1);
}

int	eating(t_data *philo)
{
	printf("%ld %d has taken a fork\n", get_time() - philo->curent_time,
		philo->place + 1);
	printf("%ld %d has taken a fork\n", get_time() - philo->curent_time,
		philo->place + 1);
	printf("%ld %d is eating\n", get_time() - philo->curent_time, philo->place
		+ 1);
	philo->ntimes--;
	return (1);
}

int	sleeping(t_data *philo)
{
	if (!philo->stop_flag)
		sem_wait(philo->eatt);
	philo->last_eat = get_time();
	if (!philo->stop_flag)
		sem_post(philo->eatt);
	usleep(philo->neat * 1000);
	if (!philo->stop_flag)
		sem_post(philo->forks);
	if (!philo->stop_flag)
		sem_post(philo->forks);
	if (philo->ntimes == 0)
		return (0);
	if (!philo->stop_flag)
		sem_wait(philo->print);
	printf("%ld %d is sleeping\n", get_time() - philo->curent_time, philo->place
		+ 1);
	if (!philo->stop_flag)
		sem_post(philo->print);
	return (1);
}
