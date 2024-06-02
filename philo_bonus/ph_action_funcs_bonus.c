/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action_funcs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:56:54 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/06/02 16:40:03 by dongyeuk         ###   ########.fr       */
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
	if (ph->chk_time != 0 && ph->chk_first)
		ph_sleep(ph, ph->chk_time);
	else
		ph->chk_first = 1;
	sem_wait(ph->auth);
	ph_print_str("%lld %d has taken a fork\n", ph);
	if (ph->db->philo_count == 1)
	{
		sem_post(ph->auth);
		ph_sleep(ph, ph->db->life);
	}
	chk_death(ph);
	sem_wait(ph->auth);
	ph_print_str("%lld %d has taken a fork\n", ph);
	return (TRUE);
}

/* func(address of philo)
return : TRUE or FALSE */
int	ph_eat_something(t_ph *ph)
{
	chk_death(ph);
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
