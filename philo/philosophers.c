/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:11:12 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/10 17:50:16 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	*auth;
	pthread_t		*tid;
	t_data			*db;

	if (chk_arguments(argc) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - wrong arguments", 2));
	db = init_data(argc, argv);
	tid = init_tid(db);
	auth = init_mutex(db);
	if ((tid == NULL || db == NULL || auth == NULL)
		&& free_undef_error(tid, db, auth))
		return (_rt_failure_with_msg_nl_fd("main - init failed", 2));
	pthread_mutex_lock(db->ready);
	if (create_thread(auth, tid, db) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - create failed", 2));
	pthread_mutex_unlock(db->ready);
	if (join_thread(tid, db) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - join failed", 2));
	if (destroy_mutex(auth, db) == FALSE)
		return (_rt_failure_with_msg_nl_fd("main - destroy failed", 2));
	return (0);
}
