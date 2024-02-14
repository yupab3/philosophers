/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_funcs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:25:36 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/13 16:11:57 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(address of data - arg of astronut)
return : NONE(void)
Astronut who takes philosophers to space */
void	*astronut(t_ph *ph)
{
	if (standby(ph) == FALSE)
	{
		free(ph);
		exit(0);
	}
	while (1)
	{
		if (ph_think(ph) == FALSE)
			exit(0);
		if (ph_take_fork(ph) == FALSE)
			exit(0);
		// if (ph_take_other_fork(ph) == FALSE)
		// 	return (NULL);
		if (ph_eat_something(ph) == FALSE)
			exit(0);
		if (ph_fall_in_sleep(ph) == FALSE)
			exit(0);
	}
	exit(0);
}

/* func(address of philo)
return : TRUE
exit case : died(1) */
int	chk_death(t_ph *ph)
{
	int	idx;

	idx = 0;
	if (get_time_diff(ph->eat_time) > ph->db->life)
	{
		ph_print_die("%lld %d died\n", ph);
		while (idx < ph->db->philo_count)
		{
			sem_post(ph->db->starving);
			idx++;
		}
		exit(1);
	}
	return (TRUE);
}
