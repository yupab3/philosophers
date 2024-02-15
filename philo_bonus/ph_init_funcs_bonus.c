/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_funcs_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:18:24 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/15 17:25:35 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/* func(address of t_data, tag_no)
return : allocated address of t_ph or NULL */
t_ph	*init_philo(sem_t *auth, t_data *db, int tag_no)
{
	t_ph			*ph;

	ph = (t_ph *)malloc(sizeof(t_ph));
	if (ph == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_philo - malloc error", 2));
	memset(ph, 0, sizeof(t_ph));
	ph->db = db;
	ph->meals = ph->db->meals;
	ph->tag_no = tag_no + 1;
	ph->auth = auth;
	return (ph);
}

/* func(argc of main func, argv of main func)
return : allocated address of t_data or NULL */
t_data	*init_data(int argc, char **argv)
{
	t_data	*db;

	db = (t_data *)malloc(sizeof(t_data));
	if (db == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_data - malloc error", 2));
	memset(db, 0, sizeof(t_data));
	if (ph_atoi(argv[1], &(db->philo_count)) == FALSE
		|| ph_atoi(argv[2], &(db->life)) == FALSE
		|| ph_atoi(argv[3], &(db->eat)) == FALSE
		|| ph_atoi(argv[4], &(db->sleep)) == FALSE)
	{
		free(db);
		return (_rt_null_with_msg_nl_fd("func. init_data - atoi error", 2));
	}
	if (init_sem_db(db) == FALSE)
		return (_rt_null_with_msg_nl_fd("func. init_data - sem_init error", 2));
	if (argc == 5)
		db->infinity = 1;
	else if (ph_atoi(argv[5], &(db->meals)) == FALSE)
	{
		free(db);
		return (_rt_null_with_msg_nl_fd("func. init_data - atoi error", 2));
	}
	return (db);
}

/* func(total philocount)
return : allocated address of pthread_t or NULL */
int	*init_pid(t_data *db)
{
	int			*pid;
	int			philo_count;

	if (db == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_pid - db is NULL", 2));
	db->life *= 1000;
	db->eat *= 1000;
	db->sleep *= 1000;
	philo_count = db->philo_count;
	pid = (int *)malloc(sizeof(int) * philo_count);
	if (pid == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_pid - malloc error", 2));
	memset(pid, 0, sizeof(int) * philo_count);
	return (pid);
}

/* func(db of main func)
return : TRUE or FALSE */
int	init_sem_db(t_data *db)
{
	sem_unlink("ph_starving");
	sem_unlink("ph_ready");
	sem_unlink("ph_print");
	sem_unlink("ph_auth");
	db->starving = sem_open("ph_starving",
			O_CREAT | O_RDWR, 0644, 0);
	db->ready = sem_open("ph_ready",
			O_CREAT | O_RDWR, 0644, 1);
	db->print = sem_open("ph_print",
			O_CREAT | O_RDWR, 0644, 1);
	if (db->starving == SEM_FAILED || db->ready == SEM_FAILED
		|| db->print == SEM_FAILED)
		return (_rt_false_with_msg_cleaning_sem(
				"func. init_sem_db - sem_init error", 2, db));
	return (TRUE);
}
