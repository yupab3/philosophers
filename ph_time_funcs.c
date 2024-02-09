/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:46:00 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/08 17:40:27 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(void)
return : (long long)current time(miliseconds) */
long long	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_usec / 1000);
}

/* func(time to compare)
return : (long long)result of comparison(miliseconds) */
long long	get_time_diff(long long runtime)
{
	struct timeval	start;
	long long		result;

	gettimeofday(&start, NULL);
	result = start.tv_sec * 1000 + start.tv_usec / 1000 - runtime;
	return (result);
}

/* func(address of philo, miliseconds to sleep)
return : NONE(void) */
int	ph_sleep(t_ph *ph, long long milisec)
{
	long long	set_time;

	set_time = get_time();
	if (milisec * 0.8 < ph->db->life - get_time_diff(ph->eat_time))
		usleep(milisec * 800);
	while (get_time_diff(set_time) < milisec)
	{
		usleep(100);
		if (chk_death(ph) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

/* func(miliseconds to sleep)
return : NONE(void) */
int	ph_sleep_eat(t_ph *ph, long long milisec)
{
	if (milisec * 0.8 < ph->db->life)
		usleep(milisec * 800);
	while (get_time_diff(ph->eat_time) < milisec)
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
