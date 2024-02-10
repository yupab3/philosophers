/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex_funcs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:27:24 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/09 12:50:12 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(auth, db)
return : TRUE */
int	destroy_mutex(pthread_mutex_t *auth, t_data *db)
{
	int	err_flag;
	int	idx;

	idx = 0;
	err_flag = TRUE;
	while (idx < db->philo_count)
	{
		if (pthread_mutex_destroy(&(auth[idx])) != SUCCESS)
		{
			write(2, "pthread_destroy failed at mutex array. auth idx : ", 50);
			ph_putnbr_fd(idx, 2);
			write(2, "\n", 1);
			err_flag = FALSE;
		}
		idx++;
	}
	return (err_flag);
}
