/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:11:12 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/14 14:16:14 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	sem_t		*auth;
	int			*pid;
	t_data		*db;

	if (chk_arguments(argc) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - wrong arguments", 2));
	db = init_data(argc, argv);
	pid = init_pid(db);
	auth = sem_open("ph_fork", O_CREAT | O_RDWR, 0644, db->philo_count);
	if ((pid == NULL || db == NULL || auth == SEM_FAILED)
		&& free_undef_error(pid, db, auth))
		return (_rt_failure_with_msg_nl_fd("main - init failed", 2));
	sem_wait(db->ready);
	if (create_child(auth, pid, db) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - create failed", 2));
	sem_post(db->ready);
	if (kill_process(pid, db) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - join failed", 2));
	if (destroy_sem(auth, db, pid) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - destroy failed", 2));
	return (0);
}
