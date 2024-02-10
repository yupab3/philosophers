/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:11:37 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/10 17:21:21 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>
# include <errno.h>
# include <unistd.h>

# define TRUE		1
# define FALSE		0

# define SUCCESS	0
# define FAILURE	1

/* structure of input data */
typedef struct s_data
{
	long long		philo_count;
	int				starver;
	int				death;
	long long		eat;
	long long		sleep;
	long long		life;
	long long		meals;
	int				infinity;
	int				printlock;
	int				*fork;
	pthread_mutex_t	*starving;
	pthread_mutex_t	*print;
	pthread_mutex_t	*kill;
	pthread_mutex_t	*ready;
	long long		init_time;
}				t_data;

/* structure of philosopher */
typedef struct s_ph
{
	pthread_mutex_t	*auth[2];
	int				tag_no;
	long long		eat_time;
	int				meals;
	t_data			*db;
}				t_ph;

void			*astronut(void *data);

int				ph_think(t_ph *ph);
int				ph_take_own_fork(t_ph *ph);
int				ph_take_other_fork(t_ph *ph);
int				ph_eat_something(t_ph *ph);
int				ph_fall_in_sleep(t_ph *ph);

int				drop_fork(t_ph *ph);

long long		get_time(void);
long long		get_time_diff(long long runtime);
int				ph_sleep(t_ph *ph, long long milisec);
int				ph_sleep_eat(t_ph *ph, long long milisec);

int				ph_atoi(const char *nptr, long long *ans);
void			ph_putnbr_fd(int n, int fd);

int				chk_arguments(int argc);
int				free_undef_error(pthread_t *tid_null_able,
					t_data *db_null_able, pthread_mutex_t *auth_null_able);

int				standby(t_ph *ph);
int				join_thread(pthread_t *tid, t_data *db);
void			ph_print_str(char *str, t_ph *ph);
void			ph_print_die(char *str, t_ph *ph);
int				create_thread(pthread_mutex_t *auth, pthread_t *tid,
					t_data *db);

int				destroy_mutex(pthread_mutex_t *auth, t_data *db);

int				chk_death(t_ph *ph);

t_ph			*init_philo(pthread_mutex_t *auth, t_data *db, int tag_no);
pthread_mutex_t	*init_mutex(t_data *db);
t_data			*init_data(int argc, char **argv);
pthread_t		*init_tid(t_data *db);
int				init_mutex_db(t_data *db);

int				_rt_false_with_msg_nl_fd(char *null_able, int fd);
int				_rt_failure_with_msg_nl_fd(char *null_able, int fd);
void			*_rt_null_with_msg_nl_fd(char *null_able, int fd);

#endif