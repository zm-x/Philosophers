/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:39 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/22 12:24:03 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_it(t_data *philo)
{
	pthread_mutex_lock(philo[philo->i - 1].print);
	if (philo->ntimes != 0)
		printf("%ld %d died\n", get_time() - philo[philo->i - 1].curent_time,
			philo[philo->i - 1].place + 1);
	pthread_mutex_unlock(philo[philo->i - 1].print);
	pthread_mutex_lock(philo[philo->i - 1].dead);
	*philo[philo->i - 1].is_dead = 1;
	pthread_mutex_unlock(philo[philo->i - 1].dead);
	pthread_mutex_unlock(philo[philo->i - 1].eatt);
}

int	give_value(t_data *philo, char **av, int ac, t_utilis *useful)
{
	philo->nphilo = ft_atoi(av[1], useful);
	philo->ndie = ft_atoi(av[2], useful);
	philo->neat = ft_atoi(av[3], useful);
	philo->nsleep = ft_atoi(av[4], useful);
	philo->ntimes = -1;
	if (ac == 6)
	{
		philo->ntimes = ft_atoi(av[5], useful);
		if (useful->philo[0].ntimes <= 0)
			return (0);
	}
	philo->eatt = &useful->eatt;
	philo->dead = &useful->dead;
	philo->is_dead = &useful->is_dead;
	philo->check_left = 0;
	philo->check_right = 0;
	philo->curent_time = useful->start;
	philo->forks = useful->forks;
	philo->print = &useful->print;
	philo->last_eat = get_time();
	philo->av = ft_atoi(av[2], useful);
	philo->place = useful->i;
	return (1);
}

int	init(t_utilis *useful, char **av, int ac)
{
	if (ft_atoi(av[1], useful) == 1)
		return (one_philo(ft_atoi(av[2], useful)), 0);
	if (ft_atoi(av[1], useful) > 200)
		return (0);
	while (useful->i < ft_atoi(av[1], useful))
		pthread_mutex_init(&useful->forks[useful->i++], NULL);
	pthread_mutex_init(&useful->dead, NULL);
	pthread_mutex_init(&useful->eatt, NULL);
	useful->i = 0;
	while (useful->i < ft_atoi(av[1], useful))
	{
		if (!give_value(&useful->philo[useful->i], av, ac, useful))
			return (0);
		useful->i++;
	}
	if (useful->error || ft_atoi(av[1], useful) <= 0)
		return (printf("wrong arguments\n"), 0);
	useful->i = 0;
	return (1);
}

int	main(int ac, char **av)
{
	t_utilis	useful;

	useful.error = 0;
	useful.i = 0;
	if (!error_func(ac))
		return (1);
	useful.start = get_time();
	pthread_mutex_init(&useful.print, NULL);
	useful.is_dead = 0;
	if (!init(&useful, av, ac))
		return (1);
	while (useful.i++ < useful.philo[0].nphilo)
		if (pthread_create(&useful.thread[useful.i - 1], NULL, all,
				&useful.philo[useful.i - 1]) != 0)
			return (printf("thread failed\n"), 1);
	if (pthread_create(&useful.lm9dm, NULL, check_death, useful.philo) != 0)
		return (printf("thread failed\n"), 1);
	useful.i = 0;
	pthread_join(useful.lm9dm, NULL);
	while (useful.i < useful.philo[0].nphilo)
	{
		pthread_join(useful.thread[useful.i], NULL);
		useful.i++;
	}
	return (0);
}
