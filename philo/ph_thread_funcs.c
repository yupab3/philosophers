/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:25:36 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/14 16:33:07 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(address of data - arg of astronut)
return : NONE(void)
Astronut who takes philosophers to space */
void	*astronut(void *data)
{
	t_ph	*ph;

	ph = (t_ph *)data;
	if (standby(ph) == FALSE)
	{
		free(ph);
		return (NULL);
	}
	while (1)
	{
		if (ph_think(ph) == FALSE)
			return (NULL);
		if (ph_take_own_fork(ph) == FALSE)
			return (NULL);
		if (ph_take_other_fork(ph) == FALSE)
			return (NULL);
		if (ph_eat_something(ph) == FALSE)
			return (NULL);
		if (ph_fall_in_sleep(ph) == FALSE)
			return (NULL);
	}
	return (NULL);
}

/* func(address of philo)
return : TRUE or FALSE */
int	chk_death(t_ph *ph)
{
	if (get_time_diff(ph->eat_time) > ph->db->life)
	{
		pthread_mutex_lock(ph->db->kill);
		if (ph->db->death == 0)
			ph_print_die("%lld %d died\n", ph);
		ph->db->death = 1;
		pthread_mutex_unlock(ph->db->kill);
	}
	pthread_mutex_lock(ph->db->kill);
	if (ph->db->death != 0)
	{
		pthread_mutex_unlock(ph->db->kill);
		return (FALSE);
	}
	pthread_mutex_unlock(ph->db->kill);
	return (TRUE);
}

/* func(address of philo)
return : TRUE or FALSE */
int	chk_death_unlock_own(t_ph *ph)
{
	if (get_time_diff(ph->eat_time) > ph->db->life)
	{
		pthread_mutex_lock(ph->db->kill);
		if (ph->db->death == 0)
			ph_print_die("%lld %d died\n", ph);
		ph->db->death = 1;
		pthread_mutex_unlock(ph->db->kill);
	}
	pthread_mutex_lock(ph->db->kill);
	if (ph->db->death != 0)
	{
		pthread_mutex_unlock(ph->db->kill);
		pthread_mutex_unlock(ph->auth[0]);
		return (FALSE);
	}
	pthread_mutex_unlock(ph->db->kill);
	return (TRUE);
}
