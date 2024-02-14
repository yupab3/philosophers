/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex_funcs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:27:24 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/14 14:51:25 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(auth, db)
return : TRUE */
int	destroy_sem(sem_t *auth, t_data *db, int *pid)
{
	int	err_flag;
	int	idx;

	idx = 0;
	err_flag = TRUE;
	sem_unlink("ph_fork");
	if (auth != SEM_FAILED)
		if (sem_close(auth) != -1)
			write(2, "sem_close failed\n", 17);
	close_unlink_all_db_sem(db);
	free(pid);
	return (err_flag);
}
