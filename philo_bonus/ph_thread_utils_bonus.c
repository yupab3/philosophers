/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:55:55 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/06/24 17:01:02 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(address of each thread's philo)
return : NONE(void) */
int	standby(t_ph *ph)
{
	int	a;
	int	delay;

	a = ph->db->philo_count % 2;
	delay = ph->db->eat;
	if (ph->db->eat != ph->db->sleep)
		ph->chk_time = ph->db->eat - ph->db->sleep;
	if (a == 1)
		ph->chk_time = 2 * ph->db->eat - ph->db->sleep;
	if (delay == 0)
		delay = ph->db->life;
	sem_wait(ph->db->ready);
	sem_post(ph->db->ready);
	ph->eat_time = ph->db->init_time;
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
int	create_child(sem_t *auth, int *pid, t_data *db)
{
	t_ph			*philo;
	int				idx;

	idx = 0;
	while (idx < db->philo_count)
	{
		philo = init_philo(auth, db, idx);
		if (philo == NULL && free_undef_error(pid, db, auth))
			return (FALSE);
		pid[idx] = fork();
		if (pid[idx] == 0)
			astronut(philo);
		free(philo);
		idx++;
	}
	if (idx != db->philo_count)
	{
		idx = 0;
		while (idx++ < db->philo_count)
			sem_post(db->starving);
		kill_process(pid, db);
		return (_rt_false_with_msg_nl_fd(
				"func. create_child - pthread create error", 2));
	}
	return (TRUE);
}

/* func(tid, db)
return : TRUE */
int	kill_process(int *pid, t_data *db)
{
	int	err_flag;
	int	idx;

	idx = 0;
	err_flag = TRUE;
	while (idx++ < db->philo_count)
		sem_wait(db->starving);
	idx = 0;
	while (pid[idx] != 0 && idx < db->philo_count)
	{
		if (kill(pid[idx], SIGKILL) != SUCCESS)
		{
			write(2, "kill failed, pid idx : ", 27);
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
	sem_wait(ph->db->print);
	printf(str, get_time_diff(ph->db->init_time) / 1000, ph->tag_no);
	sem_post(ph->db->print);
}

void	ph_print_die(char *str, t_ph *ph)
{
	sem_wait(ph->db->print);
	printf(str, get_time_diff(ph->db->init_time) / 1000, ph->tag_no);
}
