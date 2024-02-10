/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:37:44 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/10 18:59:34 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(address of philo)
return : TRUE */
int	drop_fork(t_ph *ph)
{
	sem_post(ph->auth);
	sem_post(ph->auth);
	return (TRUE);
}
