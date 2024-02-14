/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:11:37 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/14 15:57:22 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
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
	long long		eat;
	long long		sleep;
	long long		life;
	long long		meals;
	int				infinity;
	sem_t			*starving;
	sem_t			*print;
	sem_t			*ready;
	long long		init_time;
}				t_data;

/* structure of philosopher */
typedef struct s_ph
{
	sem_t			*auth;
	int				tag_no;
	long long		eat_time;
	int				meals;
	long long		chk_time;
	t_data			*db;
}				t_ph;

void			*astronut(t_ph *ph);

int				ph_think(t_ph *ph);
int				ph_take_fork(t_ph *ph);
// int				ph_take_other_fork(t_ph *ph);
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
void			close_unlink_all_db_sem(t_data *db_null_able);
int				free_undef_error(int *pid_null_able, t_data *db_null_able,
					sem_t *auth_null_able);

int				standby(t_ph *ph);
int				kill_process(int *pid, t_data *db);
void			ph_print_str(char *str, t_ph *ph);
void			ph_print_die(char *str, t_ph *ph);
int				create_child(sem_t *auth, int *tid, t_data *db);

int				destroy_sem(sem_t *auth, t_data *db, int *pid);

int				chk_death(t_ph *ph);

t_ph			*init_philo(sem_t *auth, t_data *db, int tag_no);
t_data			*init_data(int argc, char **argv);
int				*init_pid(t_data *db);
int				init_sem_db(t_data *db);

int				_rt_false_with_msg_nl_fd(char *null_able, int fd);
int				_rt_failure_with_msg_nl_fd(char *null_able, int fd);
void			*_rt_null_with_msg_nl_fd(char *null_able, int fd);
int				_rt_false_with_msg_cleaning_sem(char *null_able, int fd,
					t_data *db);

#endif