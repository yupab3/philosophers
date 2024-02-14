/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:46:00 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/13 17:33:16 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(void)
return : (long long)current time(microseconds) */
long long	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000000 + start.tv_usec);
}

/* func(time to compare)
return : (long long)result of comparison(microseconds) */
long long	get_time_diff(long long runtime)
{
	struct timeval	start;
	long long		result;

	gettimeofday(&start, NULL);
	result = start.tv_sec * 1000000 + start.tv_usec - runtime;
	return (result);
}

/* func(address of philo, microseconds to sleep)
return : NONE(void) */
int	ph_sleep(t_ph *ph, long long microsec)
{
	long long	set_time;

	set_time = get_time();
	if (microsec * 0.8 < ph->db->life - get_time_diff(ph->eat_time))
		usleep(microsec * 0.8);
	while (get_time_diff(set_time) < microsec)
	{
		usleep(100);
		if (chk_death(ph) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

/* func(microseconds to sleep)
return : NONE(void) */
int	ph_sleep_eat(t_ph *ph, long long microsec)
{
	if (microsec * 0.8 < ph->db->life - get_time_diff(ph->eat_time))
		usleep(microsec * 0.8);
	while (get_time_diff(ph->eat_time) < microsec)
	{
		usleep(100);
		if (chk_death(ph) == FALSE)
			return (FALSE);
	}
	if (ph->db->infinity == 0)
	{
		if (--(ph->meals) == 0)
		{
			pthread_mutex_lock(ph->db->starving);
			if (--(ph->db->starver) == 0)
			{
				pthread_mutex_lock(ph->db->kill);
				ph->db->death = 1;
				pthread_mutex_unlock(ph->db->kill);
			}
			pthread_mutex_unlock(ph->db->starving);
		}
	}
	return (TRUE);
}
