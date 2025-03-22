/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:27:15 by zael-mou          #+#    #+#             */
/*   Updated: 2025/03/22 16:26:22 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_open(t_utilis *useful, sem_t *sem)
{
	if (useful->forks == SEM_FAILED || useful->dead == SEM_FAILED)
	{
		printf ("sem_open failed\n");
		exit (1);
	}
	if (useful->eatt == SEM_FAILED || useful->etime == SEM_FAILED)
	{
		printf ("sem_open failed\n");
		exit (1);
	}
	if (sem == SEM_FAILED || useful->print == SEM_FAILED)
	{
		printf ("sem_open failed\n");
		exit (1);
	}
}

void	unlink_all(void)
{
	sem_unlink("/fork");
	sem_unlink("/dead");
	sem_unlink("/is_dead");
	sem_unlink("/print");
	sem_unlink("/eatt");
	sem_unlink("/etimes");
	sem_unlink("/d_print");
}

void	close_all_p(t_data *useful)
{
	sem_close(useful->forks);
	sem_close(useful->dead);
	sem_close(useful->is_dead);
	sem_close(useful->print);
	sem_close(useful->eatt);
	sem_close(useful->etimes);
	sem_close(useful->dead_print);
}

void	close_all(t_utilis *useful)
{
	sem_close(useful->forks);
	sem_close(useful->dead);
	sem_close(useful->dead_print);
	sem_close(useful->philo[0].is_dead);
	sem_close(useful->print);
	sem_close(useful->eatt);
	sem_close(useful->etime);
}
