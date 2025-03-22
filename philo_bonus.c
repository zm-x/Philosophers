/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:39 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/22 16:27:07 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_useful(t_data *philo, t_utilis *useful)
{
	philo->eatt = useful->eatt;
	philo->dead = useful->dead;
	philo->curent_time = useful->start;
	philo->forks = useful->forks;
	philo->print = useful->print;
	philo->etimes = useful->etime;
}

int	give_value(t_data *philo, char **av, int ac, t_utilis *useful)
{
	int	i;

	i = 1;
	philo->nphilo = ft_atoi(av[i++], useful);
	philo->ndie = ft_atoi(av[i++], useful);
	philo->neat = ft_atoi(av[i++], useful);
	philo->nsleep = ft_atoi(av[i++], useful);
	philo->ntimes = -1;
	if (ac == 6)
	{
		philo->ntimes = ft_atoi(av[i++], useful);
		if (useful->philo[0].ntimes <= 0)
			return (0);
	}
	philo_useful(philo, useful);
	pthread_mutex_init(&philo->flag, NULL);
	philo->last_eat = get_time();
	philo->av = ft_atoi(av[2], useful);
	philo->place = useful->i;
	philo->stop_flag = 0;
	philo->dead_print = useful->dead_print;
	philo->has_finish = &useful->has_finish;
	return (1);
}

int	init(t_utilis *useful, char **av, int ac)
{
	sem_t	*sem;

	if (ft_atoi(av[1], useful) == 1)
		return (one_philo(ft_atoi(av[2], useful)), 0);
	if (ft_atoi(av[1], useful) <= 0 || ft_atoi(av[1], useful) > 200)
		return (printf("wrong arguments\n"), 0);
	useful->forks = sem_open("/fork", O_CREAT, 644, ft_atoi(av[1], useful));
	useful->dead = sem_open("/dead", O_CREAT, 644, 1);
	useful->eatt = sem_open("/eatt", O_CREAT, 644, 1);
	useful->etime = sem_open("/etimes", O_CREAT, 644, 0);
	useful->i = 0;
	useful->has_finish = 0;
	sem = sem_open("/is_dead", O_CREAT, 644, 0);
	check_open(useful, sem);
	while (useful->i < ft_atoi(av[1], useful))
	{
		useful->philo[useful->i].is_dead = sem;
		if (!give_value(&useful->philo[useful->i], av, ac, useful))
			return (close_all(useful), 0);
		useful->i++;
	}
	if (useful->error)
		return (printf("wrong arguments\n"), close_all(useful), 0);
	useful->i = 0;
	return (1);
}

void	*check_etimes(void *p)
{
	t_data	*philo;
	int		i;

	philo = (t_data *)p;
	i = 0;
	while (i++ < philo->nphilo)
		sem_wait(philo->etimes);
	*philo->has_finish = 1;
	sem_post(philo->is_dead);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_utilis	useful;
	int			pids[200];

	useful.error = 0;
	useful.i = 0;
	if (!error_func(ac))
		return (1);
	unlink_all();
	useful.print = sem_open("/print", O_CREAT, 644, 1);
	useful.dead_print = sem_open("/d_print", O_CREAT, 644, 1);
	useful.start = get_time();
	if (!init(&useful, av, ac))
		return (1);
	while (useful.i++ < useful.philo[0].nphilo)
	{
		useful.pid = fork();
		pids[useful.i - 1] = useful.pid;
		if (useful.pid == 0)
			all_bonus(&useful.philo[useful.i - 1]);
	}
	pthread_create(&useful.lm9dm, NULL, check_etimes, &useful.philo[0]);
	check_death(&useful.philo[0], pids);
	pthread_join(useful.lm9dm, NULL);
	unlink_all();
	close_all(&useful);
}
