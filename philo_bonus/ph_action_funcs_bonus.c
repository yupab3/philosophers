/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action_funcs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:56:54 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/11 15:42:27 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(address of philo)
return : TRUE or FALSE */
int	ph_think(t_ph *ph)
{
	chk_death(ph);
	ph_print_str("%lld %d is thinking\n", ph);
	return (TRUE);
}

/* func(address of philo)
return : TRUE or FALSE */
int	ph_take_fork(t_ph *ph)
{
	while (chk_death(ph) == TRUE)
	{
		sem_wait(ph->auth);
		ph_print_str("%lld %d has taken a fork\n", ph);
		if (ph->db->philo_count == 1)
		{
			sem_post(ph->auth[0]);
			ph_sleep(ph, ph->db->life);
		}
		sem_wait(ph->auth);
		ph_print_str("%lld %d has taken a fork\n", ph);
	}
	return (TRUE);
}

/* func(address of philo)
return : TRUE or FALSE */
int	ph_take_other_fork(t_ph *ph)
{
	while (chk_death(ph) == TRUE)
	{
		pthread_mutex_lock(ph->auth[1]);
		if ((ph->tag_no == ph->db->philo_count - 1 && ph->db->fork[0] == 0)
			|| (ph->tag_no != ph->db->philo_count - 1
				&& ph->db->fork[ph->tag_no + 1] == 0))
		{
			if (ph->tag_no == ph->db->philo_count - 1)
				ph->db->fork[0] = 1;
			else
				ph->db->fork[ph->tag_no + 1] = 1;
			pthread_mutex_unlock(ph->auth[1]);
			ph_print_str("%lld %d has taken a fork\n", ph);
			return (TRUE);
		}
		pthread_mutex_unlock(ph->auth[1]);
	}
	pthread_mutex_unlock(ph->auth[0]);
	free(ph);
	return (FALSE);
}

/* func(address of philo)
return : TRUE or FALSE */
int	ph_eat_something(t_ph *ph)
{
	ph->eat_time = get_time();
	ph_print_str("%lld %d is eating\n", ph);
	if (ph_sleep_eat(ph, ph->db->eat) == FALSE)
	{
		free(ph);
		return (FALSE);
	}
	return (drop_fork(ph));
}

/* func(address of philo)
return : TRUE or FALSE */
int	ph_fall_in_sleep(t_ph *ph)
{
	ph_print_str("%lld %d is sleeping\n", ph);
	if (ph_sleep(ph, ph->db->sleep) == FALSE)
	{
		free(ph);
		return (FALSE);
	}
	return (TRUE);
}