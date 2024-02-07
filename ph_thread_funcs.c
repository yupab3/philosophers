/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:25:36 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/07 14:51:24 by dongyeuk         ###   ########.fr       */
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
		if (chk_death(ph) == FALSE)
		{
			free(ph);
			return (NULL);
		}
		ph_print_str("%lld %d is thinking\n", ph);
		pthread_mutex_lock(ph->auth[0]);
		if (chk_death(ph) == FALSE)
		{
			pthread_mutex_unlock(ph->auth[0]);
			free(ph);
			return (NULL);
		}
		ph->fork[0] = 1;
		ph_print_str("%lld %d has taken a fork\n", ph);
		pthread_mutex_lock(ph->auth[1]);
		if (chk_death(ph) == FALSE)
		{
			pthread_mutex_unlock(ph->auth[0]);
			pthread_mutex_unlock(ph->auth[1]);
			free(ph);
			return (NULL);
		}
		ph->fork[1] = 1;
		ph_print_str("%lld %d has taken a fork\n", ph);
		if (ph->fork[0] == 1 && ph->fork[1] == 1)
		{
			ph->eat_time = get_time();
			ph_print_str("%lld %d is eating\n", ph);
			if (ph_sleep(ph, ph->db->eat) == FALSE)
			{
				pthread_mutex_unlock(ph->auth[0]);
				pthread_mutex_unlock(ph->auth[1]);
				free(ph);
				return (NULL);
			}
			ph->fork[0] = 0;
			ph->fork[1] = 0;
		}
		pthread_mutex_unlock(ph->auth[0]);
		pthread_mutex_unlock(ph->auth[1]);
		ph_print_str("%lld %d is sleeping\n", ph);
		if (ph_sleep(ph, ph->db->sleep) == FALSE)
		{
			free(ph);
			return (NULL);
		}
	}
	return (NULL);
}

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
