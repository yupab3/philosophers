/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:55:55 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/14 13:52:09 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(address of each thread's philo)
return : NONE(void) */
int	standby(t_ph *ph)
{
	int	a;
	int	delay;

	a = ph->db->philo_count % 2;
	delay = ph->db->eat;
	if (delay == 0)
		delay = ph->db->life;
	pthread_mutex_lock(ph->db->ready);
	pthread_mutex_unlock(ph->db->ready);
	ph->eat_time = get_time();
	if (a == 1 && ph->tag_no == 0)
	{
		if (ph_sleep(ph, delay) == FALSE)
			return (FALSE);
	}
	else if (ph->tag_no % 2 == 1)
	{
		if (ph_sleep(ph, delay / 2) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

/* func(auth, tid, db)
return : TRUE or FALSE */
int	create_thread(pthread_mutex_t *auth, pthread_t *tid, t_data *db)
{
	t_ph			*philo;
	int				idx;

	idx = 0;
	db->life *= 1000;
	db->eat *= 1000;
	db->sleep *= 1000;
	while (idx < db->philo_count)
	{
		philo = init_philo(auth, db, idx);
		if (philo == NULL && free_undef_error(tid, db, auth))
			return (FALSE);
		if (pthread_create(&tid[idx], NULL, astronut, (void *)philo) < 0)
			break ;
		idx++;
	}
	if (idx != db->philo_count)
	{
		join_thread(tid, db);
		return (_rt_false_with_msg_nl_fd(
				"func. create_thread - pthread create error", 2));
	}
	db->init_time = get_time();
	return (TRUE);
}

/* func(tid, db)
return : TRUE */
int	join_thread(pthread_t *tid, t_data *db)
{
	int	err_flag;
	int	idx;

	idx = 0;
	err_flag = TRUE;
	while (idx < db->philo_count)
	{
		if (pthread_join(tid[idx], NULL) != SUCCESS)
		{
			write(2, "pthread_join failed, tid idx : ", 27);
			ph_putnbr_fd(idx, 2);
			write(2, "\n", 1);
			err_flag = FALSE;
		}
		idx++;
	}
	return (err_flag);
}

void	ph_print_str(char *str, t_ph *ph)
{
	pthread_mutex_lock(ph->db->print);
	if (ph->db->printlock == 0)
		printf(str, get_time_diff(ph->db->init_time) / 1000, ph->tag_no);
	pthread_mutex_unlock(ph->db->print);
}

void	ph_print_die(char *str, t_ph *ph)
{
	pthread_mutex_lock(ph->db->print);
	if (ph->db->printlock == 0)
		printf(str, get_time_diff(ph->db->init_time) / 1000, ph->tag_no);
	if (get_time_diff(ph->eat_time) > ph->db->life)
		ph->db->printlock = 1;
	pthread_mutex_unlock(ph->db->print);
}
