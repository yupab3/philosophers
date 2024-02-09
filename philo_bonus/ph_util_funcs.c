/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:30:31 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/07 15:54:24 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_all_db(t_data *db_null_able);

/* func(address of pthread_t, address of t_data)
return : TRUE */
int	free_undef_error(pthread_t *tid_null_able, t_data *db_null_able,
				pthread_mutex_t *auth_null_able)
{
	int	idx;

	if (auth_null_able != NULL)
	{
		idx = 0;
		while (idx < db_null_able->philo_count)
		{
			pthread_mutex_destroy(&auth_null_able[idx]);
			idx++;
		}
	}
	free_all_db(db_null_able);
	free(tid_null_able);
	free(auth_null_able);
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

static void	free_all_db(t_data *db_null_able)
{
	if (db_null_able->starving != NULL)
		pthread_mutex_destroy(db_null_able->starving);
	if (db_null_able->print != NULL)
		pthread_mutex_destroy(db_null_able->print);
	if (db_null_able->kill != NULL)
		pthread_mutex_destroy(db_null_able->kill);
	if (db_null_able->ready != NULL)
		pthread_mutex_destroy(db_null_able->ready);
	free(db_null_able->starving);
	free(db_null_able->print);
	free(db_null_able->kill);
	free(db_null_able->ready);
}
