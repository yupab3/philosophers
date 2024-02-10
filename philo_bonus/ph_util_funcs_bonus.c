/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_funcs_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:30:31 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/10 19:36:42 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(address of pthread_t, address of t_data)
return : TRUE */
int	free_undef_error(int *pid_null_able, t_data *db_null_able,
					sem_t *auth_null_able)
{
	int	idx;

	if (auth_null_able != SEM_FAILED)
	{
		if (sem_close(auth_null_able) == -1)
			write(2, "sem_close failed\n", 17);
		sem_unlink("ph_fork");
	}
	close_unlink_all_db_sem(db_null_able);
	free(pid_null_able);
	free(db_null_able);
	return (TRUE);
}

/* func(argc of main func)
return : TRUE or FALSE */
int	chk_arguments(int argc)
{
	if (argc != 5 && argc != 6)
		return (_rt_false_with_msg_nl_fd(
				"func. chk_arguments - invalid argc", 2));
	return (TRUE);
}

void	close_unlink_all_db_sem(t_data *db_null_able)
{
	if (db_null_able->starving != SEM_FAILED)
		if (sem_close(db_null_able->starving) != SEM_FAILED)
			write(2, "sem_close failed\n", 17);
	if (db_null_able->ready != SEM_FAILED)
		if (sem_close(db_null_able->ready) != SEM_FAILED)
			write(2, "sem_close failed\n", 17);
	if (db_null_able->print != SEM_FAILED)
		if (sem_close(db_null_able->print) != SEM_FAILED)
			write(2, "sem_close failed\n", 17);
	sem_unlink("ph_starving");
	sem_unlink("ph_print");
	sem_unlink("ph_ready");
}
