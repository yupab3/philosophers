/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:18:24 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/07 14:38:00 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(address of t_data, tag_no)
return : allocated address of t_ph or NULL */
t_ph	*init_philo(pthread_mutex_t *auth, t_data *db, int tag_no)
{
	t_ph			*ph;

	ph = (t_ph *)malloc(sizeof(t_ph));
	if (ph == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_philo - malloc error", 2));
	memset(ph, 0, sizeof(t_ph));
	ph->db = db;
	ph->meals = ph->db->meals;
	ph->tag_no = tag_no;
	ph->auth[0] = &auth[tag_no];
	if (tag_no == db->philo_count - 1)
		ph->auth[1] = &auth[0];
	else
		ph->auth[1] = &auth[tag_no + 1];
	return (ph);
}

/* func(address of pthread_mutex_t, address of t_data)
return : allocated address of pthread_mutex_t or NULL */
pthread_mutex_t	*init_mutex(t_data *db)
{
	pthread_mutex_t	*auth;
	int				idx;

	if (db == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_mutex - db is NULL", 2));
	auth = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * db->philo_count);
	if (auth == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_mutex - malloc error", 2));
	memset(auth, 0, sizeof(pthread_mutex_t) * db->philo_count);
	idx = 0;
	while (idx < db->philo_count)
	{
		if (pthread_mutex_init(&(auth[idx]), NULL) != SUCCESS)
			break ;
		idx++;
	}
	if (idx != db->philo_count)
	{
		while (idx-- > 0)
			pthread_mutex_destroy(&(auth[idx]));
		return (_rt_null_with_msg_nl_fd(
				"func. init_mutex - mutex init error", 2));
	}
	return (auth);
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
	if (init_mutex_db(db) == FALSE)
		return (_rt_null_with_msg_nl_fd("func. init_data - mutex error", 2));
	if (ph_atoi(argv[1], &(db->philo_count)) == FALSE
		|| ph_atoi(argv[2], &(db->life)) == FALSE
		|| ph_atoi(argv[3], &(db->eat)) == FALSE
		|| ph_atoi(argv[4], &(db->sleep)) == FALSE)
	{
		free(db);
		return (_rt_null_with_msg_nl_fd("func. init_data - atoi error", 2));
	}
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
pthread_t	*init_tid(t_data *db)
{
	pthread_t	*tid;
	int			philo_count;

	if (db == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_tid - db is NULL", 2));
	philo_count = db->philo_count;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * philo_count);
	if (tid == NULL)
		return (_rt_null_with_msg_nl_fd("func. init_tid - malloc error", 2));
	memset(tid, 0, sizeof(pthread_t));
	return (tid);
}

/* func(db of main func)
return : TRUE or FALSE */
int	init_mutex_db(t_data *db)
{
	db->ready = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	db->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	db->kill = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (db->ready == NULL || db->kill == NULL || db->print == NULL)
	{
		free(db->ready);
		free(db->kill);
		free(db->print);
		return (_rt_false_with_msg_nl_fd(
				"func. init_mutex_db - malloc error", 2));
	}
	memset(db->ready, 0, sizeof(pthread_mutex_t));
	memset(db->print, 0, sizeof(pthread_mutex_t));
	memset(db->kill, 0, sizeof(pthread_mutex_t));
	if (pthread_mutex_init(db->ready, NULL) != SUCCESS)
		return (_rt_false_with_msg_nl_fd(
				"func. init_mutex_db - mutex init error (ready)", 2));
	if (pthread_mutex_init(db->print, NULL) != SUCCESS)
		return (_rt_false_with_msg_nl_fd(
				"func. init_mutex_db - mutex init error (print)", 2));
	if (pthread_mutex_init(db->kill, NULL) != SUCCESS)
		return (_rt_false_with_msg_nl_fd(
				"func. init_mutex_db - mutex init error (kill)", 2));
	return (TRUE);
}
