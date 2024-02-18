/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:37:44 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/18 20:13:50 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(address of philo)
return : TRUE */
int	drop_fork(t_ph *ph)
{
	pthread_mutex_lock(ph->auth[0]);
	ph->db->fork[ph->tag_no] = 0;
	pthread_mutex_unlock(ph->auth[0]);
	pthread_mutex_lock(ph->auth[1]);
	if (ph->tag_no != ph->db->philo_count - 1)
		ph->db->fork[ph->tag_no + 1] = 0;
	else
		ph->db->fork[0] = 0;
	pthread_mutex_unlock(ph->auth[1]);
	return (TRUE);
}
