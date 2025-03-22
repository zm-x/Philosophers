/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:28:30 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/22 12:48:57 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	error_func(int ac)
{
	if (ac < 5 || ac > 6)
		return (printf("wrong arguments\n"), 0);
	return (1);
}

int	ft_atoi(char *nptr, t_utilis *useful)
{
	int	i;
	int	r;
	int	sign;

	i = 0;
	r = 0;
	sign = 1;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return ((useful->error = 1), 0);
		r = r * 10 + nptr[i] - '0';
		i++;
	}
	if (r * sign <= 0)
		return ((useful->error = 1), 0);
	return (r * sign);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	*bring_time(t_data *philo)
{
	long	*eat_die;

	eat_die = malloc(sizeof(long) * 2);
	pthread_mutex_lock(philo->eatt);
	eat_die[0] = philo->last_eat;
	pthread_mutex_unlock(philo->eatt);
	pthread_mutex_lock(philo->dead);
	eat_die[1] = philo->ndie;
	pthread_mutex_unlock(philo->dead);
	return (eat_die);
}
